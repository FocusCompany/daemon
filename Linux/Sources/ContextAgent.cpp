//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <FocusSerializer.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <X11/Xutil.h>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"

bool _xerror = false;

int ContextAgent::x11Errorhandler(Display *display, XErrorEvent *error) {
    _xerror = true;
    spdlog::get("logger")->error("X11 Error");
    return 1;
}

std::tuple<std::string, std::string> ContextAgent::getWindowInfo() {
    int tmp;
    XGetInputFocus(_display, &_window, &tmp);
    if (!_xerror) {
        if (_window == None) {
            spdlog::get("logger")->error("No windows on focus");
        } else {
            Window parent = _window;
            Window root = None;
            Window *children;
            unsigned int nchild = 0;
            Status s1;
            while (parent != root) {
                _window = parent;
                s1 = XQueryTree(_display, _window, &root, &parent, &children, &nchild);
                if (s1)
                    XFree(children);
                if (_xerror) {
                    spdlog::get("logger")->error("Failing to find window name");
                    return std::make_tuple(std::string(), std::string());
                }
            }
            _window = XmuClientWindow(_display, _window);
            XTextProperty prop;
            Status s2;
            s2 = XGetWMName(_display, _window, &prop);
            if (!_xerror && s2) {
                int count = 0;
                int result;
                char **list = nullptr;
                result = XmbTextPropertyToTextList(_display, &prop, &list, &count);
                if (result == Success) {
                    std::string windowName(list[0]);
                    XFreeStringList(list);
                    Status s3;
                    XClassHint *classWindow;
                    classWindow = XAllocClassHint();
                    if (_xerror) {
                        spdlog::get("logger")->error("XAllocClassHint error");
                    }
                    s3 = XGetClassHint(_display, _window, classWindow);
                    if (_xerror || s3) {
                        std::string processName(classWindow->res_class);
                        XFree(classWindow->res_class);
                        XFree(classWindow->res_name);
                        XFree(classWindow);
                        return std::make_tuple(windowName, processName);
                    } else {
                        spdlog::get("logger")->error("XGetClassHint error");
                    }
                } else {
                    spdlog::get("logger")->error("XmbTextPropertyToTextList error");
                }
            } else {
                spdlog::get("logger")->error("XGetWMName error");
            }
        }
    }
    return std::make_tuple(std::string(), std::string());
}

void ContextAgent::Run(std::atomic<bool> &sigReceived) {
    _sigReceived = sigReceived.load();
    setlocale(LC_ALL, "");
    _display = XOpenDisplay(nullptr);
    if (_display == nullptr) {
        spdlog::get("logger")->error("Failed to connect to X Server");
    }
    if (_display != nullptr) {
        _eventListener = std::make_unique<std::thread>(std::bind(&ContextAgent::EventListener, this));
    }
}

void ContextAgent::EventListener() {
    std::string oldProcessName;
    std::string oldWindowsTitle;

    XSetErrorHandler(x11Errorhandler);

    while (_isRunning && !_sigReceived) {
        std::tuple<std::string, std::string> info = getWindowInfo();
        std::string windowsTitle = std::get<0>(info);
        std::string processName = std::get<1>(info);
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

ContextAgent::~ContextAgent() {
    _isRunning = false;
    _eventListener->join();
    XCloseDisplay(_display);
}

ContextAgent::ContextAgent() {
    _isRunning = true;
}
