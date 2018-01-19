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
public:
    void Run();
    bool GetConnectionStatus();
    std::string GetCurrentToken();
    bool Login(std::string &, std::string &);
    bool Disconnect();
    bool RenewToken();
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
