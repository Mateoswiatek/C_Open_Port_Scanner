cmake_minimum_required(VERSION 3.24)
project(SOCKET_SKANER C)

set(CMAKE_C_STANDARD 99)

link_libraries(ws2_32 wsock32)

add_executable(SOCKET_SKANER main.c)
