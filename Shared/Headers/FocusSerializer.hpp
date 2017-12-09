//
// Created by Etienne Pasteur on 09/12/2017.
//

#ifndef DAEMON_FOCUSSERIALIZER_HPP
#define DAEMON_FOCUSSERIALIZER_HPP


#include <FocusEvent.pb.h>

class FocusSerializer {
public:
    static Focus::Event CreateEventFromContext(const std::string &dest, const google::protobuf::Message &payload);
};


#endif //DAEMON_FOCUSSERIALIZER_HPP
