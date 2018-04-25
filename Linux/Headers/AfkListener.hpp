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
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();

    void EventListener() const override final;

    void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const override final;

public:
    void Run() override final;
};


#endif //DAEMON_AFKLISTENER_HPP
