//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <FocusSerializer.hpp>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"
#include <spdlog/spdlog.h>
#include <array>

void ContextAgent::Run(std::atomic<bool> &sigReceived) {
    _sigReceived = sigReceived.load();
    _eventListener = std::make_unique<std::thread>(std::bind(&ContextAgent::EventListener, this));
}

void ContextAgent::EventListener() {
    std::string cmd = "osascript ./printAppTitle.scpt";
    std::string oldProcessName;
    std::string oldWindowsTitle;
    while (_isRunning && !_sigReceived) {
        std::array<char, 256> buffer{};
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
        if (!pipe) {
            spdlog::get("logger")->error("Failed to retrieve current AppName");
        } else {
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 256, pipe.get()) != nullptr)
                    result += buffer.data();
            }
            std::string processName = result.substr(1, result.find("\",\"") - 1);
            std::string windowsTitle = result.substr(result.find("\",\"") + 3, result.size() - (result.find("\",\"") + 3) - 2);
            if (oldProcessName != processName || oldWindowsTitle != windowsTitle) {
                oldProcessName = processName;
                oldWindowsTitle = windowsTitle;
                OnContextChanged(processName, windowsTitle);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void ContextAgent::OnContextChanged(const std::string &processName, const std::string &windowTitle) const {
    Focus::ContextEventPayload context;
    context.set_processname(processName);
    context.set_windowname(windowTitle);

    Focus::Event event = FocusSerializer::CreateEventFromContext("ContextChanged", context);

    _eventEmitter->Emit("NewEvent", event);
}

ContextAgent::~ContextAgent() {
    _isRunning = false;
    _eventListener->join();
}

ContextAgent::ContextAgent() {
    _isRunning = true;
}
