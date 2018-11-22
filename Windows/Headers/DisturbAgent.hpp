//
// Created by Etienne Pasteur on 15/11/2018.
//

#ifndef DAEMON_DISTURBAGENT_HPP
#define DAEMON_DISTURBAGENT_HPP


#include "IDisturbAgent.hpp"
#include <memory>
#include <thread>
#include <FocusEventListener.hpp>
#include "FocusEventEmitter.hpp"

class DisturbAgent : public IDisturbAgent {
private:
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::unique_ptr<FocusEventListener<const std::string &>> _disturbAgentListener = std::make_unique<FocusEventListener<const std::string &>>();

public:
    void Run() override final;

    virtual ~DisturbAgent() {}
};


#endif //DAEMON_DISTURBAGENT_HPP
