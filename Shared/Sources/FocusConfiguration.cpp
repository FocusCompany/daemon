//
// Created by Etienne Pasteur on 27/03/2018.
//

#include <iostream>
#include <fstream>
#include <spdlog_pragma.hpp>
#include "FocusConfiguration.hpp"
#include <lightconf_pragma.hpp>
#include "json_pragma.hpp"

namespace lightconf {
    LIGHTCONF_BEGIN_ENUM(serverType)
                    LIGHTCONF_ENUM_VALUE(serverType::AUTHENTICATION, "AUTHENTICATION")
                    LIGHTCONF_ENUM_VALUE(serverType::BACKEND, "BACKEND")
    LIGHTCONF_END_ENUM()

    LIGHTCONF_BEGIN_TYPE(user)
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _email, "email")
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _password, "password")
    LIGHTCONF_END_TYPE()

    LIGHTCONF_BEGIN_TYPE(device)
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _id, "id_device")
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _name, "device_name")
    LIGHTCONF_END_TYPE()


    LIGHTCONF_BEGIN_TYPE(server)
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _ip, "ip")
        LIGHTCONF_TYPE_MEMBER_REQ(int, _port, "port")
        LIGHTCONF_TYPE_MEMBER_REQ(serverType, _type, "type")
    LIGHTCONF_END_TYPE()
}

FocusConfiguration::FocusConfiguration(const std::string &configFile) :
        _userInfo({user{"", ""}}),
        _device({device{"", ""}}),
        _triggerAfk("300"),
        _serversInfo({server{"auth.thefocuscompany.me", 3000, serverType::AUTHENTICATION}, server{"backend.thefocuscompany.me", 5555, serverType::BACKEND}}),
        _defaultServer({std::string("127.0.0.1"), 4242, serverType::DEFAULT}),
        _configFile(configFile),
        _source(),
        _eventEmitter(std::make_unique<FocusEventEmitter>()),
        _messageListener(std::make_unique<FocusEventListener<const std::string &>>()) {
    readConfiguration();
    generateConfigurationFile();
    _messageListener->RegisterMessage("Configuration", [this](const std::string &data) {
        auto j = nlohmann::json::parse(data);
        if (j.find("action") != j.end()) {
            if (j["action"] == "get_user_credentials") {
                _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"fill_login_form\", \"data\": {\"email\": \"" + _userInfo._email + "\", \"password\": \"" + _userInfo._password + "\"}}");
            } else if (j["action"] == "set_user_credentials") {
                if (j.find("data") != j.end()) {
                    auto infoUser = j["data"];
                    setUser(infoUser["email"], infoUser["password"]);
                }
            }
        }
    });
}

struct server FocusConfiguration::getServer(const serverType type) const {
    auto it = std::find_if(_serversInfo.begin(), _serversInfo.end(), [type](const server &srv) { return srv._type == type; });
    if (it != _serversInfo.end())
        return (*it);
    else {
        return (_defaultServer);
    }
}

struct device FocusConfiguration::getDevice() const {
    return _device;
}

void FocusConfiguration::setDevice(const std::string &deviceName, const std::string &deviceId) {
    if (!_source.empty()) {
        _device = device{deviceId, deviceName};
        lightconf::group config;
        config = lightconf::config_format::read(_source);
        config.set<device>("device", device{
                deviceId,
                deviceName
        });
        std::ofstream stream(_configFile, std::ios::out);
        if (stream) {
            _source = lightconf::config_format::write(config, _source, 80);
            stream << _source;
            spdlog::get("logger")->info("Device id stored in configuration file");
        }
    }
}

std::string FocusConfiguration::getTriggerAfk() const {
    return _triggerAfk;
}

void FocusConfiguration::setTriggerAfk(const std::string &triggerAfk) {
    if (!_source.empty()) {
        _triggerAfk = triggerAfk;
        lightconf::group config;
        config = lightconf::config_format::read(_source);
        config.set<std::string>("trigger_afk", triggerAfk);
        std::ofstream stream(_configFile, std::ios::out);
        if (stream) {
            _source = lightconf::config_format::write(config, _source, 80);
            stream << _source;
            spdlog::get("logger")->info("triggerAfk id stored in configuration file");
        }
    }
}

struct user FocusConfiguration::getUser() const {
    return _userInfo;
}

void FocusConfiguration::setUser(const std::string &email, const std::string &password) {
    if (!_source.empty()) {
        _userInfo = user{email, password};
        lightconf::group config;
        config = lightconf::config_format::read(_source);
        config.set<user>("user", user{
                email,
                password
        });
        std::ofstream stream(_configFile, std::ios::out);
        if (stream) {
            _source = lightconf::config_format::write(config, _source, 80);
            stream << _source;
            spdlog::get("logger")->info("User stored in configuration file");
        }
    }
}

void FocusConfiguration::generateConfigurationFile() {
    spdlog::get("logger")->info("Generating a default configuration file");
    lightconf::group config;
    _source = "";
    try {
        config = lightconf::config_format::read(_source);
        config.set<user>("user", _userInfo);
        config.set<std::vector<server>>("servers", _serversInfo);
        config.set<std::string>("trigger_afk", _triggerAfk);
        config.set<device>("device", _device);
        std::ofstream outStream(_configFile, std::ios::out);
        if (outStream) {
            _source = lightconf::config_format::write(config, _source, 80);
            outStream << _source;
            spdlog::get("logger")->info("Written configuration file successfully");
        } else {
            spdlog::get("logger")->critical("Unable to create config file");
        }
    } catch (const std::exception &) {
        spdlog::get("logger")->error("Failed to write configuration file");
    }
}

void FocusConfiguration::readConfiguration() {
    lightconf::group config;
    _source = "";
    try {
        spdlog::get("logger")->info("Loading configuration file from {0}", _configFile);
        std::ifstream stream(_configFile, std::ios::in);
        if (stream) {
            _source = std::string(std::istreambuf_iterator<char>(stream),
                                  std::istreambuf_iterator<char>());
            config = lightconf::config_format::read(_source);
            _userInfo = config.get<user>("user", _userInfo);
            _device = config.get<device>("device", _device);
            _triggerAfk = config.get<std::string>("trigger_afk", _triggerAfk);
            _serversInfo = config.get<std::vector<server>>("servers", _serversInfo);
            spdlog::get("logger")->info("Reading configuration file successfully");
            return;
        } else {
            spdlog::get("logger")->warn("Missing configuration file");
        }
    } catch (const lightconf::parse_error &) {
        spdlog::get("logger")->error("Parsing configuration file error");
    } catch (const std::exception &) {
        spdlog::get("logger")->error("Failed to read configuration file");
    }
}