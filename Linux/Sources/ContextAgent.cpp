//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include "ContextAgent.hpp"

IContextAgent *contextAgent;

ContextAgent::ContextAgent() {
    contextAgent = this; //This is mendatory for the hook to be able to communicate with our appContext.
}

ContextAgent::~ContextAgent() {
}

void LinuxContextAgent::Run() {
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void LinuxContextAgent::OnContextChanged(std::string &processName, std::string &windowTitle) {
    _eventEmitter->Emit("OnWindowsContextChanged", processName);
}