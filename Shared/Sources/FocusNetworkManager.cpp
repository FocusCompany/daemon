//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusNetworkManager.hpp>
#include <FocusContextEventPayload.pb.h>
#include <FocusSecureSocket.hpp>
#include <iostream>
#include <FocusEnvelope.pb.h>

FocusNetworkManager::FocusNetworkManager() {
    _socket = std::static_pointer_cast<IFocusSocket>(std::make_shared<FocusSecureSocket<Client>>("rq:rM>}U?@Lns47E1%kR.o@n%FcmmsL/@{H8]yf7", "Yne@$w-vo<fVvi]a<NY6T1ed:M$fCG*[IaLV{hID", "D:)Q[IlAW!ahhC2ac:9*A}h:p?([4%wOTJ%JR%cs"));
}

FocusNetworkManager::~FocusNetworkManager() {
    _socket->Disconnect();
}

void FocusNetworkManager::Run(std::string user_uuid) {
    _socket->Connect("tcp://192.168.1.106:5555");

    _networkManagerThread = std::make_unique<std::thread>(std::bind(&FocusNetworkManager::RunReceive, this));

    _eventListener->RegisterEnvelope("FocusNetworkManager", [this, user_uuid](Focus::Envelope &envelope) {
        std::cout << "ID from envelope: " << envelope.clientid() << std::endl;
        std::string envelopeData;
        envelope.SerializeToString(&envelopeData);
        try {
            _socket->Send(user_uuid, envelopeData);
        }
        catch (const std::exception &e) {
            std::cout << "Error : " << e.what() << std::endl;
        }
    });
}

void FocusNetworkManager::RunReceive() {
    //TODO: Implementing Reception module to handle server request.
}
