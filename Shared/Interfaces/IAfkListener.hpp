//
// Created by Etienne Pasteur on 25/04/2018.
//

#ifndef DAEMON_IAFKLISTENER_HPP
#define DAEMON_IAFKLISTENER_HPP


#include <chrono>

class IAfkListener {
public:
    virtual void Run() = 0;

private:
    virtual void EventListener() const = 0;

    virtual void OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const = 0;
};


#endif //DAEMON_IAFKLISTENER_HPP