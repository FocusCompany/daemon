//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_JSON_PRAGMA_HPP
#define DAEMON_JSON_PRAGMA_HPP

#if defined(MSVC)
    #include "json.hpp"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
        #include "json.hpp"
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_JSON_PRAGMA_HPP
