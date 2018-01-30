//
// Created by Etienne Pasteur on 29/01/2018.
//

#ifndef FOCUS_CLIENT_MOUSELISTENER_HPP
#define FOCUS_CLIENT_MOUSELISTENER_HPP

#include <future>
#include "IMouseListener.hpp"
#include "FocusEvent.pb.h"
#include "FocusEventEmitter.hpp"

class MouseListener : public IMouseListener
{
public:
	MouseListener();

	void Run() override final;

	void OnMouseEvent(int button, long x, long y) override final;

private:
	std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
};

#endif //FOCUS_CLIENT_MOUSELISTENER_HPP
