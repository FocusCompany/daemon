//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_ZMQ_PRAGMA_HPP
#define DAEMON_ZMQ_PRAGMA_HPP

#if defined(MSVC)
    #include "zmq.hpp"
    #include "zmq_addon.hpp"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
        #include "zmq.hpp"
        #include "zmq_addon.hpp"
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_ZMQ_PRAGMA_HPP
