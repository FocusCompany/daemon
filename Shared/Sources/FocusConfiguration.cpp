//
// Created by Etienne Pasteur on 27/03/2018.
//

#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>
#include "FocusConfiguration.hpp"
#include "lightconf/lightconf.hpp"
#include "lightconf/config_format.hpp"

namespace lightconf {
    LIGHTCONF_BEGIN_ENUM(serverType)
                    LIGHTCONF_ENUM_VALUE(serverType::AUTHENTICATION, "AUTHENTICATION")
                    LIGHTCONF_ENUM_VALUE(serverType::BACKEND, "BACKEND")
    LIGHTCONF_END_ENUM()

    LIGHTCONF_BEGIN_TYPE(user)
        LIGHTCONF_TYPE_MEMBER_OPT(std::string, _first_name, "first_name", "foo")
        LIGHTCONF_TYPE_MEMBER_OPT(std::string, _last_name, "last_name", "bar")
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _email, "email")
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _password, "password")
    LIGHTCONF_END_TYPE()

    LIGHTCONF_BEGIN_TYPE(server)
        LIGHTCONF_TYPE_MEMBER_REQ(std::string, _ip, "ip")
        LIGHTCONF_TYPE_MEMBER_REQ(int, _port, "port")
        LIGHTCONF_TYPE_MEMBER_REQ(serverType, _type, "type")
    LIGHTCONF_END_TYPE()
}

FocusConfiguration::FocusConfiguration(const std::string &configFile) {
    _defaultServer._ip = "127.0.0.1";
    _defaultServer._port = 4242;
    _defaultServer._type = serverType::DEFAULT;

    _configFile = configFile;
    lightconf::group config;
    _source = "";
    try {
        spdlog::get("logger")->info("Loading configuration file from {0}", configFile);
        std::ifstream stream(_configFile, std::ios::in);
        if (stream) {
            _source = std::string(std::istreambuf_iterator<char>(stream),
                                  std::istreambuf_iterator<char>());
            config = lightconf::config_format::read(_source);
            _userInfo = config.get<user>("user");
            _triggerAfk = config.get<std::string>("trigger_afk", "300");
            _deviceId = config.get<std::string>("id_device", "");
            _serversInfo = config.get<std::vector<server>>("servers", {});
            _filled = true;
            spdlog::get("logger")->info("Reading configuration file successfully");
        } else {
            _filled = false;
            spdlog::get("logger")->error("Missing configuration file");
        }
    } catch (const lightconf::parse_error &e) {
        _filled = false;
        spdlog::get("logger")->error("Parsing configuration file error");
    } catch (const std::exception &e) {
        _filled = false;
        spdlog::get("logger")->error("Failed to read configuration file");
    }
}

bool FocusConfiguration::isFilled() const {
    return _filled;
}

struct user FocusConfiguration::getUser() const {
    return _userInfo;
}

struct server FocusConfiguration::getServer(const serverType type) const {
    auto it = std::find_if(_serversInfo.begin(), _serversInfo.end(), [type](const server &srv) { return srv._type == type; });
    if (it != _serversInfo.end())
        return (*it);
    else {
        return (_defaultServer);
    }
}

void FocusConfiguration::setDeviceId(const std::string &deviceId) {
    if (_filled && !_source.empty()) {
        _deviceId = deviceId;
        lightconf::group config;
        config = lightconf::config_format::read(_source);
        config.set<std::string>("id_device", deviceId);
        std::ofstream stream(_configFile, std::ios::out);
        if (stream) {
            stream << lightconf::config_format::write(config, _source, 80);
            spdlog::get("logger")->info("Device id stored in configuration file");
        }
    }
}

std::string FocusConfiguration::getDeviceId() const {
    return _deviceId;
}

std::string FocusConfiguration::getTriggerAfk() const {
    return _triggerAfk;
}

void FocusConfiguration::setTriggerAfk(const std::string &triggerAfk) {
    if (_filled && !_source.empty()) {
        _triggerAfk = triggerAfk;
        lightconf::group config;
        config = lightconf::config_format::read(_source);
        config.set<std::string>("trigger_afk", triggerAfk);
        std::ofstream stream(_configFile, std::ios::out);
        if (stream) {
            stream << lightconf::config_format::write(config, _source, 80);
            spdlog::get("logger")->info("triggerAfk id stored in configuration file");
        }
    }
}
