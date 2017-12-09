//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP
#define FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP

#include <string>
#include <functional>
#include <thread>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include "FocusEvent.pb.h"

template<class TPayload>
class FocusEventListener {
private:
    std::function<void(std::string clientId, TPayload &payload)> _onMessage;
    std::unique_ptr<std::thread> _eventListenerThread;
    int _socketSUB;

    static void RunReceive(int socketSUB, std::function<void(std::string clientId, TPayload &)> *onMessage) {
        while (true) {
            char *buf = NULL;
            int bytes = nn_recv(socketSUB, &buf, NN_MSG, 0);
            std::string recv = std::string(buf);
            nn_freemsg(buf);
            std::string clientId = recv.substr(0, recv.find_first_of('|'));
            std::string payload = recv.substr(recv.find_first_of('|') + 1);

            Focus::Event event;
            if (!event.ParseFromString(payload))
                continue;
            (*onMessage)(clientId, event);
        }
    }

public:
    FocusEventListener() {
        _socketSUB = nn_socket(AF_SP, NN_SUB);
        nn_connect(_socketSUB, "ipc:///tmp/EventEmitter");
    }

    void Register(std::string payloadType, std::function<void(std::string clientId, TPayload &)> onMessage) {
        nn_setsockopt(_socketSUB, NN_SUB, NN_SUB_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(RunReceive, _socketSUB, &_onMessage);
    }
};


#endif //FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP