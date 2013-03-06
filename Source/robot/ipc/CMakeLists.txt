cmake_minimum_required (VERSION 2.6)

include_directories(${ROBOT_SOURCE_DIR})

set(shared_source_files
    ipc_socket.cpp
    ipc_socket.h
    ipc_server.cpp
    ipc_server.h
    ipc_client.cpp
    ipc_client.h
)

add_library(libipc ${shared_source_files})
