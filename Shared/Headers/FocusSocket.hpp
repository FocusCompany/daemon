//
// Created by Etienne Pasteur on 22/01/2018.
//

#ifndef DAEMON_FOCUSSOCKET_HPP
#define DAEMON_FOCUSSOCKET_HPP

#include <IFocusSocket.hpp>
#include "../../Library/zmq_addon.hpp"

class FocusSocket : public IFocusSocket{
public:

    static zmq::context_t *Context;

    std::unique_ptr <zmq::socket_t> _socket;

    FocusSocket();

    virtual std::string &GetSocketID() override;

    virtual void SetSocketID(const std::string &id) override;


    virtual void Send(const std::string &clientId, const std::string &payload) override final;

    virtual std::string Receive() override final;

    virtual void Connect(const std::string &address) override final;

    virtual void Bind(const std::string &address) override final;

    virtual bool ShouldAccept() override final;

    virtual std::unique_ptr <IFocusSocket> Accept() override final;

    virtual void *GetNativeSocket() override final;

    virtual void Disconnect() override;
};


#endif //DAEMON_FOCUSSOCKET_HPP
