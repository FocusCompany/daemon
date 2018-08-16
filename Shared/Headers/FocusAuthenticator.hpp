//
// Created by Etienne Pasteur on 16/12/2017.
//

#ifndef DAEMON_FOCUSAUTHENTICATOR_HPP
#define DAEMON_FOCUSAUTHENTICATOR_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <httplib_pragma.hpp>
#include "FocusConfiguration.hpp"
#include "FocusEventListener.hpp"

class FocusAuthenticator {
private:
    static constexpr auto public_key = "-----BEGIN PUBLIC KEY-----\n"
                                       "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDdlatRjRjogo3WojgGHFHYLugdUWAY9iR3fy4arWNA1KoS8kVw33cJibXr8bvwUAUparCwlvdbH6dvEOfou0/gCFQsHUfQrSDv+MuSUMAe8jzKE4qW+jK+xQU9a03GUnKHkkle+Q0pX/g6jXZ7r1/xAK5Do2kQ+X5xK9cipRgEKwIDAQAB\n"
                                       "-----END PUBLIC KEY-----";

    std::unique_ptr<httplib::Client> _cli;
    std::shared_ptr<FocusConfiguration> _config;
    std::string _token;
    std::string _uuid;
    std::string _deviceId;
    bool _connected;
    int _connectionAttempt;

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

    FocusAuthenticator();
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
