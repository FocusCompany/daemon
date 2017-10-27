//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusNetworkManager.hpp>
#include <iostream>

void FocusNetworkManager::Run() {
	_networkManagerThread = std::make_unique<std::thread>(std::bind(&FocusNetworkManager::RunReceive, this));
}

void FocusNetworkManager::RunReceive() {
	std::cout << "RunReceive NetworkManager function is called properly !" << std::endl;
}