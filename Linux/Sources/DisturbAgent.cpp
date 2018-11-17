//
// Created by Etienne Pasteur on 15/11/2018.
//

#include "DisturbAgent.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <FocusSerializer.hpp>
#include "FocusContextEventPayload.pb.h"
#include <spdlog_pragma.hpp>
#include <array>
#include <BundleLocation.hpp>
#include "json_pragma.hpp"

void DisturbAgent::Run() {
    std::string cmd = "exec bash " + _bashScriptLocation + " ";

    _disturbAgentListener->RegisterMessage("DisturbAgent", [this, cmd](const std::string &data) {
        auto j = nlohmann::json::parse(data);
        if (j.find("action") != j.end()) {
            std::string cmdArg = cmd;
            if (j["action"] == "dnd") {
                cmdArg += "turn_on";
            } else if (j["action"] == "stop_dnd") {
                cmdArg += "turn_off";
            } else if (j["action"] == "get_state") {
                cmdArg += "get_state";
            }
            std::array<char, 256> buffer{};
            std::string result;
            auto process = popen(cmdArg.c_str(), "r");
            if (process == nullptr) {
                spdlog::get("logger")->critical("Unable to invoke BashScript. Aborting.");
                std::exit(1);
            }
            std::shared_ptr<FILE> pipe(process, pclose);
            if (!pipe) {
                spdlog::get("logger")->error("Failed to retrieve current state");
            } else {
                while (!feof(pipe.get())) {
                    if (fgets(buffer.data(), 256, pipe.get()) != nullptr)
                        result += buffer.data();
                }
                if (result == "ok") {
                    _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"toggle_dnd_button\"}");
                } else if (result == "on") {
                    _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"dnd_button\", \"data\": {\"status\": \"on\"}}");
                } else if (result == "off") {
                    _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"dnd_button\", \"data\": {\"status\": \"off\"}}");
                }
            }
        }
    });
}

DisturbAgent::DisturbAgent() : _eventEmitter(std::make_unique<FocusEventEmitter>()),
                               _bashScriptLocation() {
    _bashScriptLocation = getExecPath() + "toggleDoNotDisturb.sh";
}
