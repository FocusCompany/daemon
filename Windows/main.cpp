//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <signal.h>
#include <spdlog_pragma.hpp>
#include "FocusDaemon.hpp"
#include <FocusPlatformFolders.hpp>

std::atomic<bool> sigReceived;

void exitProgram()
{
	sigReceived = true;
	spdlog::set_pattern("\t*****  %v  *****");
	spdlog::get("logger")->info("End of program");
	spdlog::get("logger")->flush();
	spdlog::drop_all();
}

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	if (CEvent == CTRL_C_EVENT || CEvent == CTRL_BREAK_EVENT || CEvent == CTRL_CLOSE_EVENT || CEvent == CTRL_LOGOFF_EVENT || CEvent == CTRL_SHUTDOWN_EVENT)
		exitProgram();
	return TRUE;
}

int main()
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		return -1;
	
	sigReceived = false;

	FocusDaemon::bootstrap("Windows");
	FocusDaemon daemon;
	daemon.Run("daemon.config", sigReceived);
	exitProgram();
	return (0);
}
