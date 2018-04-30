//
// Created by Etienne Pasteur on 22/01/2018.
//

#include <FocusSocket.hpp>

zmq::context_t *FocusSocket::Context = new zmq::context_t();

FocusSocket::FocusSocket() {
    _socket = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_DEALER);
}

bool FocusSocket::Send(const std::string &deviceId, const std::string &payload) const {
    zmq::multipart_t rep;
    _socket->setsockopt(ZMQ_IDENTITY, deviceId.c_str(), 16);
    rep.addstr(payload);
    return rep.send(*_socket, 0);
}

std::string FocusSocket::Receive() const {
    zmq::message_t msg;
    _socket->recv(&msg);
    std::string ret = std::string(static_cast<char *>(msg.data()), msg.size());
    return ret;
}

void FocusSocket::Connect(const std::string &address) const {
    _socket->connect(address);
}

void FocusSocket::Disconnect() const {
    _socket->close();
}