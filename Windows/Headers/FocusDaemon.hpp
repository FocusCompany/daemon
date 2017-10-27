//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSDAEMON_HPP
#define FOCUS_CLIENT_FOCUSDAEMON_HPP

#include <memory>
#include "IFocusDaemon.hpp"
#include "IFocusNetworkManager.hpp"
#include "IFocusKeyLogger.hpp"
#include "IFocusEventManager.hpp"
#include "FocusNetworkManager.hpp"
#include "FocusKeyLogger.hpp"
#include "FocusEventManager.hpp"

class FocusDaemon : public IFocusDaemon {
private:
	std::unique_ptr<IFocusKeyLogger> KeyLogger = std::unique_ptr<IFocusKeyLogger>(std::make_unique<FocusKeyLogger>());
	std::unique_ptr<IFocusNetworkManager> NetworkManager = std::unique_ptr<IFocusNetworkManager>(std::make_unique<FocusNetworkManager>());
	std::unique_ptr<IFocusEventManager> EventManager = std::unique_ptr<IFocusEventManager>(std::make_unique<FocusEventManager>());

public:
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSDAEMON_HPP
