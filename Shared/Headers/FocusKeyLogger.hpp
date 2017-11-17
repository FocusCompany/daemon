//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
#define FOCUS_CLIENT_FOCUSKEYLOGGER_HPP

#include <IFocusKeyLogger.hpp>
#include <thread>
#include "IWindowsContextAgent.hpp"
#include "WindowsContextAgent.hpp"
#include "IFocusEventListener.hpp"
#include "FocusEventListener.hpp"
#include "IFocusEventEmitter.hpp"
#include "FocusEventEmitter.hpp"


class FocusKeyLogger : public IFocusKeyLogger {
private:
	std::unique_ptr<std::thread> _keyLoggerThread;
	std::unique_ptr<IWindowsContextAgent> ContextAgent = std::unique_ptr<IWindowsContextAgent>(std::make_unique<WindowsContextAgent>());
	std::unique_ptr<IFocusEventListener> _eventListener = std::unique_ptr<IFocusEventListener>(std::make_unique<FocusEventListener>());
	std::unique_ptr<IFocusEventEmitter> _eventEmitter = std::unique_ptr<IFocusEventEmitter>(std::make_unique<FocusEventEmitter>());
	void PushKeyLog(std::string &context);
	void RunKeyLogger();

public:
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
