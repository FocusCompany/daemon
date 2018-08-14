//
// Created by Etienne Pasteur on 17/05/2018.
//

#include <spdlog_pragma.hpp>
#include <csignal>
#include <iostream>
#include "FocusUI.hpp"
#include <webview_pragma.hpp>
#include <BundleLocation.hpp>

struct webview _w;

void FocusUI::Run() {
    spdlog::get("logger")->info("FocusUI is running");

    _messageListener->RegisterMessage("webviewAction", [](const std::string &payload) {
        webview_dispatch(&_w, [](struct webview *w, void *arg) {
            std::string data = "HandleCommand('" + std::string(static_cast<char*>(arg)) + "');";
            free(arg);
            webview_eval(w, data.c_str());
            }, strdup(const_cast<char*>(payload.c_str())));

    });

    std::string url = "file://" + getExecPath() + "login.html";

    _w.title = "Focus";
    _w.url = url.c_str();
    _w.width = 800;
    _w.height = 600;
    _w.userdata = this;
    _w.debug = true;
    _w.external_invoke_cb = [](struct webview *w, const char *data) {
        auto *app = static_cast<FocusUI *>(w->userdata);
        app->HandleCommand(std::string(data));
    };

    webview_init(&_w);
    while (webview_loop(&_w, 1) == 0) {}
    webview_terminate(&_w);
}

void FocusUI::HandleCommand(const std::string &data) {
    spdlog::get("logger")->info("Received from frontend : {}", data);
}

FocusUI::FocusUI() : _messageListener(std::make_unique<FocusEventListener<const std::string &>>()) {}
