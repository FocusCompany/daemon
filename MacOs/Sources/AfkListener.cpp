//
// Created by Etienne Pasteur on 25/04/2018.
//

#include "AfkListener.hpp"
#include <ApplicationServices/ApplicationServices.h>
#include <spdlog/spdlog.h>
#include <FocusAfkEventPayload.pb.h>
#include <FocusSerializer.hpp>

void AfkListener::Run(int triggerAfkInSecond) {
    _triggerAfkInSecond = triggerAfkInSecond;
    _eventListener = std::make_unique<std::thread>(std::bind(&AfkListener::EventListener, this));
}

void AfkListener::EventListener() {
    bool afk = false;
    double lastInputSince = 0;

    while (true) {
        lastInputSince = CGEventSourceSecondsSinceLastEventType(kCGEventSourceStateHIDSystemState, kCGAnyInputEventType);
        if (lastInputSince < _triggerAfkInSecond) {
            afk = false;
        } else {
            if (!afk) {
                spdlog::get("console")->info("AFK since 5 minutes");
                auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                OnAfk(now + std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(_triggerAfkInSecond)));
                afk = true;
            }
        }
        sleep(2);
    }
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
