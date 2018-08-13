//
// Created by pasteu_e on 5/5/18.
//

#ifndef DAEMON_LIGHTCONF_PRAGMA_HPP
#define DAEMON_LIGHTCONF_PRAGMA_HPP

#define WEBVIEW_IMPLEMENTATION

#if defined(MSVC)
    #include "webview.h"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
        #include "webview.h"
    #pragma GCC diagnostic pop
#endif

#endif //DAEMON_LIGHTCONF_PRAGMA_HPP
