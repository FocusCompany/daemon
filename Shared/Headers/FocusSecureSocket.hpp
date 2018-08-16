//
// Created by Etienne Pasteur on 22/01/2018.
//

#ifndef DAEMON_FOCUSSECURESOCKET_HPP
#define DAEMON_FOCUSSECURESOCKET_HPP

#include "FocusSocket.hpp"
#include <string.h>

enum SecureSocketType {
    Client = 0,
    Server = 1
};

template <SecureSocketType type>
class FocusSecureSocket : public FocusSocket { };

template <>
class FocusSecureSocket<Server> : public FocusSocket {
public:
    FocusSecureSocket(const std::string &serverSecretKey) : FocusSocket() {
        _socket->setsockopt(ZMQ_CURVE_SERVER, 1);
        _socket->setsockopt(ZMQ_CURVE_SECRETKEY, serverSecretKey.c_str(), serverSecretKey.size());
    }
};

template <>
class FocusSecureSocket<Client> : public FocusSocket {
public:
    FocusSecureSocket(const std::string &serverKey, const std::string &publicKey, const std::string &clientSecretKey) : FocusSocket() {
        _socket->setsockopt(ZMQ_CURVE_SERVERKEY, serverKey.c_str(), serverKey.size());
        _socket->setsockopt(ZMQ_CURVE_PUBLICKEY, publicKey.c_str(), publicKey.size());
        _socket->setsockopt(ZMQ_CURVE_SECRETKEY, clientSecretKey.c_str(), clientSecretKey.size());
    }
};

#endif //DAEMON_FOCUSSECURESOCKET_HPP
