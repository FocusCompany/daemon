//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP

#include <string>
#include <FocusEvent.pb.h>

class FocusEventEmitter {
private:
    int _socketPUB;

public:
    FocusEventEmitter();

    void Emit(std::string dest, Focus::Event &payload);

    void RouteToModules(Focus::Event &payload);
};


#endif //FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP