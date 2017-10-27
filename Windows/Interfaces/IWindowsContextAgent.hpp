//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP
#define FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP

#include <string>

class IWindowsContextAgent {
public:
	virtual void Run() = 0;
	virtual void OnContextChanged(std::string &processName, std::string &windowTitle) = 0;

};

#endif //FOCUS_CLIENT_IWINDOWSCONTEXTAGENT_HPP