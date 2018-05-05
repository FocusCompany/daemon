//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_SPDLOG_PRAGMA_HPP
#define DAEMON_SPDLOG_PRAGMA_HPP

#if defined(MSVC)
    #include <spdlog/spdlog.h>
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
        #include <spdlog/spdlog.h>
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_SPDLOG_PRAGMA_HPP
