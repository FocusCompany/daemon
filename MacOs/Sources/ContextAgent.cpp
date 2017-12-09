//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <FocusSerializer.hpp>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"


ContextAgent::ContextAgent() {

}

ContextAgent::~ContextAgent() {

}

void ContextAgent::Run() {
    //TODO: Implementing ContextAgent
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void ContextAgent::OnContextChanged(const std::string &processName, const std::string &windowTitle) const {
    Focus::ContextEventPayload context;
    context.set_processname(processName);
    context.set_windowname(windowTitle);

    Focus::Event event = FocusSerializer::CreateEventFromContext("OnWindowsContextChanged", context);

    _eventEmitter->Emit("OnWindowsContextChanged", event);
}