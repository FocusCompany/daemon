//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <spdlog/spdlog.h>
#include "FocusDaemon.hpp"
#include <condition_variable>
#include <FocusPlatformFolders.hpp>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> sigReceived;

void exitProgram(__attribute__((__unused__)) int sig) {
    (void)sig;
    sigReceived = true;
    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("End of program");
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

    FocusDaemon::bootstrap("macOS");
    FocusDaemon daemon;
    if (daemon.Run("daemon.config", sigReceived)) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck);
    } else {
        exitProgram(0);
    }
    return (0);
}