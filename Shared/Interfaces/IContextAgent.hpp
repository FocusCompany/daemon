//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP

#include <atomic>
#include <string>

class IContextAgent {
public:
    virtual void Run(std::atomic<bool> &sigReceived) = 0;

	virtual void OnContextChanged(const std::string &processName, const std::string &windowTitle) const = 0;

	virtual ~IContextAgent() {}

private:
    virtual void EventListener() = 0;
};

#endif //FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP