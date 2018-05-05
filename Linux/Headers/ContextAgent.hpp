//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP

#include "IContextAgent.hpp"
#include <memory>
#include "FocusEventEmitter.hpp"
#include <X11/Xlib.h>
#include <X11/Xmu/WinUtil.h>
#include <atomic>

class ContextAgent : public IContextAgent {
private:
    std::atomic<bool> _isRunning;
    std::atomic<bool> _sigReceived;
    Window _window;
    std::unique_ptr<Display, std::function<void(Display *)>> _display;
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter;

    void EventListener() override final;

    std::tuple<std::string, std::string> getWindowInfo();

    static int x11Errorhandler(Display *display, XErrorEvent *error);

public:
    void Run(std::atomic<bool> &sigReceived) override final;

    void OnContextChanged(const std::string &processName, const std::string &windowTitle) const override final;

    ContextAgent();

    virtual ~ContextAgent();
};

#endif //FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
