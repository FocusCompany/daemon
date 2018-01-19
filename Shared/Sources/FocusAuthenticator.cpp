//
// Created by Etienne Pasteur on 16/12/2017.
//

#include "FocusAuthenticator.hpp"
#include <json.hpp>
#include <jwt/jwt_all.h>

void FocusAuthenticator::Run() {

    _cli = std::make_unique<httplib::Client>("localhost", 3000, 5);

    httplib::Params params;
    params = {
            {"email",      "enzo@gmail.com"},
            {"first_name", "Etienne"},
            {"last_name",  "Pasteur"},
            {"password",   "toto42sh"}
    };

    auto res = _cli->post("/login", params);
    if (res == nullptr) {
        std::cout << "WTF" << std::endl;
    } else {
        if (res && res->status == 200) {
            auto j = nlohmann::json::parse(res->body);
            if (j.find("token") != j.end()) {
                ExpValidator exp;

                std::ifstream rsa_pub_file{"./keys/public_key"};
                std::string rsa_pub_key{std::istreambuf_iterator<char>(rsa_pub_file), std::istreambuf_iterator<char>()};
                std::ifstream rsa_private_file{"./keys/private_key"};
                std::string rsa_private_key{std::istreambuf_iterator<char>(rsa_private_file), std::istreambuf_iterator<char>()};


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
}

bool FocusAuthenticator::GetConnectionStatus() {

    return false;
}

std::string FocusAuthenticator::GetCurrentToken() {
    return std::string();
}

bool FocusAuthenticator::Login(std::string &, std::string &) {
    return false;
}

bool FocusAuthenticator::Disconnect() {
    return false;
}

bool FocusAuthenticator::RenewToken() {
    return false;
}
