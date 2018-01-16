//
// Created by Etienne Pasteur on 16/12/2017.
//

#ifndef DAEMON_FOCUSAUTHENTICATOR_HPP
#define DAEMON_FOCUSAUTHENTICATOR_HPP

#include <iostream>

class FocusAuthenticator {
private:
    std::string _token;
public:
    void Run();
    bool GetConnectionStatus();
    std::string GetCurrentToken();
    bool Connect(std::string &, std::string &);
    bool Disconnect();
    bool RenewToken();
    bool Register(std::string &, std::string &, std::string &, std::string &);
};


#endif //DAEMON_FOCUSAUTHENTICATOR_HPP
