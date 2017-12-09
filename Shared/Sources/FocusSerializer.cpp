//
// Created by Etienne Pasteur on 09/12/2017.
//

#include <sys/time.h>
#include "FocusSerializer.hpp"

Focus::Event FocusSerializer::CreateEventFromContext(const std::string &dest, google::protobuf::Message &payload) {
    Focus::Event event;

    auto *timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(time(NULL));
    timestamp->set_nanos(0);

    event.set_allocated_timestamp(timestamp);
    event.set_payloadtype(dest);
    event.mutable_payload()->PackFrom(payload);

    return event;
}
