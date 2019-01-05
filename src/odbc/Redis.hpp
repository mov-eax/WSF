#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _REDIS_H
#define _REDIS_H 1

namespace yungredis {
    redisContext *context;

    pplx::task<bool> init() {
        return pplx::task<bool>([=] {
            try {
                struct timeval timeout = { yungconfig::redisTimeout, 0 };
                context = redisConnectWithTimeout(yungconfig::redis.c_str(), yungconfig::redisPort, timeout);
                return true;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    void ping() {

    }
}

#endif
