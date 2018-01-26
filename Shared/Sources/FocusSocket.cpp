//
// Created by Etienne Pasteur on 22/01/2018.
//

#include <IFocusSocket.hpp>
#include <FocusSocket.hpp>

zmq::context_t *FocusSocket::Context = new zmq::context_t();

FocusSocket::FocusSocket() : IFocusSocket() {
    _socket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t(*FocusSocket::Context, ZMQ_DEALER));
}

std::string &FocusSocket::GetSocketID() {
    return IFocusSocket::GetSocketID();
}

void FocusSocket::SetSocketID(const std::string &id) {
    IFocusSocket::SetSocketID(id);
}

void FocusSocket::Send(const std::string &clientId, const std::string &payload) {
    zmq::multipart_t rep;
    _socket->setsockopt(ZMQ_IDENTITY, clientId.c_str(), 16);
    rep.addstr(payload);
    rep.send(*_socket, 0);
}

std::string FocusSocket::Receive() {
    zmq::message_t msg;
    _socket->recv(&msg);
    std::string ret = std::string(static_cast<char *>(msg.data()), msg.size());
    return ret;
}

void FocusSocket::Connect(const std::string &address) {
    _socket->connect(address);
}

void FocusSocket::Bind(const std::string &address) {
    _socket->bind(address);
}

bool FocusSocket::ShouldAccept() {
    return false;
}

std::unique_ptr <IFocusSocket> FocusSocket::Accept() {
    return nullptr;
}

void *FocusSocket::GetNativeSocket() {
    return _socket.get();
}

void FocusSocket::Disconnect() {
    _socket->close();
}