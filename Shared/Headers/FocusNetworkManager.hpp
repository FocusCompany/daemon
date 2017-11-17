//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
#define FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP

#include <IFocusNetworkManager.hpp>
#include <thread>
#include "IFocusEventListener.hpp"
#include "FocusEventListener.hpp"

class FocusNetworkManager : public IFocusNetworkManager {
private:
	int _socket;
	std::unique_ptr<std::thread> _networkManagerThread;
	std::unique_ptr<IFocusEventListener> _eventListener = std::unique_ptr<IFocusEventListener>(std::make_unique<FocusEventListener>());
	void RunReceive();
public:
	FocusNetworkManager();
	virtual ~FocusNetworkManager();
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
