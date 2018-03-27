//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <FocusSerializer.hpp>
#include "ContextAgent.hpp"
#include "FocusContextEventPayload.pb.h"
#include <Carbon/Carbon.h>

ContextAgent::ContextAgent() {

}

ContextAgent::~ContextAgent() {

}

void ContextAgent::Run() {
    //TODO: Implementing ContextAgent

    int layer;
    std::string tmp;

    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    CFIndex numWindows = CFArrayGetCount(windowList);
    for (int i = 0; i < (int) numWindows; i++) {
        auto info = static_cast<CFDictionaryRef>(CFArrayGetValueAtIndex(windowList, i));
        auto appName = static_cast<CFStringRef>(CFDictionaryGetValue(info, kCGWindowOwnerName));
        auto windowName = static_cast<CFStringRef>(CFDictionaryGetValue(info, kCGWindowName));
        CFNumberGetValue(static_cast<CFNumberRef>(CFDictionaryGetValue(info, kCGWindowLayer)), kCFNumberIntType, &layer);
        if (appName != nullptr && layer == 0) {
            tmp = CFStringGetCStringPtr(appName, kCFStringEncodingMacRoman);
            std::cout << "Layer: " << layer << " AppName: " << tmp;
            if (windowName != nullptr) {
                tmp = CFStringGetCStringPtr(windowName, kCFStringEncodingMacRoman);
                std::cout << " WindowName: " << tmp;
            }
            std::cout << std::endl;
        }
    }
    CFRelease(windowList);

    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void ContextAgent::OnContextChanged(const std::string &processName, const std::string &windowTitle) const {
    Focus::ContextEventPayload context;
    context.set_processname(processName);
    context.set_windowname(windowTitle);

    Focus::Event event = FocusSerializer::CreateEventFromContext("ContextChanged", context);

    _eventEmitter->Emit("NewEvent", event);
}