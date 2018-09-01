//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <FocusSerializer.hpp>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"
#include <spdlog_pragma.hpp>
#include <array>
#include <BundleLocation.hpp>

void ContextAgent::Run(std::atomic<bool> &sigReceived) {
    _sigReceived = sigReceived.load();
    _isRunning = true;
    _eventListener = std::make_unique<std::thread>(std::bind(&ContextAgent::EventListener, this));
}

void ContextAgent::EventListener() {
    std::string cmd = "osascript \"" + _appleScriptLocation + "\"";
    std::string oldProcessName;
    std::string oldWindowsTitle;
    while (_isRunning && !_sigReceived) {
        std::array<char, 256> buffer{};
        std::string result;
        auto process = popen(cmd.c_str(), "r");
        if (process == nullptr) {
            spdlog::get("logger")->critical("Unable to invoke AppleScript. Aborting.");
            std::exit(1);
        }
        std::shared_ptr<FILE> pipe(process, pclose);
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
    if (_isRunning) {
        _isRunning = false;
        _eventListener->join();
    }
}

ContextAgent::ContextAgent() : _eventListener(),
                               _isRunning(false),
                               _sigReceived(false),
                               _eventEmitter(std::make_unique<FocusEventEmitter>()),
                               _appleScriptLocation() {

    _appleScriptLocation = getExecPath() + "printAppTitle.scpt";
}
