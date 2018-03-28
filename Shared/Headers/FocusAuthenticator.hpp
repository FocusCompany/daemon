//
// Created by Etienne Pasteur on 16/12/2017.
//

#ifndef DAEMON_FOCUSAUTHENTICATOR_HPP
#define DAEMON_FOCUSAUTHENTICATOR_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <httplib.h>
#include "FocusConfiguration.hpp"

class FocusAuthenticator {
private:
    std::unique_ptr<httplib::Client> _cli;
    std::string _token;
    std::string _uuid;
    bool _connected = false;
public:
    void Run(FocusConfiguration &config);

    std::string GetUUID() const;

    bool GetConnectionStatus() const;

    std::string GetCurrentToken() const;

    bool Login(const std::string &email, const std::string &password);

    bool Disconnect();

    bool RenewToken();
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
