//
// Created by Etienne Pasteur on 17/05/2018.
//

#include "json_pragma.hpp"
#include <spdlog_pragma.hpp>
#include <csignal>
#include <iostream>
#include "FocusUI.hpp"
#include <webview_pragma.hpp>
#include <BundleLocation.hpp>

// This is how to send data to webview
//std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
//_eventEmitter->EmitMessage("webviewAction", "{\"action\": \"fill_login_form\", \"data\": {\"email\": \"test\", \"password\": \"etienne\"}}");

void FocusUI::Run() {
    spdlog::get("logger")->info("FocusUI is running");

    struct webview _w = {};

    _messageListener->RegisterMessage("WebviewAction", [&](const std::string &payload) {
        webview_dispatch(&_w, [](struct webview *w, void *arg) {
            std::string data = "HandleCommand('" + std::string(static_cast<char *>(arg)) + "');";
            free(arg);
            webview_eval(w, data.c_str());
        }, strdup(const_cast<char *>(payload.c_str())));

    });

    std::string url = "file://" + getExecPath() + "app.html";

    _w.title = "Focus";
    _w.url = url.c_str();
    _w.width = 350;
    _w.height = 500;
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
    auto j = nlohmann::json::parse(data);
    if (j.find("module") != j.end() && j.find("action") != j.end()) {
        std::string module = j["module"];
        _command[module](data);
    } else {
        spdlog::get("logger")->info("Module and/or action not found in frontend payload");
    }
}

FocusUI::FocusUI() : _eventEmitter(std::make_unique<FocusEventEmitter>()),
                     _messageListener(std::make_unique<FocusEventListener<const std::string &>>()),
                     _command() {
    _command["configuration"] = [this](const std::string &data) {
        _eventEmitter->EmitMessage("Configuration", data);
    };
    _command["authenticator"] = [this](const std::string &data) {
        _eventEmitter->EmitMessage("Authenticator", data);
    };
    _command["keylogger"] = [this](const std::string &data) {
        _eventEmitter->EmitMessage("Keylogger", data);
    };
}
