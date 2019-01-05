#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _REDIS_H
#define _REDIS_H 1

namespace yungredis {

    pplx::task<bool> init() {
        return pplx::task<bool>([=] {
            return false;
        });
    }
    
}

#endif
