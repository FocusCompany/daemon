//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <signal.h>
#include <spdlog/spdlog.h>
#include "FocusDaemon.hpp"
#include <condition_variable>
#include <FocusPlatformFolders.hpp>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> sigReceived;

void exitProgram()
{
	sigReceived = true;
	spdlog::set_pattern("\t*****  %v  *****");
	spdlog::get("logger")->info("End of program");
	spdlog::get("logger")->flush();
	spdlog::drop_all();
	std::unique_lock<std::mutex> lck(mtx);
	cv.notify_all();
}

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	if (CEvent == CTRL_C_EVENT || CEvent == CTRL_BREAK_EVENT || CEvent == CTRL_CLOSE_EVENT || CEvent == CTRL_LOGOFF_EVENT || CEvent == CTRL_SHUTDOWN_EVENT)
		exitProgram();
	return TRUE;
}

int main(const int ac, const char** av)
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		return -1;
	
	sigReceived = false;
	auto console = spdlog::stdout_color_mt("console");
	std::vector<spdlog::sink_ptr> sinks;
	sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
	sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(sago::getDataHome() + "/Focus/logs.txt", 1048576 * 5, 3));
	auto combined_logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
	spdlog::register_logger(combined_logger);

	spdlog::set_pattern("\t*****  %v  *****");
	spdlog::get("logger")->info("Starting Focus daemon on Windows Platform");
	spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l]\t\t: %v");

	FocusDaemon daemon;
	if (daemon.Run("daemon.config", sigReceived)) {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck);
	} else {
		exitProgram(0);
	}
	return (0);
}
