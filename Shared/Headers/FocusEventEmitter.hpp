//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP

#include <string>

class FocusEventEmitter {
private:
    int _socketPUB;

public:
    FocusEventEmitter();

    void Emit(std::string destinator, std::string &payload);

    void RouteToModules(std::string &payload);
};


#endif //FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP