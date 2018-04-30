//
// Created by Etienne Pasteur on 25/04/2018.
//

#ifndef DAEMON_AFKLISTENER_HPP
#define DAEMON_AFKLISTENER_HPP

#include <IAfkListener.hpp>
#include <thread>
#include <FocusEventEmitter.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <atomic>

class AfkListener : public IAfkListener {
private:
    Display *_display;
    int _triggerAfkInSecond;
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::atomic<bool> _isRunning;

    void EventListener() override final;

    void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const override final;

public:
    void Run(int triggerAfkInSecond) override final;

    AfkListener();

    virtual ~AfkListener();
};


#endif //DAEMON_AFKLISTENER_HPP
