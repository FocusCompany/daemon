//
// Created by Etienne Pasteur on 12/08/2018.
//

#ifndef DAEMON_BUNDLELOCATION_HPP
#define DAEMON_BUNDLELOCATION_HPP

#include <iostream>

#if defined(MSVC)
	#include <Shlwapi.h>
#elif defined(APPLE)
    #include <mach-o/dyld.h>
#elif defined(UNIX)
    #include <libgen.h>
    #include <unistd.h>
    #include <linux/limits.h>
#endif

static const std::string getExecPath() {
#if defined(MSVC)
	TCHAR dest[MAX_PATH];
	DWORD length = GetModuleFileName(NULL, dest, MAX_PATH);
	PathRemoveFileSpec(dest);
	return std::string(dest) + "\\";
#elif defined(APPLE)
    std::string path(PAGE_SIZE, '\0');
    auto size = static_cast<uint32_t>(path.size());
    if (_NSGetExecutablePath(path.begin().base(), &size) != 0) {
        std::exit(1);
    }
    path = path.substr(0, path.find_last_of('/') + 1);
    return path;
#elif defined(UNIX)
    char result[ PATH_MAX ];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    result[count] = '\0';
    const char *path;
    if (count != -1) {
        path = dirname(result);
        return std::string(path) + "/";
    }
    return std::string("");
#endif
}

#endif //DAEMON_BUNDLELOCATION_HPP
