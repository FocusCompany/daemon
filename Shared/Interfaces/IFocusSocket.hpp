//
// Created by Etienne Pasteur on 22/01/2018.
//

#ifndef DAEMON_IFOCUSSOCKET_HPP
#define DAEMON_IFOCUSSOCKET_HPP

#include <string>
#include <memory>

class IFocusSocket {

private:
    std::string _id;

public:
    IFocusSocket() {}

    virtual std::string &GetSocketID() {
        return _id;
    }
    virtual void SetSocketID(const std::string &id) {
        _id = id;
    }

    /// Sends \payload via the connected socket.
    /// \param payload The message payload to send.
    /// \param clientId The id of the client, if needed by your implementation.
    virtual void Send(const std::string &clientId, const std::string &payload) = 0;

    /// Should block until a message can be received.
    /// \return message from socket
    virtual std::string Receive() = 0;

    /// Connect the socket to the \address using the specified protocol.
    /// \param address Ex:"tcp://127.0.0.1:5432"
    virtual void Connect(const std::string &address) = 0;

    /// Bind the socket to the \address.
    /// \param address Ex:"tcp://*:5432"
    virtual void Bind(const std::string &address) = 0;

    /// Should listen for new connections on the binded socket and return a new socket when a connection arrives.
    /// \return The new socket representing the new connection.
    virtual std::unique_ptr<IFocusSocket> Accept() = 0;

    /// If your socket implementation automatically accept and stores new connections (Ex. ZeroMQ), return false.
    /// \return whether your Accept() function needs to be called.
    virtual bool ShouldAccept() = 0;

    /// Terminate the current connection and release all ressources.
    virtual void Disconnect() = 0;

    /// Returns a pointer to your underlying socket.
    virtual void *GetNativeSocket() = 0;
};

#endif //DAEMON_IFOCUSSOCKET_HPP
