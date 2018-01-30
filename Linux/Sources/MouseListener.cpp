//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "MouseListener.hpp"
#include "FocusMouseEventPayload.pb.h"
#include "FocusSerializer.hpp"

MouseListener::MouseListener()
{
}

void MouseListener::Run()
{
	//TODO: Implementing ContextAgent
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
}

void MouseListener::OnMouseEvent(int button, long x, long y)
{

}
