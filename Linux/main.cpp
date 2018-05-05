//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <spdlog/spdlog.h>
#include <condition_variable>
#include "FocusDaemon.hpp"
#include <FocusPlatformFolders.hpp>
#include <algorithm>
#include <string>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> sigReceived;

void exitProgram(int sig) {
    sigReceived = true;
    std::string name(sys_signame[sig]);
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("End of program : SIG{}", name);
    spdlog::get("logger")->flush();
    spdlog::drop_all();
    std::unique_lock<std::mutex> lck(mtx);
    cv.notify_all();
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
    if (daemon.Run("daemon.config", sigReceived)) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck);
    } else {
        exitProgram(0);
    }
    return (0);
}