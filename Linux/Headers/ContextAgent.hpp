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

class ContextAgent : public IContextAgent {
private:
    Display *_display;
    Window _window;
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();

    void EventListener() override final;

    std::tuple<std::string, std::string> getWindowInfo();

    static int x11Errorhandler(Display *display, XErrorEvent *error);

public:
    void Run() override final;

    void OnContextChanged(const std::string &processName, const std::string &windowTitle) const override final;
};

#endif //FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
