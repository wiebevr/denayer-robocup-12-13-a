cmake_minimum_required (VERSION 2.8)

include_directories("${ROBOT_SOURCE_DIR}")

link_directories("${ROBOT_BINARY_DIR}/lib")

add_library(libwifi wifi.cpp wifi.h game.pb.cc game.pb.h)
add_executable(wifi main.cpp wifi.cpp wifi.h game.pb.cc game.pb.h)

target_link_libraries(wifi libipc ${PROTOBUF_LIBRARY})
