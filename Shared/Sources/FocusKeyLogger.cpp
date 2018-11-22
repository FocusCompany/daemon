//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include <FocusEnvelope.pb.h>
#include <spdlog_pragma.hpp>
#include "FocusSerializer.hpp"
#include "json_pragma.hpp"

void FocusKeyLogger::Run(std::shared_ptr<FocusAuthenticator> &authenticator, std::shared_ptr<FocusConfiguration> &config, std::atomic<bool> &sigReceived) {
    _authenticator = authenticator;

    _eventListener->Register("NewEvent", [this](Focus::Event &newContext) {
        if (_watching) {
            AddEvent(newContext);
        } else {
            spdlog::get("console")->info("New event catch but recording is turned off");
        }
    });

    _keyLoggerListener->RegisterMessage("Keylogger", [this](const std::string &data) {
        auto j = nlohmann::json::parse(data);
        if (j.find("action") != j.end()) {
            if (j["action"] == "watch") {
                _watching = true;
                _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"toggle_watch_button\"}");
            } else if (j["action"] == "stop_watching") {
                _watching = false;
                _eventEmitter->EmitMessage("WebviewAction", "{\"action\": \"toggle_watch_button\"}");
            }
        }
    });

    _messageListener->RegisterMessage("FocusSendDataToBackend", [this](const std::string &) {
        //TODO: Ensure is thread safe to clear the vector here
        spdlog::get("console")->info("Clear events cached");
        _events.clear();
    });

    _disturbAgent->Run();
    _contextAgent->Run(sigReceived);
    _afkListener->Run(std::stoi(config->getTriggerAfk()), sigReceived);
}

void FocusKeyLogger::AddEvent(const Focus::Event &ev) {
    if (!_authenticator->GetDeviceId().empty()) {
        _events.push_back(ev);
        spdlog::get("console")->info("Adding new event of type {0} to cache", ev.payloadtype());
        spdlog::get("logger")->flush();
        if (_events.size() > 5) {
            Focus::Envelope envelope;

            envelope.set_jwt(_authenticator->GetToken());
            envelope.set_deviceid(_authenticator->GetDeviceId());
            google::protobuf::RepeatedPtrField<Focus::Event> data(_events.begin(), _events.end());
            envelope.mutable_events()->Swap(&data);

            _eventEmitter->EmitEnvelope("FocusNetworkManager", envelope);
        }
    } else {
        spdlog::get("console")->info("Can't add new event of type {0} to cache", ev.payloadtype());
    }
}