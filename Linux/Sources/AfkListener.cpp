//
// Created by Etienne Pasteur on 25/04/2018.
//

#include "AfkListener.hpp"
#include <spdlog_pragma.hpp>
#include <FocusAfkEventPayload.pb.h>
#include <FocusSerializer.hpp>
#include <iostream>

void AfkListener::Run(int triggerAfkInSecond, std::atomic<bool> &sigReceived) {
    _triggerAfkInSecond = triggerAfkInSecond;
    _sigReceived = sigReceived.load();
    setlocale(LC_ALL, "");
    _display = std::unique_ptr<Display, std::function<void(Display * )>>(XOpenDisplay(nullptr), [](Display *ptr) {
        if (ptr != nullptr) {
            XCloseDisplay(ptr);
        }
    });
    if (!_display) {
        spdlog::get("logger")->error("Failed to connect to X Server");
    } else {
        _isRunning = true;
        _eventListener = std::make_unique<std::thread>(std::bind(&AfkListener::EventListener, this));
    }
}

void AfkListener::EventListener() {
    bool afk = false;
    long lastInputSince = 0;
    XScreenSaverInfo *info = XScreenSaverAllocInfo();

    while (_isRunning && !_sigReceived) {
        XScreenSaverQueryInfo(_display.get(), DefaultRootWindow(_display.get()), info);
        lastInputSince = info->idle / 1000;
        if (lastInputSince < _triggerAfkInSecond) {
            afk = false;
        } else {
            if (!afk) {
                spdlog::get("console")->info("AFK since {} seconds", _triggerAfkInSecond);
                auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                OnAfk(now - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(_triggerAfkInSecond)));
                afk = true;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    XFree(info);
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

AfkListener::~AfkListener() {
    if (_isRunning) {
        _isRunning = false;
        _eventListener->join();
    }
}

AfkListener::AfkListener() : _triggerAfkInSecond(),
                             _isRunning(false),
                             _sigReceived(false),
                             _display(),
                             _eventListener(),
                             _eventEmitter(std::make_unique<FocusEventEmitter>()) {}
