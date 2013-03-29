#include "serial.h"
#include <string.h>
#include <iostream> 


// ---------------------------------------------------------------------------
Serial::Serial()
{
   this->baudrate = BAUDRATE;
   this->stopbits = STOPBITS;
   this->databits = DATABITS; 
   this->path = PORT_0;
}


// ---------------------------------------------------------------------------
Serial::~Serial()
{
	// Close the filedescriptor 
	close(fd);	
}

// ---------------------------------------------------------------------------
Serial::Serial( string path, double baud, int databits, int stopbits ) 
{
    this->baudrate = convertBaud( baud );
    this->stopbits = stopbits;
    this->databits = databits;
    this->path = path;
}

// ---------------------------------------------------------------------------
int Serial::init(void)
{
	struct termios old_flags; 
	struct termios term_attr;
	
	// Open the port, return -1 when failed
    if ((this->fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY)) == -1) 
    { 
        cout << "ERROR: Can open the port."; 
        return -1; 
    } 

    // Get the attributes of the port
    if (tcgetattr(this->fd, &term_attr) != 0) 
    { 
        cout << "ERROR: tcgetattr() failed."; 
        return -1; 
    } 

    // Set the baud rate
    cfsetispeed(&term_attr, this->baudrate);
    cfsetospeed(&term_attr, this->baudrate);

    // set some flags
    term_attr.c_cflag |= (CLOCAL | CREAD);
    term_attr.c_cflag &= ~PARENB;
    term_attr.c_cflag &= ~CSTOPB;
    term_attr.c_cflag &= ~CSIZE;
    term_attr.c_cflag |= CS8;

    // Send the new attributes to the port
    tcsetattr(this->fd, TCSANOW, &term_attr);

    return 0; 
}

// ---------------------------------------------------------------------------
int Serial::sWrite(const char *cmd )
{
	int check; 
	
	// Write the message to the filedescriptor
	check = write(this->fd, cmd, strlen(cmd));	
	
	// Check for errors 	
	if( check < 0) 
	{
		fputs("Write failed!\n", stderr);
		return -1;
	}
	else if(check == 0){
		printf("No bytes transmitted");
		return 0;
    }
	
	// End a commend always with a 'CR' (ascii = 13)
    char ending[1];
    ending[0] = 13;

	// Write out
    check = write(this->fd, ending,1);

	// check for errors again
    if( check < 0 )
    {
        fputs("write failed!\n",stderr);
        return -1;
    }

	return check;
}

// ---------------------------------------------------------------------------
int Serial::sRead( string &result) 
{
	// Max read = 100 characters
    char buf[1000];
	int max = 1000;				
	int state=1; 
	int receivedbyte=0; 
	
	// don't block serial read
	fcntl(fd, F_SETFL, FNDELAY);
	
	// Keep reading until nothing more to read or 1000 chars has been read
    while( state > 0 && receivedbyte < max) 
    { 
        state = read(fd,&buf[receivedbyte],1); 
        if( state > 0 ) 
            receivedbyte++; 
    } 
	// place the result in the variable
    result = buf;

	// return number of bytes that have been read
    return receivedbyte;
}

// ---------------------------------------------------------------------------
double Serial::getbaud( void ) 
{
	struct termios termAttr;
	double inputSpeed = -1;
	speed_t baudRate;
	tcgetattr(this->fd, &termAttr);
	/* Get the input speed. */
	baudRate = cfgetispeed(&termAttr);
	switch (baudRate) {
		case B0:      inputSpeed = 0; break;
		case B50:     inputSpeed = 50; break;
		case B110:    inputSpeed = 110; break;
		case B134:    inputSpeed = 134; break;
		case B150:    inputSpeed = 150; break;
		case B200:    inputSpeed = 200; break;
		case B300:    inputSpeed = 300; break;
		case B600:    inputSpeed = 600; break;
		case B1200:   inputSpeed = 1200; break;
		case B1800:   inputSpeed = 1800; break;
		case B2400:   inputSpeed = 2400; break;
		case B4800:   inputSpeed = 4800; break;
		case B9600:   inputSpeed = 9600; break;
		case B19200:  inputSpeed = 19200; break;
		case B38400:  inputSpeed = 38400; break;
	}
	return inputSpeed;
}

// ---------------------------------------------------------------------------
speed_t Serial::convertBaud ( double baud )
{
    int baud_int = 0;
    if ( baud < sizeof( int ) )
    {
        baud_int = baud;
    }
    else 
    {
        if ( baud == 38400 ) 
            return B38400;
    }
	switch (baud_int) {
		case 0:      return B0; break;
		case 50:     return B50; break;
		case 110:    return B110; break;
		case 134:    return B134; break;
		case 150:    return B150; break;
		case 200:    return B200; break;
		case 300:    return B300; break;
		case 600:    return B600; break;
		case 1200:   return B1200; break;
		case 1800:   return B1800; break;
		case 2400:   return B2400; break;
		case 4800:   return B4800; break;
		case 9600:   return B9600; break;
		case 19200:  return B19200; break;
	}

    return BAUDRATE;
}
