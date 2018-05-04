//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusNetworkManager.hpp>
#include <FocusContextEventPayload.pb.h>
#include <FocusSecureSocket.hpp>
#include <iostream>
#include <FocusEnvelope.pb.h>
#include <spdlog/spdlog.h>

FocusNetworkManager::FocusNetworkManager() :
        _socket(std::static_pointer_cast<FocusSocket>(std::make_shared<FocusSecureSocket<Client>>("rq:rM>}U?@Lns47E1%kR.o@n%FcmmsL/@{H8]yf7", "Yne@$w-vo<fVvi]a<NY6T1ed:M$fCG*[IaLV{hID", "D:)Q[IlAW!ahhC2ac:9*A}h:p?([4%wOTJ%JR%cs"))),
        _networkManagerThread(),
        _isRunning(false),
        _sigReceived(false),
        _eventListener(std::make_unique<FocusEventListener<Focus::Envelope>>()),
        _eventEmitter(std::make_unique<FocusEventEmitter>()),
        _device_id() {}

FocusNetworkManager::~FocusNetworkManager() {
    if (_isRunning) {
        _isRunning = false;
        _networkManagerThread->join();
    }
    _socket->Disconnect();
}

void FocusNetworkManager::Run(const std::string &device_id, std::shared_ptr<FocusConfiguration> &config, std::atomic<bool> &sigReceived) {
    auto srv = config->getServer(serverType::BACKEND);
    std::string urlStr = "tcp://";
    urlStr += srv._ip;
    urlStr += ":";
    urlStr += std::to_string(srv._port);

    _device_id = device_id;
    _sigReceived = sigReceived.load();

    _socket->Connect(urlStr);

    _isRunning = true;
    _networkManagerThread = std::make_unique<std::thread>(std::bind(&FocusNetworkManager::RunReceive, this));

    _eventListener->RegisterEnvelope("FocusNetworkManager", [this](Focus::Envelope &envelope) {
        spdlog::get("console")->info("Trying to send envelope");
        std::string envelopeData;
        envelope.SerializeToString(&envelopeData);
        if (_socket->Send(_device_id, envelopeData)) {
            spdlog::get("console")->info("Envelope send successfully");
            _eventEmitter->EmitMessage("FocusSendDataToBackend", "OK");
        } else {
            spdlog::get("logger")->error("Can't send data to server");
        }
    });
}

void FocusNetworkManager::RunReceive() {
    //TODO: Implementing Reception module to handle server request.
}
