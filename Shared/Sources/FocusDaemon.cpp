//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>
#include <spdlog/spdlog.h>
#include <FocusPlatformFolders.hpp>

bool FocusDaemon::Run(const std::string &configFileName, std::atomic<bool> &sigReceived) {
    spdlog::get("logger")->info("FocusDaemon is running");

    _config = std::make_shared<FocusConfiguration>(sago::getConfigHome() + "/Focus/" + configFileName);
    auto usr = _config->getUser();

    Authenticator->Run(_config);
    if (Authenticator->Login(usr._email, usr._password, _config->getDevice()._id)) {
        _device_id = Authenticator->GetDeviceId();
        spdlog::get("logger")->info("User uuid: {}", Authenticator->GetUUID());
        if (_device_id.empty()) {
            if (Authenticator->RegisterDevice(_config->getDevice()._name)) {
                Authenticator->Login(usr._email, usr._password, _config->getDevice()._id);
                _device_id = Authenticator->GetDeviceId();
            }
        }
    }
    if (!_device_id.empty()) {
        spdlog::get("logger")->info("Device Id: {}", _device_id);
        EventManager->Run(sigReceived);
        NetworkManager->Run(_device_id, _config, sigReceived);
        KeyLogger->Run(Authenticator, _config, sigReceived);
        return true;
    }
    return false;
}