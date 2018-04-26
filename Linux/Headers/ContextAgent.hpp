//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP

#include "IContextAgent.hpp"
#include <memory>
#include "FocusEventEmitter.hpp"

class ContextAgent : public IContextAgent {
private:
    std::unique_ptr<std::thread> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();

    void EventListener() override final;


public:
    void Run() override final;

	void OnContextChanged(const std::string &processName, const std::string &windowTitle) const override final;
};

#endif //FOCUS_CLIENT_WINDOWSCONTEXTAGENT_HPP
