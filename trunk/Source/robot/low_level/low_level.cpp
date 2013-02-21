/* Low level class
 * @author Jasper
 * @author Ken
 */

#include "low_level.h"


// ---------------------------------------------------------------------------
LowLevel::LowLevel()
{}

// ---------------------------------------------------------------------------
void LowLevel::driveForward(int speed)
{
    speed = percentToValue(speed, MAX_SPEED);
}

// ---------------------------------------------------------------------------
void LowLevel::driveBackwards(int speed)
{   
    speed = percentToValue(speed, MAX_SPEED);
}

// ---------------------------------------------------------------------------
void LowLevel::turnLeft(int speed)
{   
    speed = percentToValue(speed, MAX_SPEED);
}

// ---------------------------------------------------------------------------
void LowLevel::turnRight(int speed)
{ 
    speed = percentToValue(speed, MAX_SPEED);
}

// ---------------------------------------------------------------------------
void LowLevel::stopMoving(void)
{
    
}


// Private functions
// ---------------------------------------------------------------------------
float percentToValue(int percent, int max)
{
    float value = max / 100;
    value *= percent;
    return value;   
}
