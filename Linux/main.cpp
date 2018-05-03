//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <spdlog/spdlog.h>
#include <condition_variable>
#include "FocusDaemon.hpp"
#include <FocusPlatformFolders.hpp>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> sigReceived;

void exitProgram(int sig) {
    sigReceived = true;
    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("End of program");
    spdlog::get("logger")->flush();
    spdlog::drop_all();
    std::unique_lock<std::mutex> lck(mtx);
    cv.notify_all();
}

int main(const int ac, const char **av) {
    signal(SIGABRT, &exitProgram);
    signal(SIGTERM, &exitProgram);
    signal(SIGINT, &exitProgram);
    sigReceived = false;

    auto console = spdlog::stdout_color_mt("console");
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(sago::getDataHome() + "/Focus/logs.txt", 1048576 * 5, 3));
    auto combined_logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    spdlog::register_logger(combined_logger);

    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("Starting Focus daemon on Linux Platform");
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l]\t\t: %v");

    FocusDaemon daemon;
    daemon.Run("daemon.config", sigReceived);

    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck);

    return (0);
}