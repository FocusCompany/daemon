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
#include "FocusEventListener.hpp"


class FocusAuthenticator {
private:
    std::unique_ptr<httplib::Client> _cli;
    std::shared_ptr<FocusConfiguration> _config;
    std::string _token = "";
    std::string _uuid = "";
    std::string _deviceId = "";
    bool _connected = false;
public:
    void Run(std::shared_ptr<FocusConfiguration> &config);

    std::string GetUUID() const;

    std::string GetDeviceId() const;

    bool GetConnectionStatus() const;

    std::string GetToken();

    bool Login(const std::string &email, const std::string &password, const std::string &deviceId = "");

    bool RegisterDevice(const std::string &name);

    bool Disconnect();

    bool RenewToken();
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
