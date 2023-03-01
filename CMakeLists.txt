cmake_minimum_required(VERSION 3.22)
project(server_client_app)

set(CMAKE_CXX_STANDARD 14)

add_executable(client_app
        client.cpp
        Client.hpp
        ClientCommandHandler.hpp
        ClientCommandHandler.cpp)

add_executable(server_app
        server.cpp
        Server.hpp
        Server.cpp
        Connection.hpp
        Connection.cpp)