//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>

void FocusDaemon::Run() {
	Authenticator->Run();
    if (Authenticator->Login("et.pasteur@hotmail.fr", "toto42sh"))
        _user_uuid = Authenticator->GetUUID();
    if (!_user_uuid.empty()) {
        EventManager->Run();
        NetworkManager->Run(_user_uuid);
        KeyLogger->Run();

        //Let's wait indefinitely
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
    }
}