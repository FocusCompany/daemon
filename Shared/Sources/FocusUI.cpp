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

    _messageListener->RegisterMessage("alert", [](const std::string &) {
        webview_dispatch(&_w, [](struct webview *w, void *) {
            webview_eval(w, "alert('hello, world');");
            }, nullptr);
    });

    std::string url = "file://" + getExecPath() + "login.html";

    _w.title = "Focus";
    _w.url = url.c_str();
    _w.width = 800;
    _w.height = 600;
    _w.userdata = this;
    _w.external_invoke_cb = [](struct webview *, const char *data) {
        std::cout << std::string(data) << std::endl;
    };

    webview_init(&_w);
    while (webview_loop(&_w, 1) == 0) {}
    webview_terminate(&_w);
}

void FocusUI::HandleCommand(const std::string &data) {
    std::cout << std::string(data) << std::endl;
}

FocusUI::FocusUI() : _messageListener(std::make_unique<FocusEventListener<const std::string &>>()) {}
