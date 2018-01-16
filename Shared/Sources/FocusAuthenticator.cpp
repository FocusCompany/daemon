//
// Created by Etienne Pasteur on 16/12/2017.
//

#include "FocusAuthenticator.hpp"
#include <httplib.h>
#include <json.hpp>
#include <jwt/jwt_all.h>

void FocusAuthenticator::Run() {
    httplib::Client cli("localhost", 3000);

    httplib::Params params;
    params = {
            {"email",    "et.pasteur@hotmail.fr"},
            {"first_name",    "Etienne"},
            {"last_name",    "Pasteur"},
            {"password", "toto42sh"}
    };

    auto res = cli.post("/register", params);
    if (res && res->status == 200) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("token") != j.end()) {
            std::cout << j["token"] << std::endl;

            ExpValidator exp;

            std::ifstream rsa_file {"keys/rsa.pub"};
            std::string rsa_pub_key { std::istreambuf_iterator<char>(rsa_file), std::istreambuf_iterator<char>() };

            std::cout << rsa_pub_key << std::endl;

            RS256Validator signer(rsa_pub_key);

            try {
                nlohmann::json header, payload;

                std::tie(header, payload) = JWT::Decode(j["token"], &signer, &exp);
                std::cout << "Header: " << header << std::endl;
                std::cout << "Payload: " << payload << std::endl;
            } catch (InvalidTokenError &tfe) {
                // An invalid token
                std::cout << "Validation failed: " << tfe.what() << std::endl;
            }
        }
    } else if (res) {
        auto j = nlohmann::json::parse(res->body);
        if (j.find("message") != j.end())
            std::cout << j["message"] << std::endl;
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

