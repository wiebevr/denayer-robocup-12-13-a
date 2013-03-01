/* Low level class
 * Functions for low level communication 
 * @author Jasper
 * @author Ken
 */

#include "low_level.h"
#include "string.h"

// ---------------------------------------------------------------------------
LowLevel::LowLevel()
{
    serial = new Serial(38400, 8 ,1);
    if(serial->init())
        exit();
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
   serial->write("s\r");
}

// ---------------------------------------------------------------------------
void LowLevel::ledTest(void)
{
   serial->write("t\r");
}

// Private functions
// ---------------------------------------------------------------------------
float percentToValue(int percent, int max)
{
    float value = max / 100;
    value *= percent;
    return value;   
}

// ---------------------------------------------------------------------------
void LowLevel::drive(int speed, char richting)
{
    string buffer;
    stringstream ss;
    speed = percentToValue(speed, MAX_SPEED);
    ss << speed;

    buffer = "d";
    buffer.append(" ");
    buffer.append(richting);
    buffer.append(" ");
    buffer.append(ss.str());
    buffer.append(" ");
    buffer.append(ss.str());
    buffer.append('\r');

    serial->write(buffer);
}
