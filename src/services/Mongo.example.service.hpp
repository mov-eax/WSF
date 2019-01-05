#include "../Shared.hpp"

#ifndef _MONGOSAMPLE_H
#define _MONGOSAMPLE_H 1

namespace yungservice {
    namespace mongo {
        web::json::value insertOne(web::json::value result) {
            web::json::value sampleData;
            sampleData["hello"] = web::json::value::string("world");

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::insertOne("test", sampleData);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }


            result["insertedData"] = sampleData;
            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value insertMany(web::json::value result) {
            web::json::value sampleData;
            sampleData[0]["hello"] = web::json::value::string("world");
            sampleData[1]["hello"] = web::json::value::string("world");
            sampleData[2]["hello"] = web::json::value::string("world 1");
            sampleData[3]["hello"] = web::json::value::string("world 2");
            sampleData[4]["hello"] = web::json::value::string("world 3");

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::insertMany("test", sampleData);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }


            result["insertedData"] = sampleData;
            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value updateOne(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            web::json::value newData;
            newData["updated"] = true;

            web::json::value options;
            options["upsert"] = true;

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::updateOne("test", filterData, newData, options);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value updateMany(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            web::json::value newData;
            newData["updated_all"] = true;

            web::json::value options;
            options["upsert"] = true;

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::updateMany("test", filterData, newData, options);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value findOne(web::json::value result) {
            web::json::value placeholder = web::json::value::parse("{}");

            if (MONGOCXX) {
                auto task = yungmongo::findOne("test", placeholder);
                result["data"] = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            return result;
        }

        web::json::value findMany(web::json::value result) {
            web::json::value placeholder = web::json::value::parse("{}");

            if (MONGOCXX) {
                auto task = yungmongo::findMany("test", placeholder);
                result["data"] = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            return result;
        }

        web::json::value deleteOne(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world 2");

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::deleteOne("test", filterData);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value deleteMany(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            bool success = false;

            if (MONGOCXX) {
                auto task = yungmongo::deleteMany("test", filterData);
                success = task.get();
            } else {
                result["message"] = web::json::value::string("MongoDB Drivers are not enabled");
            }

            result["success"] = web::json::value(success);

            return result;
        }
    }
}

#endif
