#include "serial.h"


// ---------------------------------------------------------------------------
Serial::Serial()
{
   this->baudrate = BAUDRATE;
   this->stopbits = STOPBITS;
   this->databits = DATABITS; 
}


// ---------------------------------------------------------------------------
Serial::~Serial()
{

}

// ---------------------------------------------------------------------------
Serial::Serial( int baud, int databits, int stopbits ); 
{
    this->baudrate = convertBaud( baud );
    this->stopbits = stopbits;
    this->databits = databits;
}


int main(void) {

	int counter, i;
	unsigned char Cmd[10];
	unsigned char Result[10];

	
	printf("open USB0......\n");
	printf("initPort: %d\n",initport());
	printf("baud after init  = %d\n", getbaud(fd));

	
	Cmd[0] = 0x02;		//       Module 2
	Cmd[1] = 0x06;		//	Get Axis Parameter (GAP) 
	Cmd[2] = 0xD1;		//	209 Get Encoder Position
	Cmd[3] = 0x01;		//	Encoder number 1
	Cmd[4] = 0; Cmd[5] = 0; Cmd[6] = 0; Cmd[7] = 0;
	checksum(Cmd);


	printf("write..."); 

	printf("%d bytes!\n",writeport(fd, Cmd));
	
	for(i = 0; i < 9; i++) printf("%d; ", Cmd[i]); printf("\n");
	
	usleep(500000);		// sleep 500 ms
	
	fcntl(fd, F_SETFL, FNDELAY); // don't block serial read
	
	printf("read...\n");
	printf("%d bytes\n", readport(fd,Result));
	
	printf("read    = ");	for(i = 0; i < 9; i++) printf("%d; ", Cmd[i]); printf("\n");

	close(fd);	ssize_t size = 10;
	return 0;
}



void checksum(unsigned char *Cmd){
	int i; Cmd[8] = 0;
	for(i = 0; i < 8; i++) Cmd[8] += Cmd[i];
	return;
}


int writeport(int fd, unsigned char *Cmd)
{
	int check; char n;
	fd_set nfds;
	struct timeval timeout;


	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
 
	printf("write(2) function\n");


	check = write(fd, Cmd, 	size);		//originally strlen(bCmd) but there are some zero Bytes in the Cmd
	
	tcdrain(fd); //waits until all output written to the object referred to by fildes is transmitted

	if (check < 0) {
		fputs("write failed!\n", stderr);
		close(fd);
		return -1;
	}
	else if(check == 0){
		printf("no bytes transmitted");
		close(fd);
		return 0;
	}

return check;                                                                       	                                
}

int readport(int fd, unsigned char *Result) 
{
	printf("read(2) function\n");
	int max = 12;				// 9 bytes as an answer to a Command
	int    state=1; 
	int    receivedbyte=0; 

    while( state > 0 && receivedbyte < max) 
        { 
        state = read(fd,&Result[receivedbyte],1); 
        if( state > 0 ) 
            receivedbyte++; 
        } 
    return    receivedbyte;
}

int getbaud(int fd) 
{
	//printf("getbaud\n");
	struct termios termAttr;
	int inputSpeed = -1;
	speed_t baudRate;
	tcgetattr(fd, &termAttr);
	/* Get the input speed.                              */
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
speed_t convertBaud ( double baud )
{
	switch (baud) {
		case 0:      return B0; break;
		case 50:     return = B50; break;
		case 110:    return = B110; break;
		case 134:    return = B134; break;
		case 150:    return = B150; break;
		case 200:    return = B200; break;
		case 300:    return = B300; break;
		case 600:    return = B600; break;
		case 1200:   return = B1200; break;
		case 1800:   return = B1800; break;
		case 2400:   return = B2400; break;
		case 4800:   return = B4800; break;
		case 9600:   return = B9600; break;
		case 19200:  return = B19200; break;
		case 38400:  return = B38400; break;
	}

    return BAUDRATE;
}

int initport(void){
	struct termios old_flags; 
	struct termios term_attr;

    if ((fd = open(PORT_0, O_RDWR | O_NOCTTY | O_NDELAY)) == -1) 
    { 
        perror("terminal: Can't open device " PORT_0); 
        return(1); 
    } 
    /* configurare RS232 */ 
    if (tcgetattr(fd, &term_attr) != 0) 
    { 
        perror("terminal: tcgetattr() failed"); 
        return(1); 
    } 
    /* save old flags */ 
    old_flags = term_attr; 
    cfsetispeed(&term_attr, BAUDRATE); 
    cfsetospeed(&term_attr, BAUDRATE); 
    cfmakeraw(&term_attr);

	term_attr.c_iflag = 0; 
	term_attr.c_oflag = 0; 
	term_attr.c_lflag = 0;
	term_attr.c_cflag = 0;

 
    term_attr.c_cc[VMIN] = 1;                 // finished after one bye 
    term_attr.c_cc[VTIME] = 8;             // or 800ms time out 

    term_attr.c_cflag &= ~(PARENB | CSTOPB | CSIZE); //added
    term_attr.c_cflag |= (BAUDRATE | CS8 | CRTSCTS | CLOCAL | HUPCL);  // using flow control via CTS/RTS 


	term_attr.c_oflag |= (OPOST | ONLCR); 


	 /* save old configuration */ 

  old_flags = term_attr; 
  term_attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 

                                                            
    if (tcsetattr(fd, TCSAFLUSH, &term_attr) != 0) 
        { 
        perror("terminal: tcsetattr() failed"); 
        return(1); 
        } 

    /* change standard input */ 
    if (tcgetattr(STDIN_FILENO, &term_attr) != 0) 
        { 
        perror("terminal: tcgetattr() failed"); 
        return(1); 
        } 

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_attr) != 0) 
        perror("terminal: tcsetattr() failed"); 

    FD_SET(fd, &input_fdset);                          /* Select the first channel 1 */ 

    return 0; 
}