//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP

#include <Windows.h>
#include <Psapi.h>
#include <functional>
#include <iostream>
#include "IWindowsContextAgent.hpp"
#include <memory>
#include "IFocusEventEmitter.hpp"
#include "FocusEventEmitter.hpp"

class WindowsContextAgent : public IWindowsContextAgent {

public:
	WindowsContextAgent();

	~WindowsContextAgent();

	void Run() override final;

	void OnContextChanged(std::string &processName, std::string &windowTitle) override final;

	static VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

private:
	std::unique_ptr<IFocusEventEmitter> _eventEmitter = std::unique_ptr<IFocusEventEmitter>(std::make_unique<FocusEventEmitter>());
	HWINEVENTHOOK hEvent;
};

#endif //FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
