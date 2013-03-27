all : lowlevel 
CFLAGS = -g
LFLAGS = -lstdc++

main.o : main.cpp low_level.h
	g++ -c $(CFLAGS) $(LFLAGS) main.cpp

low_level.o: low_level.cpp low_level.h serial.h
	g++ -c $(CFLAGS) low_level.cpp

serial.o: serial.cpp serial.h
	g++ -c $(CFLAGS) serial.cpp

lowlevel : main.o low_level.o serial.o 
	g++ -o lowlevel main.o low_level.o serial.o
		
