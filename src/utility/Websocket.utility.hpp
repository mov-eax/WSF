#include "../Shared.hpp"

#ifndef _WEBSOCKET_H
#define _WEBSOCKET_H 1

namespace yungutil {

    pplx::task<web::websockets::client::websocket_callback_client> listen(std::string socketUri) {
        return pplx::task<web::websockets::client::websocket_callback_client>([=] {
            web::websockets::client::websocket_callback_client newSocket;

            try {
                newSocket.connect(socketUri).wait();
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            return newSocket;
        });
    }

}

#endif
