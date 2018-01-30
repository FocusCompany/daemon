//
// Created by Etienne Pasteur on 29/01/2018.
//

#ifndef FOCUS_CLIENT_IMOUSELISTENER_HPP
#define FOCUS_CLIENT_IMOUSELISTENER_HPP

class IMouseListener {
public:
	virtual void Run() = 0;
	virtual void OnMouseEvent(int button, long x, long y) = 0;
};

#endif //FOCUS_CLIENT_IMOUSELISTENER_HPP