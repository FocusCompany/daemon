//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP
#define FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP

#include <IFocusEventManager.hpp>
#include <thread>

class FocusEventManager : public IFocusEventManager {
private:
	std::unique_ptr<std::thread> _eventManagerThread;
	void RunReceive();
public:
	void Run() override final;
};

#endif //FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP
