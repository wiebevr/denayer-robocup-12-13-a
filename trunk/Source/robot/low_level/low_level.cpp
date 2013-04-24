/** Low level class
 * Functions for low level communication 
 * @author Jasper
 * @author Ken
 */

#include <stdlib.h>
#include "low_level.h"
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
LowLevel::LowLevel()
{
    serial = new Serial( "/dev/ttyUSB0", 38400, 8 ,1 );
	// initialise the serial port. Returns 0 if succeeded
    if( serial->init() )
        exit(-1);
}

// ---------------------------------------------------------------------------
LowLevel::~LowLevel()
{
    delete serial;
}

// ---------------------------------------------------------------------------
void LowLevel::driveForward(int speed)
{
    drive(speed, 'F');
}

// ---------------------------------------------------------------------------
void LowLevel::driveBackwards(int speed)
{   
    drive(speed, 'B');
}

// ---------------------------------------------------------------------------
void LowLevel::turnLeft(int speed)
{   
    drive(speed, 'L');
}

// ---------------------------------------------------------------------------
void LowLevel::turnRight(int speed)
{ 
    drive(speed, 'R');
}

// ---------------------------------------------------------------------------
void LowLevel::stopMoving(void)
{
    string s = "s";
    serial->sWrite(s.data());
}

// ---------------------------------------------------------------------------
void LowLevel::ledTest(void)
{
   serial->sWrite("t");
}

// Private functions
// ---------------------------------------------------------------------------
float LowLevel::percentToValue(int percent, int max)
{
    float value = max / 100;
    value *= percent;
    return value;   
}

// ---------------------------------------------------------------------------
void LowLevel::drive(int speed, char direction)
{
    string buffer;
    char ss[15];
    float speed2 = percentToValue(speed, MAX_SPEED);
    speed = (int) speed2;
    sprintf(ss,"%d", speed);

    buffer = "d";
    buffer.append(" ");
    buffer.push_back(direction);
    buffer.append(" ");
    buffer.append(ss);
    buffer.append(" ");
    buffer.append(ss);

    serial->sWrite(buffer.data());
}

