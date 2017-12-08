//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "ContextAgent.hpp"

IContextAgent *contextAgent;

ContextAgent::ContextAgent() {
	contextAgent = this; //This is mendatory for the hook to be able to communicate with our appContext.
}

ContextAgent::~ContextAgent() {
	UnhookWinEvent(hEvent);
}

void ContextAgent::Run() {
	hEvent = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, WinEventProcCallback, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
	MSG msg;
	GetMessage(&msg, nullptr, NULL, NULL); // Windows message loop keepalive. This will block the current thread.
}

void ContextAgent::OnContextChanged(std::string &processName, std::string &windowTitle) {
	_eventEmitter->Emit("OnWindowsContextChanged", processName);
}

VOID CALLBACK ContextAgent::WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
	DWORD processId;

	char tmp[0xFF] = { 0 };
	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	GetModuleBaseName(hProcess, nullptr, tmp, 0xFF);
	std::string processName = std::string(tmp);
	GetWindowText(hwnd, tmp, 0xFF);
	std::string windowTitle = std::string(tmp);
	contextAgent->OnContextChanged(processName, windowTitle);
}