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
    _disturbAgentListener->RegisterMessage("DisturbAgent", [this, cmd](const std::string &data) {
        auto j = nlohmann::json::parse(data);
        if (j.find("action") != j.end()) {
            _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"dnd_button\", \"data\": {\"status\": \"not_allowed\"}}");
        }
    });
}