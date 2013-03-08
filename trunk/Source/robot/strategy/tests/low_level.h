/** Header low level communication
 * @author Jasper
 * @autor Ken
*/

/** 
 * Imposter class for testing strategy
*/


#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

#define MAX_SPEED 200

class LowLevel
{
    public:
		/** Constructor */
        LowLevel();
		/** Destructor */
        ~LowLevel();
        
        /** Function to drive the robot forward
         * @param percentSpeed Integer of the speed in percent (0 - 100)
         */
        void driveForward(int percentSpeed);
        /** Function to drive the robot backwards 
         * @param percentSpeed Integer of the speed in percent (0 - 100)
         */
        void driveBackwards(int percentSpeed);
        /** Function to rotate the robot to the left 
         * @param percentSpeed Integer of the speed in percent (0 - 100)
         */
        void turnLeft(int percentSpeed);
        /** Function to rotate the robot to the right
         * @param percentSpeed Integer of the speed in percent (0 - 100)
         */
        void turnRight(int percentSpeed);
        /** Function to stop all movement of the robot
         */
        void stopMoving(void);         
        /** Function to test the leds on the robot
         */
        void ledTest(void);

    private:
        /** Function to calculate the value of percent
         * @param percent Integer of the percent value (0 - 100)
         * @param max Integer that represent the maximum 
		 * @return float Converted percentage in function of the max value 
         */
        float percentToValue(int percent, int max);
        /** Function to send command to the robot
         * @param speed Interger with the actual speed
         * @param direction Character of the direction (F, B, L, R)
         */
        void drive(int speed, char direction);
		/** Serial object that preformes the serial communication with the robot\
		 */
        //Serial * serial;
};
#endif //LOW_LEVEL_H
