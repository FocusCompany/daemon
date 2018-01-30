//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include <FocusEnvelope.pb.h>
#include <spdlog/spdlog.h>
#include "FocusKeyEventPayload.pb.h"
#include "FocusSerializer.hpp"

// FOCUS KEYLOGGER
// They are 3 types of events :
//	- "ContextChanged" -> Triggered when users change his active window. Contain processName and windowName.
//	- "KeyPayload" -> Triggered when users change his active window. Contain plain text key log.
//	- "MouseEvent" -> Triggered when users click with his mouse. Contain coordinate (x, y) and the button pressed.

void FocusKeyLogger::Run(const std::string &user_uuid) {
    spdlog::get("logger")->info("FocusKeyLogger is running");
    _user_uuid = user_uuid;
    _keyLoggerThread = std::make_unique<std::thread>(std::bind(&FocusKeyLogger::RunKeyLogger, this));
}

void FocusKeyLogger::RunKeyLogger() {
    _eventListener->Register("NewEvent", [this](Focus::Event &newContext) {
        AddEvent(newContext);
    });
    _messageListener->RegisterMessage("FocusSendDataToBackend", [this](const std::string &msg) {
        //TODO: Ensure is thread safe to clear the vector here
        spdlog::get("console")->info("Clear events cached");
        _events.clear();
    });

    _contextAgent->Run();
    _mouseListener->Run();
    _keyListener->Run(); //This will block current thread (on windows).
}

void FocusKeyLogger::AddEvent(const Focus::Event &ev) {
    _events.push_back(ev);
    spdlog::get("console")->info("Adding new event to cache");

    if (ev.payloadtype() == "ContextChanged") {
        Focus::KeyEventPayload keyPayload;
        std::string tmpStr = _keyListener->Flush();
        if (!tmpStr.empty()) {
            keyPayload.set_plaintextkeylog(tmpStr);
            Focus::Event tmpEvent = FocusSerializer::CreateEventFromContext("KeyPayload", keyPayload);
            _events.push_back(tmpEvent);
            spdlog::get("console")->info("Adding new event to cache");
        }
    }

    if (_events.size() > 5) {
        Focus::Envelope envelope;

        envelope.set_clientid(_user_uuid);
        google::protobuf::RepeatedPtrField<Focus::Event> data(_events.begin(), _events.end());
        envelope.mutable_events()->Swap(&data);

        _eventEmitter->EmitEnvelope("FocusNetworkManager", envelope);
    }
}
