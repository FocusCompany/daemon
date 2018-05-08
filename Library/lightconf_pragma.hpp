//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_LIGHTCONF_PRAGMA_HPP
#define DAEMON_LIGHTCONF_PRAGMA_HPP

#if defined(MSVC)
    #include "lightconf/lightconf.hpp"
    #include "lightconf/config_format.hpp"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
        #include "lightconf/lightconf.hpp"
        #include "lightconf/config_format.hpp"
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_LIGHTCONF_PRAGMA_HPP
