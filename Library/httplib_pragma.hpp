//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_HTTPLIB_PRAGMA_HPP
#define DAEMON_HTTPLIB_PRAGMA_HPP

#if defined(MSVC)
    #include <httplib.h>
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
        #include <httplib.h>
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_HTTPLIB_PRAGMA_HPP
