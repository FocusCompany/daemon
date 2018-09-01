//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <spdlog_pragma.hpp>
#include <condition_variable>
#include "FocusDaemon.hpp"

std::atomic<bool> sigReceived;

void exitProgram(int sig) {
    sigReceived = true;
    std::string name(strsignal(sig));
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("End of program : SIG {}", name);
    spdlog::get("logger")->flush();
    spdlog::drop_all();
}

int main() {
    signal(SIGABRT, &exitProgram);
    signal(SIGTERM, &exitProgram);
    signal(SIGINT, &exitProgram);
    signal(SIGQUIT, &exitProgram);
    signal(SIGKILL, &exitProgram);
    sigReceived = false;

    FocusDaemon::bootstrap("Linux");
    FocusDaemon daemon;
    daemon.Run("daemon.config", sigReceived);
    exitProgram(0);
    return (0);
}