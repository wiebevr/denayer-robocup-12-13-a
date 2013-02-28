/*  serial.h 
 *  Header file for the serial (rs232) communication 
 *  @author Jasper Vercammen & Ken Peersman
 */
        
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/types.h>
#include <sys/stat.h>
       
#define BAUDRATE B38400
#define PORT_0 "/dev/ttyUSB0"
#define DATABITS 8 
#define STOPBITS 1
#define FLOWCONTROL 0
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1


class Serial {

private:
    volatile int STOP=FALSE; 
    int fd;
    ssize_t size = 9;
    fd_set input_fdset;
    speed_t baudrate;
    int databits;
    int stopbits;
    /* Function for intitialising the serial port */
    int initport(void );
    /* Function for converting a double to a baudratespeed 
     * @param baud Double value that represents the baudrate 
     * @return speed_t that gives the te baudrate */
    speed_t convertBaud ( double baud )

public:
    /* Constructor */
    Serial::Serial();
    /* Constructor 2 
     * @param baud Integer that defines the baudrate
     * @param databits Integer that defines the number of databits
     * @param stopbits Integer that defines the number of stopbits 
     */
    Serial::Serial( int baud, int databits, int stopbits ); 
    /* Destructor */
    Serial::~Serial();
    int writeport(int, unsigned char *);
    int readport(int , unsigned char *);
    int getbaud(int );
    void checksum(unsigned char *);

protected:

}
