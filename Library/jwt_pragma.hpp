//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_JWT_PRAGMA_HPP
#define DAEMON_JWT_PRAGMA_HPP

#if defined(MSVC)
    #include "jwt/jwt.hpp"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
    #pragma GCC diagnostic ignored "-Wsign-compare"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
        #include "jwt/jwt.hpp"
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_JWT_PRAGMA_HPP
