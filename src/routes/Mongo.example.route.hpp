#include "../Shared.hpp"
#include "../services/Server.service.hpp"
#include "../services/Mongo.example.service.hpp"

#ifndef _EXAMPLES_H
#define _EXAMPLES_H 1

namespace yungroute {
    namespace mongo {
        std::pair<web::http::status_code, std::string> insertOne() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::insertOne(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> insertMany() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::insertMany(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> updateOne() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::updateOne(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> updateMany() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::updateMany(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> findOne() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::findOne(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> findMany() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::findMany(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> deleteOne() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::deleteOne(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }

        std::pair<web::http::status_code, std::string> deleteMany() {
            web::json::value info;
            unsigned short status = 200;

            info = yungservice::metadata(info);
            info = yungservice::mongo::deleteMany(info);

            std::string payload = info.serialize().c_str();
            return make_pair(status, payload);
        }
    }
}

#endif
