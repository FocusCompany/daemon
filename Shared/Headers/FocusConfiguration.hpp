//
// Created by Etienne Pasteur on 27/03/2018.
//

#ifndef DAEMON_FOCUSCONFIGURATION_HPP
#define DAEMON_FOCUSCONFIGURATION_HPP

#include <string>
#include <vector>

enum class serverType {
    AUTHENTICATION, BACKEND
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
    std::vector<server> _serversInfo;
    bool _filed = false;
public:
    FocusConfiguration(const std::string &configFile);

    bool isFiled() const;

    struct user getUser()const ;

    struct server getServer(const serverType type) const;
};


#endif //DAEMON_FOCUSCONFIGURATION_HPP
