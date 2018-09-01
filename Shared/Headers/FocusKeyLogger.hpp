//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
#define FOCUS_CLIENT_FOCUSKEYLOGGER_HPP

#include <thread>
#include "IContextAgent.hpp"
#include "ContextAgent.hpp"
#include "FocusEventListener.hpp"
#include "FocusEventEmitter.hpp"
#include <FocusContextEventPayload.pb.h>
#include <IAfkListener.hpp>
#include <AfkListener.hpp>
#include "FocusAuthenticator.hpp"

class FocusKeyLogger {
private:
    std::shared_ptr<FocusAuthenticator> _authenticator = nullptr;
    std::unique_ptr<IContextAgent> _contextAgent = std::unique_ptr<IContextAgent>(std::make_unique<ContextAgent>());
    std::unique_ptr<IAfkListener> _afkListener = std::unique_ptr<IAfkListener>(std::make_unique<AfkListener>());
    std::unique_ptr<FocusEventListener<Focus::Event>> _eventListener = std::make_unique<FocusEventListener<Focus::Event>>();
    std::unique_ptr<FocusEventListener<const std::string &>> _messageListener = std::make_unique<FocusEventListener<const std::string &>>();
    std::unique_ptr<FocusEventListener<const std::string &>> _keyLoggerListener = std::make_unique<FocusEventListener<const std::string &>>();
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::vector<Focus::Event> _events = std::vector<Focus::Event>();
    std::atomic<bool> _watching = {false};

    void AddEvent(const Focus::Event &event);

public:
    void Run(std::shared_ptr<FocusAuthenticator> &authenticator, std::shared_ptr<FocusConfiguration> &config, std::atomic<bool> &sigReceived);
};

#endif //FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
