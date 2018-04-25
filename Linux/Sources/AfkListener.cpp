//
// Created by Etienne Pasteur on 25/04/2018.
//

#include "AfkListener.hpp"
#include <spdlog/spdlog.h>
#include <FocusAfkEventPayload.pb.h>
#include <FocusSerializer.hpp>

void AfkListener::Run(int triggerAfkInSecond) {
    _triggerAfkInSecond = triggerAfkInSecond;
    _eventListener = std::make_unique<std::thread>(std::bind(&AfkListener::EventListener, this));
}

void AfkListener::EventListener() {
    //TODO: Implementing ContextAgent
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}


void AfkListener::OnAfk(const std::chrono::milliseconds &timeSinceEpoch) const {
    Focus::AfkEventPayload afk;

    auto *timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(timeSinceEpoch.count() / 1000);
    timestamp->set_nanos(((timeSinceEpoch.count() % 1000) * 1000) * 1000);

    afk.set_allocated_timestamp(timestamp);

    Focus::Event event = FocusSerializer::CreateEventFromContext("Afk", afk);

    _eventEmitter->Emit("NewEvent", event);
}
