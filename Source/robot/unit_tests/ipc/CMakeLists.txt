cmake_minimum_required (VERSION 2.8)

include_directories("${ROBOT_SOURCE_DIR}")

link_directories("${ROBOT_BINARY_DIR}/lib")

add_executable(test_server ipc_server_test.cpp)
add_executable(test_client ipc_client_test.cpp)

target_link_libraries(test_server libipc)
target_link_libraries(test_client libipc)
