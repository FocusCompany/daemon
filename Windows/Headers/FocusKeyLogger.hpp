//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
#define FOCUS_CLIENT_FOCUSKEYLOGGER_HPP

#include <IFocusKeyLogger.hpp>
#include <thread>
#include "IWindowsContextAgent.hpp"
#include "WindowsContextAgent.hpp"

class FocusKeyLogger : public IFocusKeyLogger {
private:
	std::unique_ptr<std::thread> _keyLoggerThread;
	std::unique_ptr<IWindowsContextAgent> ContextAgent = std::unique_ptr<IWindowsContextAgent>(std::make_unique<WindowsContextAgent>());

	void RunKeyLogger();
public:
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSKEYLOGGER_HPP
