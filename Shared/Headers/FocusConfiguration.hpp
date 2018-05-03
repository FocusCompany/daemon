//
// Created by Etienne Pasteur on 27/03/2018.
//

#ifndef DAEMON_FOCUSCONFIGURATION_HPP
#define DAEMON_FOCUSCONFIGURATION_HPP

#include <string>
#include <vector>

enum class serverType {
    AUTHENTICATION, BACKEND, DEFAULT
};

struct user {
    std::string _first_name;
    std::string _last_name;
    std::string _email;
    std::string _password;
};

struct server {
    std::string _ip;
    int _port;
    serverType _type;
};

class FocusConfiguration {
private:
    user _userInfo;
    std::string _deviceId;
    std::string _triggerAfk;
    std::vector<server> _serversInfo;
    bool _filled = false;
    struct server _defaultServer;
    std::string _configFile;
    std::string _source;
    std::string _deviceName;
public:
    FocusConfiguration(const std::string &configFile);

    void readConfiguration(const std::string &configFile, int attempt);

    bool isFilled() const;

    struct user getUser() const;

    struct server getServer(const serverType type) const;

    std::string getDeviceId() const;

    void setDeviceId(const std::string &deviceId);

    void setTriggerAfk(const std::string &triggerAfk);

    std::string getTriggerAfk() const;

    void generateConfigurationFile(const std::string &configFile);

    const std::string &getDeviceName() const;
};


#endif //DAEMON_FOCUSCONFIGURATION_HPP
