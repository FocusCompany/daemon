//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSDAEMON_HPP
#define FOCUS_CLIENT_FOCUSDAEMON_HPP

#include <memory>
#include "FocusKeyLogger.hpp"
#include "FocusNetworkManager.hpp"
#include "FocusKeyLogger.hpp"
#include "FocusEventManager.hpp"
#include "FocusAuthenticator.hpp"

class FocusDaemon {
private:
    std::unique_ptr<FocusAuthenticator> Authenticator = std::make_unique<FocusAuthenticator>();
    std::unique_ptr<FocusKeyLogger> KeyLogger = std::make_unique<FocusKeyLogger>();
    std::unique_ptr<FocusNetworkManager> NetworkManager = std::make_unique<FocusNetworkManager>();
    std::unique_ptr<FocusEventManager> EventManager = std::make_unique<FocusEventManager>();
    std::string _user_uuid;
public:
    void Run();
};

#endif //FOCUS_CLIENT_FOCUSDAEMON_HPP
