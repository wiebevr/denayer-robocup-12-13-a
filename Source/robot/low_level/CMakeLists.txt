cmake_minimum_required (VERSION 2.8)

include_directories("${ROBOT_SOURCE_DIR}")

link_directories("${ROBOT_BINARY_DIR}/lib")

add_executable(low_level low_level.cpp serial.cpp main.cpp )
#add_executable(low_level low_level.cpp serial.cpp)
add_library(liblow_level low_level.cpp serial.cpp)

target_link_libraries(low_level libipc)
