#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _MONGO_H
#define _MONGO_H 1

namespace yungmongo {
    mongocxx::instance MongoInstance{};
    mongocxx::uri uri(yungconfig::mongo);
    mongocxx::pool pool{uri};

    std::string db = yungconfig::mongodb;

    pplx::task<bool> insertOne(std::string collection, web::json::value data) {
        return pplx::task<bool>([=] {
            try {
                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                auto dataString = data.serialize().c_str();
                auto document = bsoncxx::from_json(dataString);

                auto done = client.insert_one(document.view());

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    pplx::task<bool> insertMany(std::string collection, web::json::value data) {
        return pplx::task<bool>([=] {
            try {
                if (!data.is_array()) return false;

                auto bulkData = data.as_array();

                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                std::vector<bsoncxx::document::value> documents;

                for (int i = 0; i < bulkData.size(); i++) {
                    std::string documentString = bulkData[i].serialize().c_str();
                    auto document = bsoncxx::from_json(documentString);
                    documents.push_back(bsoncxx::document::value(document.view()));
                }

                auto done = client.insert_many(documents);

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    mongocxx::options::update updateOptions(web::json::value params) {
        mongocxx::options::update options{};

        if (params["upsert"].is_boolean()) {
            options.upsert(params["upsert"].as_bool());
        }

        return options;
    }

    pplx::task<bool> updateOne(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
        return pplx::task<bool>([=] {
            try {
                auto options = updateOptions(optionsParams);

                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                web::json::value newData;
                newData["$set"] = data;

                auto dataDocument = bsoncxx::from_json(newData.serialize().c_str());
                auto filterDocument = bsoncxx::from_json(filter.serialize().c_str());

                auto done = client.update_one(filterDocument.view(), dataDocument.view(), options);

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    pplx::task<bool> updateMany(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
        return pplx::task<bool>([=] {
            try {
                auto options = updateOptions(optionsParams);

                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                web::json::value newData;
                newData["$set"] = data;

                auto dataDocument = bsoncxx::from_json(newData.serialize().c_str());
                auto filterDocument = bsoncxx::from_json(filter.serialize().c_str());

                auto done = client.update_many(filterDocument.view(), dataDocument.view(), options);

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    mongocxx::options::find findOptions(web::json::value params) {
        mongocxx::options::find options{};

        if (params["sort"].is_object()) {
            auto optionsSort = bsoncxx::from_json(params["sort"].serialize().c_str());
            options.sort(optionsSort.view());
        }

        if (params["skip"].is_integer()) {
            options.skip(params["skip"].as_integer());
        }

        if (params["limit"].is_integer()) {
            options.limit(params["limit"].as_integer());
        }

        return options;
    }

    pplx::task<web::json::value> findOne(std::string collection, web::json::value filter, web::json::value optionsParams = web::json::value::parse("{}")) {
        return pplx::task<web::json::value>([=] {
            web::json::value result;

            try {
                auto options = findOptions(optionsParams);

                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                auto filterString = filter.serialize().c_str();
                auto filterDocument = bsoncxx::from_json(filterString);

                auto resultDocument = client.find_one(filterDocument.view(), options);

                if (resultDocument) {
                    auto resultView = resultDocument->view();

                    auto resultString = bsoncxx::to_json(resultView);
                    auto result = web::json::value::parse(resultString);

                    return result;
                } else {
                    result = web::json::value::parse("{}");
                    return result;
                }
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                result["e"] = web::json::value(e.what());

                return result;
            }
        });
    }

    pplx::task<web::json::value> findMany(std::string collection, web::json::value filter, web::json::value optionsParams = web::json::value::parse("{}")) {
        return pplx::task<web::json::value>([=] {
            web::json::value documents;
            try {
                auto options = findOptions(optionsParams);

                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                auto filterString = filter.serialize().c_str();
                auto filterDocument = bsoncxx::from_json(filterString);

                auto resultCursor = client.find(filterDocument.view(), options);

                int i = 0;
                for (auto&& document : resultCursor) {
                    std::string documentString = bsoncxx::to_json(document);
                    documents[i] = web::json::value::parse(documentString);
                    i++;
                }

                if (i == 0) documents = web::json::value::parse("[]");

                return documents;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                documents = web::json::value::parse("[]");
                return documents;
            }
        });
    }

    pplx::task<bool> deleteOne(std::string collection, web::json::value filter) {
        return pplx::task<bool>([=] {
            try {
                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                auto filterString = filter.serialize().c_str();
                auto filterDocument = bsoncxx::from_json(filterString);

                auto done = client.delete_one(filterDocument.view());

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }

    pplx::task<bool> deleteMany(std::string collection, web::json::value filter) {
        return pplx::task<bool>([=] {
            web::json::value documents;
            try {
                auto poolInstance = pool.acquire();
                auto client = (*poolInstance)[db][collection];

                auto filterString = filter.serialize().c_str();
                auto filterDocument = bsoncxx::from_json(filterString);

                auto done = client.delete_many(filterDocument.view());

                return done ? true : false;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
                return false;
            }
        });
    }
}

#endif
