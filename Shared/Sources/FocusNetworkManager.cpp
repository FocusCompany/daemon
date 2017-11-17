//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusNetworkManager.hpp>
#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

FocusNetworkManager::FocusNetworkManager()
{
	_socket = nn_socket(AF_SP, NN_PUSH);
}

FocusNetworkManager::~FocusNetworkManager()
{
	nn_shutdown(_socket, 0);
}

void FocusNetworkManager::Run() {
	nn_connect(_socket, "tcp://128.199.70.244:5555");

	_networkManagerThread = std::make_unique<std::thread>(std::bind(&FocusNetworkManager::RunReceive, this));

	_eventListener->Register("FocusNetworkManager", [&](std::string clientId, std::string &payload) {
		std::cout << "Sending: " << payload << std::endl;
		nn_send(_socket, payload.c_str(), payload.size(), 0);
	});
}

void FocusNetworkManager::RunReceive() {

}