//
// Created by Etienne Pasteur on 17/05/2018.
//

#ifndef DAEMON_FOCUSUI_HPP
#define DAEMON_FOCUSUI_HPP

#include <thread>
#include <atomic>
#include "FocusEventListener.hpp"
#include "FocusEventEmitter.hpp"

class FocusUI {
private:
    std::unique_ptr<FocusEventListener<const std::string &>> _messageListener;

public:
    FocusUI();

    void Run();

    void HandleCommand(const std::string &data);
};


#endif //DAEMON_FOCUSUI_HPP
