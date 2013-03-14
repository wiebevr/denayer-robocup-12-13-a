/** Low level class
 * Functions for low level communication 
 * @author Jasper
 * @author Ken
 */

/** 
 * Imposter class for testing strategy
*/


#include <stdlib.h>
#include "low_level.h"
#include <string>
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------
LowLevel::LowLevel()
{
}

// ---------------------------------------------------------------------------
LowLevel::~LowLevel()
{
}

// ---------------------------------------------------------------------------
void LowLevel::driveForward(int speed)
{
    cout << "forward " << speed << endl;
}

// ---------------------------------------------------------------------------
void LowLevel::driveBackwards(int speed)
{   
    cout << "backwards "  << speed << endl;
}

// ---------------------------------------------------------------------------
void LowLevel::turnLeft(int speed)
{   
    cout << "left "  << speed << endl;
}

// ---------------------------------------------------------------------------
void LowLevel::turnRight(int speed)
{ 
    cout << "right " << speed << endl;
}

// ---------------------------------------------------------------------------
void LowLevel::stopMoving(void)
{
    cout << "stop " << endl;
}

// ---------------------------------------------------------------------------
void LowLevel::ledTest(void)
{
   cout << "led" << endl;
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
}

