//
// Created by Etienne Pasteur on 16/12/2017.
//

#include "FocusAuthenticator.hpp"
#include <json.hpp>
#include <jwt/jwt_all.h>
#include <spdlog/spdlog.h>

void FocusAuthenticator::Run(FocusConfiguration &config) {
    auto srv = config.getServer(serverType::AUTHENTICATION);
    _cli = std::make_unique<httplib::Client>(srv._ip.c_str(), srv._port, 5);
}

std::string FocusAuthenticator::GetUUID() const {
    return _uuid;
}

bool FocusAuthenticator::GetConnectionStatus() const {
    return _connected;
}

std::string FocusAuthenticator::GetCurrentToken() const{
    return _token;
}

bool FocusAuthenticator::Login(const std::string &email, const std::string &password) {
    spdlog::get("logger")->info("Attempt to login");
    httplib::Params params = {
            {"email",    email},
            {"password", password}
    };
    auto res = _cli->post("/login", params);
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        _connected = false;
        return false;
    } else if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end()) {
            ExpValidator exp;
            std::ifstream rsa_pub_file("./keys/public_key");
            if (!rsa_pub_file.is_open()) {
                spdlog::get("logger")->error("Can not find rsa keys to verify the token signature");
            } else {
                std::string rsa_pub_key{std::istreambuf_iterator<char>(rsa_pub_file), std::istreambuf_iterator<char>()};
                RS256Validator signer(rsa_pub_key);
                try {
                    nlohmann::json header, payload;
                    std::tie(header, payload) = JWT::Decode(j["token"], &signer, &exp);
                    auto pl = nlohmann::json::parse(payload.dump());
                    if (pl.find("uuid") != pl.end()) {
                        _uuid = pl["uuid"];
                        _token = j["token"];
                        _connected = true;
                        spdlog::get("logger")->info("Successfully connected");
                        return true;
                    }
                } catch (InvalidTokenError &tfe) {
                    spdlog::get("logger")->error("Invalid token signature");
                    _connected = false;
                    return false;
                }
            }
        }
    }
    _connected = false;
    return false;
}

bool FocusAuthenticator::RenewToken() {
    httplib::Params params = {
            {"token", _token}
    };
    auto res = _cli->post("/renew_jwt", params);
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        _connected = false;
        return false;
    } else if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end()) {
            ExpValidator exp;
            std::ifstream rsa_pub_file("./keys/public_key");
            if (!rsa_pub_file.is_open()) {
                spdlog::get("logger")->error("Can not find rsa keys to verify the token signature");
            } else {
                std::string rsa_pub_key{std::istreambuf_iterator<char>(rsa_pub_file), std::istreambuf_iterator<char>()};
                RS256Validator signer(rsa_pub_key);
                try {
                    nlohmann::json header, payload;
                    std::tie(header, payload) = JWT::Decode(j["token"], &signer, &exp);
                    auto pl = nlohmann::json::parse(payload.dump());
                    if (pl.find("uuid") != pl.end()) {
                        _uuid = pl["uuid"];
                        _token = j["token"];
                        _connected = true;
                        spdlog::get("logger")->info("Token successfully renewed");
                        return true;
                    }
                } catch (InvalidTokenError &tfe) {
                    spdlog::get("logger")->error("Invalid token signature");
                    _connected = false;
                    return false;
                }
            }
        }
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
    auto res = _cli->del("/delete_jwt", headers, "", "application/x-www-form-urlencoded");
    if (res == nullptr) {
        spdlog::get("logger")->error("Can not establish connection with authentication server");
        return false;
    } else if (res && res->status == 200) {
        _token.clear();
        _uuid.clear();
        _connected = false;
        spdlog::get("logger")->info("Successfully disconnected");
        return true;
    }
    return false;
}
