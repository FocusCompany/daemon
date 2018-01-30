//
// Created by Etienne Pasteur on 22/01/2018.
//

#include <FocusSocket.hpp>
#include <spdlog/spdlog.h>

zmq::context_t *FocusSocket::Context = new zmq::context_t();

FocusSocket::FocusSocket() {
    _socket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t(*FocusSocket::Context, ZMQ_DEALER));
}

bool FocusSocket::Send(const std::string &clientId, const std::string &payload) const {
    zmq::multipart_t rep;
    _socket->setsockopt(ZMQ_IDENTITY, clientId.c_str(), 16);
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