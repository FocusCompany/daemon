//
// Created by Etienne Pasteur on 09/12/2017.
//

#include "FocusSerializer.hpp"
#include <chrono>
#include <ctime>

Focus::Event FocusSerializer::CreateEventFromContext(const std::string &dest, google::protobuf::Message &payload) {
    Focus::Event event;

	auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	auto *timestamp = new google::protobuf::Timestamp();
	timestamp->set_seconds(now.count() / 1000);
	timestamp->set_nanos(((now.count() % 1000) * 1000) * 1000);

    event.set_allocated_timestamp(timestamp);
    event.set_payloadtype(dest);
    event.mutable_payload()->PackFrom(payload);

    return event;
}
