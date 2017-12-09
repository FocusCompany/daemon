//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include <iostream>

void FocusKeyLogger::Run()
{
	_keyLoggerThread = std::make_unique<std::thread>(std::bind(&FocusKeyLogger::RunKeyLogger, this));
}

void FocusKeyLogger::RunKeyLogger() {
	_eventListener->Register("OnWindowsContextChanged", [&](std::string clientId, Focus::Event &newContext) {
		PushKeyLog(newContext);
	});

	_contextAgent->Run(); //Block the current thread beacause msg loop windows (Remove after adding other components)
}

void FocusKeyLogger::PushKeyLog(Focus::Event& context) {
	_eventEmitter->Emit("FocusNetworkManager", context);
}
