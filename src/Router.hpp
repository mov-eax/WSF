#include "Shared.hpp"
#include "Config.hpp"
#include "routes/Server.route.hpp"
#include "routes/Mongo.example.route.hpp"

#ifndef _ROUTER_H
#define _ROUTER_H 1

namespace yungrouter {

    web::http::http_response generateResponse(web::http::status_code code, std::string payload) {
        web::http::http_response response (code);

        response.headers().add(U("Access-Control-Allow-Origin"), U(yungconfig::cors));
        response.set_body(payload, "application/json");

        return response;
    }

    void handler(web::http::http_request request) {
        web::uri requestUri = request.request_uri();
        std::string path = requestUri.path();
        std::string method = request.method();

        std::cout << "[" + request.method() + "] Request to " << path << std::endl;

        std::pair<web::http::status_code, std::string> response;
        response = yungroute::notFound();

        if (method == "GET") {
            if (path == "/") { response = yungroute::info(); }
            if (path == "/mongo/insert/one") { response = yungroute::mongo::insertOne(); }
            if (path == "/mongo/insert/many") { response = yungroute::mongo::insertMany(); }
            if (path == "/mongo/update/one") { response = yungroute::mongo::updateOne(); }
            if (path == "/mongo/update/many") { response = yungroute::mongo::updateMany(); }
            if (path == "/mongo/find/one") { response = yungroute::mongo::findOne(); }
            if (path == "/mongo/find/many") { response = yungroute::mongo::findMany(); }
            if (path == "/mongo/delete/one") { response = yungroute::mongo::deleteOne(); }
            if (path == "/mongo/delete/many") { response = yungroute::mongo::deleteMany(); }
        }

        request.reply(generateResponse(response.first, response.second));
    }

}

#endif
