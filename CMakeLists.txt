cmake_minimum_required(VERSION 3.09)
project(server_client_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(client_app
        client_app.cpp
        client/Client.hpp
        client/Client.cpp
        client/ClientCommandHandler.hpp
        client/ClientCommandHandler.cpp
        connection/Connection.hpp
        connection/Connection.cpp
        observer/ConnectionObserver.hpp
        observer/ConnectionObserver.cpp
        observer/Observable.hpp
        observer/Observable.cpp)
target_link_libraries(client_app PUBLIC ${Boost_LIBRARIES})

add_executable(server_app
        server_app.cpp
        server/Server.hpp
        server/Server.cpp
        connection/Connection.hpp
        connection/Connection.cpp
        observer/ConnectionObserver.hpp
        observer/ConnectionObserver.cpp
        observer/Observable.hpp
        observer/Observable.cpp)
target_link_libraries(server_app PUBLIC ${Boost_LIBRARIES})