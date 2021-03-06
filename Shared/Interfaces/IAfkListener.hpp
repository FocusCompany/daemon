//
// Created by Etienne Pasteur on 25/04/2018.
//

#ifndef DAEMON_IAFKLISTENER_HPP
#define DAEMON_IAFKLISTENER_HPP

#include <atomic>
#include <chrono>

class IAfkListener {
public:
    virtual void Run(int triggerAfkInSecond, std::atomic<bool> &sigReceived) = 0;

    virtual ~IAfkListener() {}

private:
    virtual void EventListener() = 0;

    virtual void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const = 0;
};


#endif //DAEMON_IAFKLISTENER_HPP
