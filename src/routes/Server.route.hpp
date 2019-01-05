#include "../Shared.hpp"
#include "../services/Server.service.hpp"

#ifndef _SERVERINFO_H
#define _SERVERINFO_H 1

namespace yungroute {
    std::pair<web::http::status_code, std::string> info() {
        web::json::value info;
        unsigned short status = 200;

        info = yungservice::metadata(info);

        std::string payload = info.serialize().c_str();
        return make_pair(status, payload);
    }

    std::pair<web::http::status_code, std::string> notFound() {
        web::json::value info;
        unsigned short status = 404;

        info = yungservice::metadata(info);
        info["message"] = web::json::value::string("Path not found...");

        std::string payload = info.serialize().c_str();
        return make_pair(status, payload);
    }
}

#endif
