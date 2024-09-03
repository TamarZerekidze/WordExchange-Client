cmake_minimum_required(VERSION 3.29)
project(ClientSide)

set(CMAKE_CXX_STANDARD 23)

add_executable(ClientSide main.cpp
        Client.cpp
        Client.h)

target_link_libraries(ClientSide ws2_32)