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
#include "IKeyListener.hpp"
#include "KeyListener.hpp"
#include "IMouseListener.hpp"
#include "MouseListener.hpp"

class FocusKeyLogger {
private:
    std::unique_ptr<std::thread> _keyLoggerThread;
    std::unique_ptr<IContextAgent> _contextAgent = std::unique_ptr<IContextAgent>(std::make_unique<ContextAgent>());
    std::unique_ptr<IMouseListener> _mouseListener = std::unique_ptr<IMouseListener>(std::make_unique<MouseListener>());
    std::unique_ptr<IKeyListener> _keyListener = std::unique_ptr<IKeyListener>(std::make_unique<KeyListener>());
    std::unique_ptr<FocusEventListener<Focus::Event>> _eventListener = std::make_unique<FocusEventListener<Focus::Event>>();
    std::unique_ptr<FocusEventListener<const std::string&>> _messageListener = std::make_unique<FocusEventListener<const std::string &>>();
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::vector<Focus::Event> _events;
    std::string _user_uuid;

    void AddEvent(const Focus::Event &event);

    void RunKeyLogger();

public:
    void Run(const std::string &user_uuid);
};

#endif //FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
