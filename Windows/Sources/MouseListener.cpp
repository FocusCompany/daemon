//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "MouseListener.hpp"
#include "FocusMouseEventPayload.pb.h"
#include "FocusSerializer.hpp"

HHOOK hhkLowLevelMouse;
IMouseListener* mouseListener;

MouseListener::MouseListener()
{
	// Set global variable mendatory for hook to access appContext.
	mouseListener = this;
}

void MouseListener::Run()
{
	hhkLowLevelMouse = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(nullptr), 0);
}

void MouseListener::OnMouseEvent(int button, long x, long y)
{
	if (busy)
		return;

	busy = true;
	Focus::MouseEventPayload event;
	Focus::MouseEventPayload::MouseEventType type;
	switch (button)
	{
	case WM_LBUTTONDOWN:
		type = Focus::MouseEventPayload_MouseEventType_L_BUTTON_CLICK;
		break;
	case WM_RBUTTONDOWN:
		type = Focus::MouseEventPayload_MouseEventType_R_BUTTON_CLICK;
		break;
	case WM_MBUTTONDOWN:
		type = Focus::MouseEventPayload_MouseEventType_M_BUTTON_DOWN;
		break;
	case WM_MBUTTONUP:
		type = Focus::MouseEventPayload_MouseEventType_M_BUTTON_UP;
		break;
	case WM_MBUTTONDBLCLK:
		type = Focus::MouseEventPayload_MouseEventType_M_BUTTON_CLICK;
		break;
	default:
		return; //Unknown event, ignoring.
	}

	event.set_type(type);
	event.set_x(x);
	event.set_y(y);
	Focus::Event enveloppe = FocusSerializer::CreateEventFromContext("MouseEvent", event);
	_eventEmitter->Emit("FocusNetworkManager", enveloppe);
	busy = false;
}

LRESULT CALLBACK MouseListener::LowLevelMouseProc(int code, WPARAM wp, LPARAM lp)
{
	if (code == HC_ACTION)
	{
		auto s_mouse = reinterpret_cast<MSLLHOOKSTRUCT*>(lp);
		switch (wp)
		{
		case WM_LBUTTONDOWN:
			std::async([&]() { mouseListener->OnMouseEvent(wp, s_mouse->pt.x, s_mouse->pt.y); });
			break;
		case WM_RBUTTONDOWN:
			std::async([&]() { mouseListener->OnMouseEvent(wp, s_mouse->pt.x, s_mouse->pt.y); });
			break;
		case WM_MBUTTONDBLCLK:
			std::async([&]() { mouseListener->OnMouseEvent(wp, s_mouse->pt.x, s_mouse->pt.y); });
			break;
		case WM_MBUTTONUP:
			std::async([&]() { mouseListener->OnMouseEvent(wp, s_mouse->pt.x, s_mouse->pt.y); });
			break;
		case WM_MBUTTONDOWN:
			std::async([&]() { mouseListener->OnMouseEvent(wp, s_mouse->pt.x, s_mouse->pt.y); });
			break;
		default:
			break;
		}
	}
	return CallNextHookEx(hhkLowLevelMouse, code, wp, lp);
}
