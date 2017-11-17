//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP
#define FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP

#include <string>
#include <functional>
#include <IFocusEventListener.hpp>
#include <thread>

class FocusEventListener : public IFocusEventListener {
private:
	std::function<void(std::string clientId, std::string payload)> _onMessage;
	std::unique_ptr<std::thread> _eventListenerThread;
	int _socketSUB;
	static void RunReceive(int socketSUB, std::function<void(std::string clientId, std::string payload)> *onMessage, bool shouldUnpack = false);
public:
	FocusEventListener();
	void Register(std::string payloadType, std::function<void(std::string clientId, std::string payload)> onMessage) override final;
	void RegisterNoUnpack(std::string payloadType, std::function<void(std::string clientId, std::string payload)> onMessage) override final;
};


#endif //FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP