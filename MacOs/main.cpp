//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <spdlog/spdlog.h>
#include "FocusDaemon.hpp"
#include "FocusConfiguration.hpp"

void exitProgram(int sig) {
    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("End of program");
    spdlog::get("logger")->flush();
    spdlog::drop_all();
}

int main(const int ac, const char **av) {
    signal(SIGABRT, &exitProgram);
    signal(SIGTERM, &exitProgram);
    signal(SIGINT, &exitProgram);

    auto console = spdlog::stdout_color_mt("console");
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/logs.txt", 1048576 * 5, 3));
    auto combined_logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    spdlog::register_logger(combined_logger);

    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("Starting Focus daemon on MacOs Platform");
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l]\t\t: %v");

    FocusConfiguration config("daemon.config");
    if (config.isFilled()) {
        FocusDaemon daemon;
        daemon.Run(config);
    }

    exitProgram(0);
    return (0);
}