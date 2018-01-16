//
// Created by Etienne Pasteur on 16/12/2017.
//

#include "FocusAuthenticator.hpp"
#include <httplib.h>
#include <json.hpp>

void FocusAuthenticator::Run() {
    httplib::Client cli("localhost", 3000);

    httplib::Params params;
    params = {
            {"email", "et.pasteur@hotmail.fr"},
            {"password", "toto42sh"}
    };

    auto res = cli.post("/login", params);
    if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end())
        std::cout << j["token"] << std::endl;
    }
}

bool FocusAuthenticator::GetConnectionStatus() {

    return false;
}

std::string FocusAuthenticator::GetCurrentToken() {
    return std::string();
}

bool FocusAuthenticator::Connect(std::string &, std::string &) {
    return false;
}

bool FocusAuthenticator::Disconnect() {
    return false;
}

bool FocusAuthenticator::RenewToken() {
    return false;
}

bool FocusAuthenticator::Register(std::string &, std::string &, std::string &, std::string &) {
    return false;
}

