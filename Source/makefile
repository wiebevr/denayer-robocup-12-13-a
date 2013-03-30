############################################################
#
#   Author: Sven Meys
#   Date:   03/2012
#   Target: Everything
#
############################################################

CXX= g++
CXXFLAGS = -c -g -Wall
LDFLAGS = -lpthread -pthread -lstdc++
LDFLAGS_VISION = -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc

#google protocol buffers support
#CXXFLAGS += `pkg-config --cflags`
#LDFLAGS += `pkg-config --cflags`

#Source dirs
_SHARED=shared
_ROBOT=robot
_VISION=vision
_TEST=tests

#Build dirs
_BUILD=build
B_LIB=${_BUILD}/lib
B_ROBOT=${_BUILD}/${_ROBOT}
B_VISION=${_BUILD}/${_VISION}
B_TEST=${_BUILD}/${_TEST}

BUILDDIRS=${B_LIB} ${B_ROBOT} ${B_VISION} ${B_TEST}

#Main calls
all: 	clean tests vision robot
	echo "Building everything."

#Cleaning	
clean:
	echo "Cleaning build data."
	rm -rf ${_BUILD}

clean_test:
	@echo "Cleaning test data."
	rm -rf ${_BUILD}/${_TEST}
clean_vision:
	@echo "Cleaning vision data."
	rm -rf ${_BUILD}/${_VISION}
clean_robot:
	@echo "Cleaning robot data."
	rm -rf ${_BUILD}/${_ROBOT}
	
dirs:
	@mkdir -p ${BUILDDIRS}

#######
# linking main programs
#######
tests: 	dirs test_vision_data test_server test_client test_lowlevel test_strategy
	@echo BUILD SUCCESFUL
	
vision: dirs wifiserver.o vision_data.o vision.o vision_field.o vision_balls.o vision_DataCircle.o vision_robot.o lib_crc.o log.o staticlog.o thread.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${LDFLAGS_VISION} ${_VISION}/main.cpp -o ${B_TEST}/$@ \
	${B_LIB}/wifiserver.o ${B_LIB}/lib_crc.o ${B_LIB}/log.o ${B_LIB}/staticlog.o ${B_LIB}/thread.o \
	${B_LIB}/vision.o ${B_LIB}/vision_field.o ${B_LIB}/vision_balls.o ${B_LIB}/vision_DataCircle.o ${B_LIB}/vision_robot.o \
	${B_LIB}/vision_data.o
	@echo BUILD SUCCESFUL
	
	
robot: dirs wificlient.o vision_data.o lib_crc.o log.o staticlog.o thread.o low_level.o serial.o keeper.o kicker.o robot.o strategy.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_ROBOT}/main.cpp -o ${B_TEST}/$@ \
	${B_LIB}/wificlient.o ${B_LIB}/lib_crc.o ${B_LIB}/log.o ${B_LIB}/staticlog.o ${B_LIB}/thread.o \
	${B_LIB}/low_level.o ${B_LIB}/serial.o \
	${B_LIB}/strategy.o ${B_LIB}/keeper.o ${B_LIB}/kicker.o ${B_LIB}/robot.o \
	${B_LIB}/vision_data.o
	@echo BUILD SUCCESFUL
	

########
#linking tests
########
test_vision_data: vision_data.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_TEST}/$@.cc ${B_LIB}/vision_data.o -o ${B_TEST}/$@
	@./${B_TEST}/$@

test_server: dirs wifiserver.o vision_data.o lib_crc.o log.o staticlog.o thread.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_TEST}/test_server.cc -o ${B_TEST}/$@ \
	${B_LIB}/wifiserver.o ${B_LIB}/lib_crc.o ${B_LIB}/log.o ${B_LIB}/staticlog.o ${B_LIB}/thread.o \
	${B_LIB}/vision_data.o

test_client: dirs wificlient.o lib_crc.o log.o staticlog.o thread.o vision_data.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_TEST}/test_client.cc -o ${B_TEST}/$@ \
	${B_LIB}/wificlient.o ${B_LIB}/lib_crc.o ${B_LIB}/log.o ${B_LIB}/staticlog.o ${B_LIB}/thread.o \
	${B_LIB}/vision_data.o																			 

test_lowlevel: dirs low_level.o serial.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_TEST}/test_low_level.cpp -o ${B_TEST}/$@ \
	${B_LIB}/low_level.o ${B_LIB}/serial.o
	
	
test_strategy: dirs strategy.o keeper.o kicker.o robot.o low_level.o serial.o vision_data.o
	@echo Building $@
	${CXX} ${LDFLAGS} ${_TEST}/test_strategy.cpp -o ${B_TEST}/$@ \
	${B_LIB}/strategy.o ${B_LIB}/keeper.o ${B_LIB}/kicker.o ${B_LIB}/robot.o \
	${B_LIB}/low_level.o ${B_LIB}/serial.o  \
	${B_LIB}/vision_data.o
	
########	
#compiling vision
########
vision.o: ${_VISION}/vision.cpp ${_VISION}/vision.h ${_VISION}/vision_robot.h ${_VISION}/vision_balls.h ${_VISION}/vision_field.h ${_VISION}/vision_DataCircle.h ${_SHARED}/vision_data.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/vision.cpp -lopencv

vision_field.o: ${_VISION}/vision_field.cpp ${_VISION}/vision_field.h 
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/vision_field.cpp -lopencv

vision_balls.o: ${_VISION}/vision_balls.cpp ${_VISION}/vision_balls.h 
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/vision_balls.cpp -lopencv

vision_DataCircle.o: ${_VISION}/vision_DataCircle.cpp ${_VISION}/vision_DataCircle.h 
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/vision_DataCircle.cpp -lopencv

vision_robot.o: ${_VISION}/vision_robot.cpp ${_VISION}/vision_robot.h 
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/vision_robot.cpp -lopencv
	
########
#compiling lowlevel
########

low_level.o: ${_ROBOT}/low_level/low_level.cpp ${_ROBOT}/low_level/low_level.h ${_ROBOT}/low_level/serial.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/low_level/low_level.cpp -o ${B_LIB}/$@

serial.o: ${_ROBOT}/low_level/serial.cpp ${_ROBOT}/low_level/serial.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/low_level/serial.cpp  -o ${B_LIB}/$@

########
#compiling strategy
########	
strategy.o: ${_ROBOT}/strategy/strategy.cpp ${_ROBOT}/strategy/strategy.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/strategy/strategy.cpp  -o ${B_LIB}/$@

robot.o: ${_ROBOT}/strategy/robot.cpp ${_ROBOT}/strategy/robot.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/strategy/robot.cpp  -o ${B_LIB}/$@
	
kicker.o: ${_ROBOT}/strategy/kicker.cpp ${_ROBOT}/strategy/kicker.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/strategy/kicker.cpp  -o ${B_LIB}/$@
	
keeper.o: ${_ROBOT}/strategy/keeper.cpp ${_ROBOT}/strategy/keeper.h
	${CXX} ${CXXFLAGS} ${_ROBOT}/strategy/keeper.cpp  -o ${B_LIB}/$@

########
#compiling wifi
########
#The server
wifiserver.o: ${_VISION}/wifiserver.cc ${_VISION}/wifiserver.h ${_SHARED}/thread.h ${_SHARED}/log.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_VISION}/wifiserver.cc

#The client
wificlient.o: ${_ROBOT}/wificlient.cc ${_ROBOT}/wificlient.h ${_SHARED}/thread.h ${_SHARED}/log.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_ROBOT}/wificlient.cc

vision_data.o: ${_SHARED}/vision_data.cpp ${_SHARED}/vision_data.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_SHARED}/vision_data.cpp

#CRC check header lib	
lib_crc.o: ${_SHARED}/lib_crc.c ${_SHARED}/lib_crc.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_SHARED}/lib_crc.c

#header libs from last year (log, staticlog, thread)
log.o: ${_SHARED}/log.cc ${_SHARED}/log.h ${_SHARED}/staticlog.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_SHARED}/log.cc

staticlog.o: ${_SHARED}/staticlog.cc ${_SHARED}/staticlog.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_SHARED}/staticlog.cc

thread.o: ${_SHARED}/thread.cc ${_SHARED}/thread.h
	${CXX} ${CXXFLAGS} -o ${B_LIB}/$@ ${_SHARED}/thread.cc
	
##########
#compiling
##########

#testing program
test_server.o: test_server.cc wifiserver.h log.h
	$(CXX) $(CXXFLAGS) test_server.cc

#testing program
test_client.o: test_client.cc wificlient.h log.h
	$(CXX) $(CXXFLAGS) test_client.cc


#generated google protocol class
#vision_data.o: ../shared/vision_data.cpp ../shared/vision_data.h 
#	$(CXX) $(CXXFLAGS) ../shared/vision_data.cpp





#########
#cleaning
#########


	
	
#######
# Tests
#######
t_vision_data: test_vision_data.o vision_data.o
