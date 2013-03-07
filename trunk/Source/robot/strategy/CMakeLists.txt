cmake_minimum_required (VERSION 2.8)

include_directories("${ROBOT_SOURCE_DIR}")

link_directories("${ROBOT_BINARY_DIR}/lib")

set(strategy_source_files
    	keeper.cpp
	keeper.h
	kicker.cpp
    	kicker.h
    	robot.cpp
	robot.h
    	strategy.h
	strategy.cpp
)

add_executable(strategy ${strategy_source_files} main.cpp)
add_library(libstrategy ${strategy_source_files})

target_link_libraries(strategy libipc 
    # Add when working
    #liblow_level
    #libwifi
    )
