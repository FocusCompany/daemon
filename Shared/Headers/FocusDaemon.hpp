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
#include "FocusConfiguration.hpp"
#include "FocusUI.hpp"
#include "FocusEventEmitter.hpp"

class FocusDaemon {
private:
    std::shared_ptr<FocusAuthenticator> Authenticator = std::make_shared<FocusAuthenticator>();
    std::shared_ptr<FocusConfiguration> _config = nullptr;
    std::unique_ptr<FocusUI> FocusGUI = std::make_unique<FocusUI>();
    std::unique_ptr<FocusKeyLogger> KeyLogger = std::make_unique<FocusKeyLogger>();
    std::unique_ptr<FocusNetworkManager> NetworkManager = std::make_unique<FocusNetworkManager>();
    std::unique_ptr<FocusEventManager> EventManager = std::make_unique<FocusEventManager>();
    //std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::string _device_id = "";
    std::atomic<bool> _sigReceived = {false};
    std::atomic<bool> _isRunning = {false};
    std::string _configFileName = "";
    std::unique_ptr<std::thread> _daemonThread = nullptr;
    void RunDaemon();

public:
    virtual ~FocusDaemon();

    void Run(const std::string &configFileName, std::atomic<bool> &sigReceived);

    static void bootstrap(std::string const& platform_name);

    static constexpr auto version = FOCUS_VERSION;
};

#endif //FOCUS_CLIENT_FOCUSDAEMON_HPP
