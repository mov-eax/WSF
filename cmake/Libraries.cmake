FIND_PACKAGE(OpenSSL REQUIRED)

IF(UNIX AND NOT APPLE)
  SET(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
ENDIF()

FIND_PACKAGE(Boost COMPONENTS program_options thread chrono system REQUIRED)
FIND_PACKAGE(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
MESSAGE("-- BOOST PATH \t\t" ${Boost_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIR})
MESSAGE("-- OPENSSL PATH \t" ${OPENSSL_INCLUDE_DIR})

SET(
  REQUIRED_LIBRARIES
  cpprestsdk::cpprest
  ${OPENSSL_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
)

# Options for drivers are default set to off
OPTION(MONGO "Enable Mongo C++ Drivers" OFF)
OPTION(REDIS "Enable Redis C++ Drivers" OFF)
OPTION(WSS "Enable Websocket C++ Drivers" OFF)

# Optional MONGO build files
IF (MONGO)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Mongo.cmake")
  MESSAGE("-- MongoDB now enabled, MONGO definition added")
  ADD_DEFINITIONS("-DMONGO")
ENDIF (MONGO)

# Optional REDIS build files
IF (REDIS)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Redis.cmake")
  MESSAGE("-- Redis now enabled, REDIS definition added")
  ADD_DEFINITIONS("-DREDIS")
ENDIF (REDIS)

# Optional WSS build files
IF (WSS)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/Websocket.cmake")
  MESSAGE("-- Websocket++ now enabled, WSS definition added")
  ADD_DEFINITIONS("-DWSS")
ENDIF (WSS)
