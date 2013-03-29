############################################################
#
#   Author: Maarten Vandersteegen
#   Date:   03/2012
#   Target: Wifiserver test app
#
############################################################

CXX= g++
CXXFLAGS = -c -Wall
LDFLAGS = -lpthread -pthread

#google protocol buffers support
CXXFLAGS += `pkg-config --cflags`
LDFLAGS += `pkg-config --cflags`

all: clean test_server test_client

tests: t_vision_data

########
#linking
########

test_server: test_server.o wifiserver.o vision_data.o lib_crc.o log.o staticlog.o thread.o
	$(CXX) $(LDFLAGS) test_server.o wifiserver.o vision_data.o lib_crc.o log.o staticlog.o thread.o -o $@

test_client: test_client.o wificlient.o vision_data.o lib_crc.o log.o staticlog.o thread.o
	$(CXX) $(LDFLAGS) test_client.o wificlient.o vision_data.o lib_crc.o log.o staticlog.o thread.o -o $@
##########
#compiling
##########

#testing program
test_server.o: test_server.cc wifiserver.h log.h
	$(CXX) $(CXXFLAGS) test_server.cc

#testing program
test_client.o: test_client.cc wificlient.h log.h
	$(CXX) $(CXXFLAGS) test_client.cc


#the server
wifiserver.o: wifiserver.cc wifiserver.h thread.h log.h ../../image_processing/public\ data/vision_data.h
	$(CXX) $(CXXFLAGS) wifiserver.cc

#generated google protocol class
vision_data.o: ../shared/vision_data.cpp ../shared/vision_data.h 
	$(CXX) $(CXXFLAGS) ../../image_processing/public\ data/vision_data.cpp

#CRC check header lib	
lib_crc.o: lib_crc.c lib_crc.h
	$(CXX) $(CXXFLAGS) lib_crc.c

#header libs from last year (log, staticlog, thread)
log.o: log.cc log.h staticlog.h
	$(CXX) $(CXXFLAGS) log.cc

staticlog.o: staticlog.cc staticlog.h
	$(CXX) $(CXXFLAGS) staticlog.cc

thread.o: thread.cc thread.h
	$(CXX) $(CXXFLAGS) thread.cc

#########
#cleaning
#########

clean:
	rm -rf *.o test_server test_client log.txt
	
	
#######
# Tests
#######
t_vision_data: test_vision_data.o vision_data.o