# Preset OpenSSL directories
IF (NOT OPENSSL_ROOT_DIR)
  MESSAGE("-- Setting default OpenSSL Root Directory")
  SET(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
ENDIF (NOT OPENSSL_ROOT_DIR)

IF (NOT OPENSSL_LIBRARIES)
  MESSAGE("-- Setting default OpenSSL Library Directory")
  SET(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
ENDIF (NOT OPENSSL_LIBRARIES)



MESSAGE("-- OPENSSL ROOT PATH \t" ${OPENSSL_ROOT_DIR})
MESSAGE("-- OPENSSL LIBRARIES \t" ${OPENSSL_LIBRARIES})

# Required for YungC++ to compile
FIND_PACKAGE(OPENSSL REQUIRED)
FIND_PACKAGE(Boost COMPONENTS program_options thread chrono system REQUIRED)
FIND_PACKAGE(cpprestsdk REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

MESSAGE("-- BOOST PATH \t\t" ${Boost_INCLUDE_DIR})

SET(
  REQUIRED_LIBRARIES
  cpprestsdk::cpprest
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
)

# Options for drivers are default set to off
OPTION(MONGOCXX "Enable Mongo C++ Drivers" OFF)
OPTION(REDISCXX "Enable Redis C++ Drivers" OFF)
OPTION(MYSQLCXX "Enable Mongo C++ Drivers" OFF)
OPTION(WSSCXX "Enable Websocket C++ Drivers" OFF)

# Optional MongoCXX build files
IF (MONGOCXX)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Mongo.cmake")
  MESSAGE("-- MongoDB now enabled, MONGOCXX definition added")
  ADD_DEFINITIONS("-DMONGOCXX")
ENDIF (MONGOCXX)

# Optional MySQLCXX build files
IF (MYSQLCXX)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Mysql.cmake")
  MESSAGE("-- MySQL now enabled, MYSQLCXX definition added")
  ADD_DEFINITIONS("-DMYSQLCXX")
ENDIF (MYSQLCXX)

# Optional RedisCXX build files
IF (REDISCXX)
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Redis.cmake")
  MESSAGE("-- Redis now enabled, REDISCXX definition added")
  ADD_DEFINITIONS("-DREDISCXX")
ENDIF (REDISCXX)

# Optional WSSCXX build files
IF (WSSCXX)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Websocket.cmake")
  MESSAGE("-- Websocket++ now enabled, WSSCXX definition added")
  ADD_DEFINITIONS("-DWSSCXX")
ENDIF (WSSCXX)
