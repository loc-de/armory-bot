cmake_minimum_required(VERSION 3.14)
project(StrafeBot)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/socket.io-client-cpp)

include_directories(
    external/socket.io-client-cpp/src
    external/websocketpp
    src
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(StrafeBot ${SOURCES})

target_link_libraries(StrafeBot
    sioclient
)
