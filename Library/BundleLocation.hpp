//
// Created by Etienne Pasteur on 12/08/2018.
//

#ifndef DAEMON_BUNDLELOCATION_HPP
#define DAEMON_BUNDLELOCATION_HPP

#include <iostream>

#if defined(MSVC)
    // Windows
#elif defined(APPLE)
    #include <mach-o/dyld.h>
#elif defined(UNIX)
    // Unix
#endif

static const std::string getExecPath() {
#if defined(MSVC)
    return std::string("");
#elif defined(APPLE)
    std::string path(PAGE_SIZE, '\0');
    auto size = static_cast<uint32_t>(path.size());
    if (_NSGetExecutablePath(path.begin().base(), &size) != 0) {
        std::exit(1);
    }
    path = path.substr(0, path.find_last_of('/') + 1);
    return path;
#elif defined(UNIX)
    return std::string("");
#endif
}

#endif //DAEMON_BUNDLELOCATION_HPP
