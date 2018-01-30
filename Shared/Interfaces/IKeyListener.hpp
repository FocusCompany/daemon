//
// Created by Etienne Pasteur on 29/01/2018.
//

#ifndef FOCUS_CLIENT_IKEYLISTENER_HPP
#define FOCUS_CLIENT_IKEYLISTENER_HPP

#include <string>

class IKeyListener {
public:
	virtual void Run() = 0;
	virtual std::string Flush() = 0;
	virtual void PushKeylog(std::string &keylog) = 0;
};

#endif //FOCUS_CLIENT_IKEYLISTENER_HPP