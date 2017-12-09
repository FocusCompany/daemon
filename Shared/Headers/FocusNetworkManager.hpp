//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
#define FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP

#include <thread>
#include "FocusEventListener.hpp"

class FocusNetworkManager {
private:
	int _socket;
	std::unique_ptr<std::thread> _networkManagerThread;
	std::unique_ptr<FocusEventListener<Focus::Event>> _eventListener = std::make_unique<FocusEventListener<Focus::Event>>();
	void RunReceive();
public:
	FocusNetworkManager();
	virtual ~FocusNetworkManager();
	void Run();
};

#endif //FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
