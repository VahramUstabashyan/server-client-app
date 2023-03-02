cmake_minimum_required(VERSION 3.09)
project(server_client_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(client_app
        client.cpp
        Client.hpp
        ClientCommandHandler.hpp
        ClientCommandHandler.cpp)
target_link_libraries(client_app PUBLIC ${Boost_LIBRARIES})

add_executable(server_app
        server.cpp
        Server.hpp
        Server.cpp
        Connection.hpp
        Connection.cpp)
target_link_libraries(server_app PUBLIC ${Boost_LIBRARIES})