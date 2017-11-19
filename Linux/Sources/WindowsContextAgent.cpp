//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include "WindowsContextAgent.hpp"

IWindowsContextAgent *windowsContextAgent;

WindowsContextAgent::WindowsContextAgent() {
	windowsContextAgent = this; //This is mendatory for the hook to be able to communicate with our appContext.
}

WindowsContextAgent::~WindowsContextAgent() {
}

void WindowsContextAgent::Run() {
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void WindowsContextAgent::OnContextChanged(std::string &processName, std::string &windowTitle) {
    _eventEmitter->Emit("OnWindowsContextChanged", processName);
}