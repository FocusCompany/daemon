//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>
#include <spdlog/spdlog.h>

void FocusDaemon::Run(const std::string &configFileName) {
    spdlog::get("logger")->info("FocusDaemon is running");
    EventManager->Run();
    _config = std::make_shared<FocusConfiguration>(configFileName);
    auto usr = _config->getUser();
    Authenticator->Run(_config);
    if (Authenticator->Login(usr._email, usr._password, _config->getDeviceId())) {
        _device_id = Authenticator->GetDeviceId();
        spdlog::get("logger")->info("User uuid: {}", Authenticator->GetUUID());
        if (_device_id.empty()) {
            if (Authenticator->RegisterDevice("MacBook Pro de Etienne")) {
                Authenticator->Login(usr._email, usr._password, _config->getDeviceId());
                _device_id = Authenticator->GetDeviceId();
            }
        }
    }
    if (!_device_id.empty()) {
        spdlog::get("logger")->info("Device Id: {}", _device_id);
        NetworkManager->Run(_device_id, _config);
        KeyLogger->Run(Authenticator, _config);
    }
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
}