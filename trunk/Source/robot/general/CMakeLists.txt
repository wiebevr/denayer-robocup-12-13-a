cmake_minimum_required (VERSION 2.8)

include_directories("${ROBOT_SOURCE_DIR}")

link_directories("${ROBOT_BINARY_DIR}/lib")

set(general_source_files
    main.cpp
)

add_executable(bell-e ${general_source_files})

target_link_libraries(general ipc wifi strategy low_level)
