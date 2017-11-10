//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_IFOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_IFOCUSEVENTEMITTER_HPP

#include <string>

class IFocusEventEmitter {
public:
	virtual void RouteToModules(std::string &payload) = 0;
	virtual void Emit(std::string destinator, std::string &payload) = 0;
};


#endif //FOCUS_CLIENT_IFOCUSEVENTEMITTER_HPP