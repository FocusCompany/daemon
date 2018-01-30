//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
#define FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP

#include <thread>
#include <FocusSocket.hpp>
#include "FocusEventListener.hpp"
#include <FocusEnvelope.pb.h>
#include "FocusEventEmitter.hpp"

class FocusNetworkManager {
private:
    std::shared_ptr<FocusSocket> _socket;
    std::unique_ptr<std::thread> _networkManagerThread;
    std::unique_ptr<FocusEventListener<Focus::Envelope>> _eventListener = std::make_unique<FocusEventListener<Focus::Envelope>>();
    std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    std::string _user_uuid;
    void RunReceive();

public:
    FocusNetworkManager();

    ~FocusNetworkManager();

    void Run(std::string user_uuid);
};

#endif //FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
