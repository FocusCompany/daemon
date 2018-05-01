//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include <FocusEnvelope.pb.h>
#include <spdlog/spdlog.h>
#include "FocusSerializer.hpp"

void FocusKeyLogger::Run(std::shared_ptr<FocusAuthenticator> &authenticator, std::shared_ptr<FocusConfiguration> &config, std::atomic<bool> &sigReceived) {
    _authenticator = authenticator;

    _eventListener->Register("NewEvent", [this](Focus::Event &newContext) {
        AddEvent(newContext);
    });

    _messageListener->RegisterMessage("FocusSendDataToBackend", [this](const std::string &msg) {
        //TODO: Ensure is thread safe to clear the vector here
        spdlog::get("console")->info("Clear events cached");
        _events.clear();
    });

    _contextAgent->Run(sigReceived);
    _afkListener->Run(std::stoi(config->getTriggerAfk()), sigReceived);
}

void FocusKeyLogger::AddEvent(const Focus::Event &ev) {
    _events.push_back(ev);
    spdlog::get("console")->info("Adding new event to cache");
    if (_events.size() > 5) {
        Focus::Envelope envelope;

        envelope.set_jwt(_authenticator->GetToken());
        envelope.set_deviceid(_authenticator->GetDeviceId());
        google::protobuf::RepeatedPtrField<Focus::Event> data(_events.begin(), _events.end());
        envelope.mutable_events()->Swap(&data);

        _eventEmitter->EmitEnvelope("FocusNetworkManager", envelope);
    }
}
