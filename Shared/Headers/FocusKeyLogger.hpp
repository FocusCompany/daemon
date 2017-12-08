//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
#define FOCUS_CLIENT_FOCUSKEYLOGGER_HPP

#include <thread>
#include "IContextAgent.hpp"
#include "ContextAgent.hpp"
#include "FocusEventListener.hpp"
#include "FocusEventEmitter.hpp"

class FocusKeyLogger {
private:
	std::unique_ptr<std::thread> _keyLoggerThread;
	std::unique_ptr<IContextAgent> _contextAgent = std::unique_ptr<IContextAgent>(std::make_unique<ContextAgent>());
	std::unique_ptr<FocusEventListener> _eventListener = std::make_unique<FocusEventListener>();
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
	void PushKeyLog(std::string &context);
	void RunKeyLogger();

public:
	void Run();
};

#endif //FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
