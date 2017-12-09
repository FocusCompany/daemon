//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusNetworkManager.hpp>
#include <nanomsg/pipeline.h>
#include <FocusContextEventPayload.pb.h>

FocusNetworkManager::FocusNetworkManager() {
    _socket = nn_socket(AF_SP, NN_PUSH);
}

FocusNetworkManager::~FocusNetworkManager() {
    nn_shutdown(_socket, 0);
}

void FocusNetworkManager::Run() {
    nn_connect(_socket, "tcp://192.168.1.106:5555");

    _networkManagerThread = std::make_unique<std::thread>(std::bind(&FocusNetworkManager::RunReceive, this));

    _eventListener->Register("FocusNetworkManager", [this](Focus::Event &event) {
        std::string envelopeData;
        event.SerializeToString(&envelopeData);
        nn_send(_socket, envelopeData.c_str(), envelopeData.size(), 0);
    });
}

void FocusNetworkManager::RunReceive() {
    //TODO: Implementing Reception module to handle server request.
}