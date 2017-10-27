//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <iostream>
#include "FocusDaemon.hpp"

int main(const int ac, const char **av)
{
	FocusDaemon daemon;

	std::cout << "Starting Focus daemon on Windows Platform" << std::endl;

	daemon.Run();
	return (0);
}
