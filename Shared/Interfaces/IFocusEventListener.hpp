//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_IFOCUSEVENTLISTENER_HPP
#define FOCUS_CLIENT_IFOCUSEVENTLISTENER_HPP

#include <string>
#include <functional>

class IFocusEventListener {
public:
	virtual void Register(std::string payloadType, std::function<void(std::string clientId, std::string payload)> onMessage) = 0;
	virtual void RegisterNoUnpack(std::string payloadType, std::function<void(std::string clientId, std::string payload )> onMessage) = 0;
};


#endif //FOCUS_CLIENT_IFOCUSEVENTLISTENER_HPP