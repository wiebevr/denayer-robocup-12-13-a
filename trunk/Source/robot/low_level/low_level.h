/* Header low level communication
 * @author Jasper
 * @autor Ken
*/

#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

#define MAX_SPEED 200

class LowLevel
{
    public:
        LowLevel();
        ~LowLevel();
        
    protected:
        /* Function to drive the robot forward
         * @param speed integer of speed in percent
         */
        void driveForward(int percentSpeed);
        /* Function to drive the robot backwards 
         * @param speed integer of speed in percent
         */
        void driveBackwards(int percentSpeed);
        /* Function to rotate the robot to the left 
         * @param speed integer of speed in percent
         */
        void turnLeft(int percentSpeed);
        /* Function to rotate the robot to the right
         * @param speed integer of speed in percent
         */
        void turnRight(int percentSpeed);
        /* Function to stop al movement of the robot
         * @param speed integer of speed in percent
         */
        void stopMoving(void);         
        /* Function to test the leds on the robot
         */
        void ledTest(void);

    private:
        /* Function to calculate the value of percent
         * @param integer that represent the percent
         * @param integer that represent the maximum
         */
        float percentToValue(int percent, int max);
        /* Function to send command to the robot
         * @param interger with the actuel speed
         * @param character of the direction
         */
        void drive(int speed, char richting);

        Serial * serial;
}
#endif //LOW_LEVEL_H
