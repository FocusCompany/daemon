//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "ContextAgent.hpp"
#include "FocusSerializer.hpp"
#include "FocusContextEventPayload.pb.h"


ContextAgent::ContextAgent() : _isRunning(false),
                               _sigReceived(false),
                               _eventListener(),
                               _eventEmitter(std::make_unique<FocusEventEmitter>()) {}

ContextAgent::~ContextAgent() {
    if (_isRunning) {
        _isRunning = false;
        _eventListener->detach();
    }
}

void ContextAgent::Run(std::atomic<bool> &sigReceived) {
    _sigReceived = sigReceived.load();
    _isRunning = true;
    _eventListener = std::make_unique<std::thread>(std::bind(&ContextAgent::EventListener, this));
}

void ContextAgent::EventListener() {
    std::string oldProcessName;
    std::string oldWindowsTitle;
    while (_isRunning && !_sigReceived) {
        HWND hwnd = GetForegroundWindow();
        DWORD processId = GetProcessId(hwnd);
        char tmp[0xFF] = {0};
        GetWindowThreadProcessId(hwnd, &processId);
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
        GetProcessImageFileName(hProcess, tmp, 0xFF);
        std::string processName = std::string(tmp);
        processName = processName.substr(processName.find_last_of("/\\") + 1);
        GetWindowText(hwnd, tmp, 0xFF);
        std::string windowsTitle = std::string(tmp);
        if (oldProcessName != processName || oldWindowsTitle != windowsTitle) {
            oldProcessName = processName;
            oldWindowsTitle = windowsTitle;
            OnContextChanged(processName, windowsTitle);
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void ContextAgent::OnContextChanged(const std::string &processName, const std::string &windowTitle) const {
    Focus::ContextEventPayload context;
    context.set_processname(processName);
    context.set_windowname(windowTitle);

    Focus::Event event = FocusSerializer::CreateEventFromContext("ContextChanged", context);

    _eventEmitter->Emit("NewEvent", event);
}
