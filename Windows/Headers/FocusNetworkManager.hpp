//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
#define FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP

#include <IFocusNetworkManager.hpp>
#include <thread>

class FocusNetworkManager : public IFocusNetworkManager {
private:
	std::unique_ptr<std::thread> _networkManagerThread;
	void RunReceive();
public:
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
