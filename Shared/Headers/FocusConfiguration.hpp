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
    std::string _email = "";
    std::string _password = "";
};

struct device {
    std::string _id = "";
    std::string _name = "";
};

struct server {
    std::string _ip = "";
    int _port = 0;
    serverType _type = serverType::DEFAULT;
};

class FocusConfiguration {
private:
    user _userInfo;
    device _device;
    std::string _triggerAfk;
    std::vector<server> _serversInfo;
    bool _filled;
    struct server _defaultServer;
    std::string _configFile;
    std::string _source;
public:
    FocusConfiguration(const std::string &configFile);

    void readConfiguration(int attempt);

    bool isFilled() const;

    struct user getUser() const;

    struct server getServer(const serverType type) const;

    struct device getDevice() const;

    void setDeviceId(const std::string &deviceId);

    void setTriggerAfk(const std::string &triggerAfk);

    std::string getTriggerAfk() const;

    void generateConfigurationFile();
};


#endif //DAEMON_FOCUSCONFIGURATION_HPP
