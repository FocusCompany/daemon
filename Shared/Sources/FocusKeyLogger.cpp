//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>

void FocusKeyLogger::Run() {
    _keyLoggerThread = std::make_unique<std::thread>(std::bind(&FocusKeyLogger::RunKeyLogger, this));
}

void FocusKeyLogger::RunKeyLogger() const {
    _eventListener->Register("OnWindowsContextChanged", [this](Focus::Event &newContext) {
        PushKeyLog(newContext);
    });

    _contextAgent->Run();
}

void FocusKeyLogger::PushKeyLog(const Focus::Event &context) const{
    _eventEmitter->Emit("FocusNetworkManager", context);
}
