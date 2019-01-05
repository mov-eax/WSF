CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
SET(CMAKE_CXX_STANDARD 11)

# These definitions make sure UNIX OSes don't throw errors on build
if (UNIX)
  ADD_DEFINITIONS(-Wno-sign-compare -Wno-enum-compare)
endif (UNIX)

PROJECT(YungCPP)

INCLUDE("${CMAKE_CURRENT_LIST_DIR}/cmake/Base.cmake")

# Create executable
ADD_EXECUTABLE(server src/Server.cpp)

# Link libraries
TARGET_LINK_LIBRARIES(
    server
    PRIVATE
    ${REQUIRED_LIBRARIES}
)

# Link definitions
TARGET_COMPILE_DEFINITIONS(
  server
  PRIVATE
  ${REQUIRED_DEFINITIONS}
)
