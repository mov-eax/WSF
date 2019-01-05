CMAKE_MINIMUM_REQUIRED(VERSION 3.7) # 3.7 is LTS as of today
SET(CMAKE_CXX_STANDARD 11) # Most syntax of the libraries require *atleast* C++11 syntax standards

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall ${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# These definitions make sure UNIX OSes don't throw errors on build
if (UNIX)
  ADD_DEFINITIONS(-Wno-sign-compare -Wno-enum-compare)
endif (UNIX)

PROJECT(TestsForYungCPP)

INCLUDE("${CMAKE_CURRENT_LIST_DIR}/../cmake/Base.cmake")

# Required for tests
FIND_PACKAGE(Boost COMPONENTS unit_test_framework)

SET(
  REQUIRED_LIBRARIES
  ${REQUIRED_LIBRARIES}
  Boost::unit_test_framework
)

ENABLE_TESTING()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../src)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../src)

ADD_EXECUTABLE(
    ConfigTest
    Config.test.cpp
)

TARGET_LINK_LIBRARIES(ConfigTest ${REQUIRED_LIBRARIES})
TARGET_COMPILE_DEFINITIONS(ConfigTest PRIVATE BOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(
    ServerDataTest
    ServerData.test.cpp
)

TARGET_LINK_LIBRARIES(ServerDataTest ${REQUIRED_LIBRARIES})
TARGET_COMPILE_DEFINITIONS(ServerDataTest PRIVATE BOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(
    MongoShellTest
    Mongo.shell.test.cpp
)

TARGET_LINK_LIBRARIES(MongoShellTest ${REQUIRED_LIBRARIES})
TARGET_COMPILE_DEFINITIONS(MongoShellTest PRIVATE BOOST_TEST_DYN_LINK)

ADD_TEST(
    TestConfig
    ConfigTest
)

ADD_TEST(
    TestServerData
    ServerDataTest
)

ADD_TEST(
    TestMongoShell
    MongoShellTest
)
