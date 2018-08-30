//
// Created by Etienne Pasteur on 16/12/2017.
//

#include "json_pragma.hpp"
#include "FocusAuthenticator.hpp"
#include "jwt_pragma.hpp"
#include <spdlog_pragma.hpp>

void FocusAuthenticator::Run(std::shared_ptr<FocusConfiguration> &config) {
    _config = config;
    auto srv = _config->getServer(serverType::AUTHENTICATION);
    _cli = std::make_unique<httplib::Client>(srv._ip.c_str(), srv._port, 5);
    _messageListener->RegisterMessage("Authenticator", [this](const std::string &data) {
        auto j = nlohmann::json::parse(data);
        if (j.find("action") != j.end()) {
            if (j["action"] == "login") {
                if (j.find("data") != j.end()) {
                    auto infoUser = j["data"];
                    Login(infoUser["email"], infoUser["password"], _config->getDevice()._id);
                }
            } else if (j["action"] == "register_device") {
                if (j.find("data") != j.end()) {
                    auto infoUser = j["data"];
                    if (RegisterDevice(infoUser["device_name"])) {
                        Login(infoUser["email"], infoUser["password"], _config->getDevice()._id);
                    }
                }
            } else if (j["action"] == "logout") {
                Disconnect();
            }
        }
    });
}

std::string FocusAuthenticator::GetUUID() const {
    return _uuid;
}

std::string FocusAuthenticator::GetDeviceId() const {
    return _deviceId;
}

bool FocusAuthenticator::GetConnectionStatus() const {
    return _connected;
}

std::string FocusAuthenticator::GetToken() {
    try {
        auto dec_obj = jwt::decode(_token, jwt::params::algorithms({"rs256"}), jwt::params::secret(public_key), jwt::params::verify(true));
        spdlog::get("logger")->info("Token is valid");
    } catch (const jwt::TokenExpiredError &) {
        spdlog::get("logger")->info("Renewing token");
        RenewToken();
    } catch (...) {
        spdlog::get("logger")->error("Invalid token");
    }
    return _token;
}

bool FocusAuthenticator::Login(const std::string &email, const std::string &password, const std::string &deviceId) {
    if (_connectionAttempt > 3) {
        spdlog::get("logger")->critical("Failed to connect to authentication server after {0} attempt", _connectionAttempt - 1);
        std::exit(1);
    }

    spdlog::get("logger")->info("Attempt to login");
    httplib::Params params = {
            {"email",    email},
            {"password", password}
    };
    if (!deviceId.empty()) {
        params.insert({"device_id", deviceId});
    }
    auto res = _cli->post("/api/v1/login", params);
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        int waiting = _connectionAttempt * 5;
        spdlog::get("logger")->info("Retrying in {} seconds", waiting);
        std::this_thread::sleep_for(std::chrono::seconds(waiting));
        ++_connectionAttempt;
        _connected = false;
        return Login(email, password, deviceId);
    } else if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end()) {
            try {
                std::string tmp = j["token"];
                auto dec_obj = jwt::decode(tmp, jwt::params::algorithms({"rs256"}), jwt::params::secret(public_key), jwt::params::verify(true));
                if (dec_obj.payload().has_claim("uuid")) {
                    if (dec_obj.payload().has_claim("device_id")) {
                        _deviceId = std::to_string(dec_obj.payload().get_claim_value<int>("device_id"));
                    }
                    _uuid = dec_obj.payload().get_claim_value<std::string>("uuid");
                    _token = j["token"];
                    _connected = true;
                    spdlog::get("logger")->info("Successfully connected");
                    _connectionAttempt = 1;
                    if (_deviceId.empty()) {
                        _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"login\", \"data\": {\"status\": \"success\", \"device\": \"false\"}}");
                    } else {
                        _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"login\", \"data\": {\"status\": \"success\", \"device\": \"true\"}}");
                        _eventEmitter->EmitMessage("OkForRunning", "OK");
                    }
                    return true;
                }
            } catch (...) {
                spdlog::get("logger")->error("Invalid token");
                _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"login\", \"data\": {\"status\": \"error\"}}");
                _connected = false;
                return false;
            }

        }
    } else {
        _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"login\", \"data\": {\"status\": \"error\"}}");
        spdlog::get("logger")->error("Authentication failed, enter your credentials again");
    }
    _connected = false;
    return false;
}

bool FocusAuthenticator::RegisterDevice(const std::string &name) {
    if (_connectionAttempt > 3) {
        spdlog::get("logger")->critical("Failed to connect to authentication server after {0} attempt", _connectionAttempt - 1);
        std::exit(1);
    }

    spdlog::get("logger")->info("Registering new device : {}", name);
    std::stringstream auth;
    auth << "Bearer " << _token;
    httplib::Headers headers = {
            {"Authorization", auth.str()}
    };
    httplib::Params params = {{"devices_name", name}};
    auto res = _cli->post("/api/v1/register_device", headers, params);
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        int waiting = _connectionAttempt * 5;
        spdlog::get("logger")->info("Retrying in {} seconds", waiting);
        std::this_thread::sleep_for(std::chrono::seconds(waiting));
        ++_connectionAttempt;
        RegisterDevice(name);
        return false;
    } else if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("deviceId") != j.end()) {
            _config->setDevice(name, std::to_string(static_cast<int>(j["deviceId"])));
            spdlog::get("logger")->info("Device successfully registered");
            _connectionAttempt = 0;
            return true;
        }
    } else {
        spdlog::get("logger")->critical("Registration failed");
        std::exit(1);
    }
    return false;
}

bool FocusAuthenticator::RenewToken() {
    if (_connectionAttempt > 3) {
        spdlog::get("logger")->critical("Failed to connect to authentication server after {0} attempt", _connectionAttempt - 1);
        std::exit(1);
    }

    httplib::Params params = {
            {"token", _token}
    };
    auto res = _cli->post("/api/v1/renew_jwt", params);
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        int waiting = _connectionAttempt * 5;
        spdlog::get("logger")->info("Retrying in {} seconds", waiting);
        std::this_thread::sleep_for(std::chrono::seconds(waiting));
        ++_connectionAttempt;
        _connected = false;
        RenewToken();
        return false;
    } else if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end()) {
            try {
                std::string tmp = j["token"];
                auto dec_obj = jwt::decode(tmp, jwt::params::algorithms({"rs256"}), jwt::params::secret(public_key), jwt::params::verify(true));
                if (dec_obj.payload().has_claim("uuid")) {
                    if (dec_obj.payload().has_claim("device_id")) {
                        _deviceId = std::to_string(dec_obj.payload().get_claim_value<int>("device_id"));
                    }
                    _uuid = dec_obj.payload().get_claim_value<std::string>("uuid");
                    _token = j["token"];
                    _connected = true;
                    spdlog::get("logger")->info("Token successfully renewed");
                    _connectionAttempt = 0;
                    return true;
                }
            } catch (...) {
                spdlog::get("logger")->error("Invalid token signature");
                _connected = false;
                return false;
            }

        }
    } else {
        spdlog::get("logger")->error("Renewing token failed");
    }
    _connected = false;
    return false;
}

bool FocusAuthenticator::Disconnect() {
    std::stringstream auth;
    auth << "Bearer " << _token;
    httplib::Headers headers = {
            {"Authorization", auth.str()}
    };
    auto res = _cli->del("/api/v1/delete_jwt", headers, "", "application/x-www-form-urlencoded");
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        return false;
    } else if (res && res->status == 200) {
        _token.clear();
        _uuid.clear();
        _connected = false;
        spdlog::get("logger")->info("Successfully disconnected");
        return true;
    } else {
        spdlog::get("logger")->error("Disconnection failed");
    }
    return false;
}

FocusAuthenticator::FocusAuthenticator() : _eventEmitter(std::make_unique<FocusEventEmitter>()),
                                           _messageListener(std::make_unique<FocusEventListener<const std::string &>>()),
                                           _cli(),
                                           _config(),
                                           _token(),
                                           _uuid(),
                                           _deviceId(),
                                           _connected(false),
                                           _connectionAttempt(1) {}
