//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusEventManager.hpp>
#include <iostream>

void FocusEventManager::Run()
{
	_eventManagerThread = std::make_unique<std::thread>(std::bind(&FocusEventManager::RunReceive, this));
}

void FocusEventManager::RunReceive()
{
	std::cout << "RunReceive EventManger function is called properly !" << std::endl;
}
