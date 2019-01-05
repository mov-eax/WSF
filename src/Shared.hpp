#ifndef _SHARED_H
#define _SHARED_H 1

#include "boost/program_options.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/ws_client.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <chrono>

// MongoDB Drivers
#ifdef MONGOCXX
    #include <bsoncxx/builder/stream/document.hpp>
    #include <bsoncxx/builder/basic/array.hpp>
    #include <bsoncxx/builder/basic/document.hpp>
    #include <bsoncxx/builder/basic/kvp.hpp>
    #include <bsoncxx/json.hpp>
    #include <bsoncxx/types.hpp>
    #include <bsoncxx/stdx/make_unique.hpp>
    #include <bsoncxx/stdx/optional.hpp>
    #include <bsoncxx/stdx/string_view.hpp>

    #include <mongocxx/client.hpp>
    #include <mongocxx/pool.hpp>
    #include <mongocxx/instance.hpp>
    #include <mongocxx/options/find.hpp>
    #include <mongocxx/uri.hpp>

    #include "odbc/Mongo.hpp"
#else
    #define MONGOCXX 0
    #include "odbc/Mongo.shell.hpp"
#endif

// MySQL Drivers
#ifdef MYSQLCXX
    #include <jdbc/mysql_driver.h>
    #include <jdbc/mysql_connection.h>
    #include <jdbc/mysql_error.h>

    #include <jdbc/cppconn/build_config.h>
    #include <jdbc/cppconn/connection.h>
    #include <jdbc/cppconn/datatype.h>
    #include <jdbc/cppconn/driver.h>
    #include <jdbc/cppconn/exception.h>
    #include <jdbc/cppconn/metadata.h>
    #include <jdbc/cppconn/parameter_metadata.h>
    #include <jdbc/cppconn/prepared_statement.h>
    #include <jdbc/cppconn/resultset_metadata.h>
    #include <jdbc/cppconn/resultset.h>
    #include <jdbc/cppconn/sqlstring.h>
    #include <jdbc/cppconn/statement.h>
    #include <jdbc/cppconn/variant.h>
    #include <jdbc/cppconn/warning.h>

    #include "odbc/Mysql.hpp"
#else
    #define MYSQLCXX 0
    #include "odbc/Mysql.shell.hpp"
#endif

// Redis Drivers
#ifdef REDISCXX
    #include "hiredis.h"
    #include "async.h"
    #include "adapters/macosx.h"
    #include "odbc/Redis.hpp"
#else
    #define REDISCXX 0
    #include "odbc/Redis.shell.hpp"
#endif

// Websocket Drivers
#ifdef WSSCXX

#else
    #define WSSCXX 0
#endif

#endif
