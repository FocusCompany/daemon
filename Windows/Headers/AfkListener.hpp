//
// Created by Etienne Pasteur on 25/04/2018.
//

#ifndef DAEMON_AFKLISTENER_HPP
#define DAEMON_AFKLISTENER_HPP

#include <IAfkListener.hpp>
#include <thread>
#include <FocusEventEmitter.hpp>
#include <atomic>

class AfkListener : public IAfkListener {
private:
    int _triggerAfkInSecond;
    std::unique_ptr<std::thread> _eventListener;
    std::atomic<bool> _isRunning;
    std::atomic<bool> _sigReceived;
    std::unique_ptr<FocusEventEmitter> _eventEmitter;

    void EventListener() override final;

    void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const override final;

public:
    void Run(int triggerAfkInSecond, std::atomic<bool> &sigReceived) override final;

    AfkListener();

    virtual ~AfkListener();
};


#endif //DAEMON_AFKLISTENER_HPP
