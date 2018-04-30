//
// Created by Etienne Pasteur on 25/04/2018.
//

#ifndef DAEMON_AFKLISTENER_HPP
#define DAEMON_AFKLISTENER_HPP

#include <IAfkListener.hpp>
#include <thread>
#include <FocusEventEmitter.hpp>

class AfkListener : public IAfkListener {
private:
    int _triggerAfkInSecond;
    std::unique_ptr<std::thread> _eventListener;
    std::atomic<bool> _isRunning;
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();

    void EventListener() override final;

    void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const override final;

public:
    void Run(int triggerAfkInSecond) override final;

    AfkListener();

    virtual ~AfkListener();
};


#endif //DAEMON_AFKLISTENER_HPP
