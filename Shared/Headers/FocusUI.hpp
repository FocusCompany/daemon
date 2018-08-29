//
// Created by Etienne Pasteur on 17/05/2018.
//

#ifndef DAEMON_FOCUSUI_HPP
#define DAEMON_FOCUSUI_HPP

#include <thread>
#include <atomic>
#include <unordered_map>
#include "FocusEventListener.hpp"
#include "FocusEventEmitter.hpp"

class FocusUI {
private:
    std::unique_ptr<FocusEventEmitter> _eventEmitter;
    std::unique_ptr<FocusEventListener<const std::string &>> _messageListener;
    std::unordered_map<std::string, std::function<void(const std::string &)>> _command;
public:
    FocusUI();

    void Run();

    void HandleCommand(const std::string &data);
};


#endif //DAEMON_FOCUSUI_HPP
