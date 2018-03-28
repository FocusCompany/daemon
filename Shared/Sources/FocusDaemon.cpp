//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>
#include <spdlog/spdlog.h>

void FocusDaemon::Run(FocusConfiguration &config) {
    spdlog::get("logger")->info("FocusDaemon is running");
    auto usr = config.getUser();
    Authenticator->Run(config);
    if (Authenticator->Login(usr._email, usr._password)) {
        _user_uuid = Authenticator->GetUUID();
        spdlog::get("console")->info("User uuid: {}", _user_uuid);
    }
    if (!_user_uuid.empty()) {
        EventManager->Run();
        NetworkManager->Run(_user_uuid, config);
        KeyLogger->Run(_user_uuid);

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
    }
}