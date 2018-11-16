//
// Created by Etienne Pasteur on 15/11/2018.
//

#ifndef DAEMON_IDISTURBAGENT_HPP
#define DAEMON_IDISTURBAGENT_HPP

class IDisturbAgent {
public:
    virtual void Run() = 0;

    virtual ~IDisturbAgent() {}
};

#endif //DAEMON_IDISTURBAGENT_HPP
