//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusEventManager.hpp>
#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

FocusEventManager::FocusEventManager() {
	_socketPUB = nn_socket(AF_SP, NN_PUB);
	_socketSUB = nn_socket(AF_SP, NN_SUB);
}

void FocusEventManager::Run() {
	nn_setsockopt(_socketSUB, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);

	nn_bind(_socketPUB, "ipc:///tmp/EventEmitter");
	nn_bind(_socketSUB, "ipc:///tmp/EventListener");

	_eventManagerThread = std::make_unique<std::thread>(std::bind(&FocusEventManager::RunReceive, this));
}

void FocusEventManager::RunReceive() {
	while (true) {
		char *buf = NULL;
		nn_recv(_socketSUB, &buf, NN_MSG, 0);
		nn_send(_socketPUB, buf, strlen(buf) + 1, 0);
		nn_freemsg(buf);
	}
}
