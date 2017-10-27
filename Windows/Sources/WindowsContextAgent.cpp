//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "WindowsContextAgent.hpp"

WindowsContextAgent::WindowsContextAgent() {
	windowsContextAgent = this; //This is mendatory for the hook to be able to communicate with our appContext.
}

WindowsContextAgent::~WindowsContextAgent() {
	UnhookWinEvent(hEvent);
}

void WindowsContextAgent::Run() {
	std::cout << "SetWinEventHook" << std::endl;
	hEvent = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, WinEventProcCallback, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
	MSG msg;
	GetMessage(&msg, nullptr, NULL, NULL); // Windows message loop keepalive. This will block the current thread.
}

void WindowsContextAgent::OnContextChanged(std::string &processName, std::string &windowTitle) {
	std::cout << "Process Name : " << processName << std::endl;
	std::cout << "Window Title : " << windowTitle << std::endl;
}

VOID CALLBACK WindowsContextAgent::WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
	DWORD processId;

	std::cout << "I'm in the callback" << std::endl;

	char tmp[0xFF] = { 0 };
	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	GetModuleBaseName(hProcess, nullptr, tmp, 0xFF);
	std::string processName = std::string(tmp);
	GetWindowText(hwnd, tmp, 0xFF);
	std::string windowTitle = std::string(tmp);
	windowsContextAgent->OnContextChanged(processName, windowTitle);
}