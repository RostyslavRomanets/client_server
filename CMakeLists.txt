cmake_minimum_required(VERSION 3.22.1)
project(client_server_homework)

set(CMAKE_CXX_STANDARD 20)

add_executable(client client.cpp Socket.h)

add_executable(server server.cpp Socket.h)
