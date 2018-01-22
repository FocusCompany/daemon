//
// Created by Etienne Pasteur on 16/12/2017.
//

#ifndef DAEMON_FOCUSAUTHENTICATOR_HPP
#define DAEMON_FOCUSAUTHENTICATOR_HPP

#include <iostream>
#include <fstream>
#include "../../Library/httplib.h"

class FocusAuthenticator {
private:
    std::unique_ptr<httplib::Client> _cli;
    std::string _token;
    std::string _uuid;
    bool _connected = false;
public:
    void Run();

    std::string GetUUID();

    bool GetConnectionStatus();

    std::string GetCurrentToken();

    bool Login(const std::string &email, const std::string &password);

    bool Disconnect();

    bool RenewToken();
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
