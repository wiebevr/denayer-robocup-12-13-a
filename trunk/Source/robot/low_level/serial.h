/**  serial.h 
 *  Header file for the serial (rs232) communication 
 *  @author Jasper Vercammen & Ken Peersman
 */
        
#include <stdio.h>   /* Standard input/output definitions */
#include <string>  /* String function definitions */
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
    /** Filedescriptor of the serial connection */
    int fd;
    ssize_t size = 9;
    fd_set input_fdset;
    /** char array used as checksum for sending and recieving */
    unsigned char Cmd[10];
    /** The baudrate that we are using */
    speed_t baudrate;
    /** The databits used for the serial connection */
    int databits;
    /** The stopbits used for the serial conenction */
    int stopbits;
    /** The path that defines which serial port we are going to use */ 
    std::string path; 
    /** Function for converting a double to a baudratespeed 
     * @param baud Double value that represents the baudrate 
     * @return speed_t that gives the baudrate */
    speed_t convertBaud ( double baud );

public:
    /** Constructor */
    Serial();
    /** Constructor 
     * @param baud Integer that defines the baudrate
     * @param databits Integer that defines the number of databits
     * @param stopbits Integer that defines the number of stopbits 
     */
    Serial( std::string path,  int baud, int databits, int stopbits ); 
    /** Destructor */
    ~Serial();
    /** Function for intitialising the serial connection 
     * @return Gives 0 if init succeeded, gives 1 if failed */
    int init(void );
    
    int writeport(int, unsigned char *);
    int readport(int , unsigned char *);
    int getbaud( void );
    void checksum(unsigned char *);

protected:

};
