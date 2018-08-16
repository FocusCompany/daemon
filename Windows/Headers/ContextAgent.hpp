//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP

#include <Windows.h>
#include <Psapi.h>
#include <functional>
#include <iostream>
#include "IContextAgent.hpp"
#include <memory>
#include "FocusEventEmitter.hpp"
#include <thread>
#include <atomic>

class ContextAgent : public IContextAgent {
private:
    std::atomic<bool> _isRunning;
    std::atomic<bool> _sigReceived;
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter;

    void EventListener() override final;

public:
    ContextAgent();

    ~ContextAgent();

    void Run(std::atomic<bool> &sigReceived) override final;

    void OnContextChanged(const std::string &processName, const std::string &windowTitle) const override final;
};

#endif //FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
