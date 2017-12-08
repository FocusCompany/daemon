//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "ContextAgent.hpp"

IContextAgent *contextAgent;

ContextAgent::ContextAgent() {
    contextAgent = this; //This is mendatory for the hook to be able to communicate with our appContext.
}

ContextAgent::~ContextAgent() {

}

void ContextAgent::Run() {
    std::string windowTitle = "Hello World";
    std::string processName;

    while (true) {
        getline(std::cin, processName);
        OnContextChanged(processName, windowTitle);
    }
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void ContextAgent::OnContextChanged(std::string &processName, std::string &windowTitle) {
    _eventEmitter->Emit("OnWindowsContextChanged", processName);
}