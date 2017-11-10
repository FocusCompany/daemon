//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP

#include <IFocusEventEmitter.hpp>

class FocusEventEmitter : public IFocusEventEmitter {
private:
	int _socketPUB;

public:
	FocusEventEmitter();

	void Emit(std::string destinator, std::string &payload) override final;

	void RouteToModules(std::string &payload) override final;
};


#endif //FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP