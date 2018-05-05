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
#include "FocusConfiguration.hpp"
#include <atomic>

class FocusNetworkManager {
private:
    std::shared_ptr<FocusSocket> _socket;
    std::unique_ptr<std::thread> _networkManagerThread;
    std::atomic<bool> _isRunning;
    std::atomic<bool> _sigReceived;
    std::unique_ptr<FocusEventListener<Focus::Envelope>> _eventListener;
    std::unique_ptr<FocusEventEmitter> _eventEmitter;
    std::string _device_id;
    void RunReceive();

public:
    FocusNetworkManager();

    virtual ~FocusNetworkManager();

    void Run(const std::string &device_id, std::shared_ptr<FocusConfiguration> &config, std::atomic<bool> &sigReceived);
};

#endif //FOCUS_CLIENT_FOCUSNETWORKMANAGER_HPP
