#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

#define MAX_SPEED 250

class LowLevel
{
    public:
        LowLevel();
        ~LowLevel();
        
    protected:
        void driveForward(int percentSpeed);
        void driveBackwards(int percentSpeed);
        void turnLeft(int percentSpeed);
        void turnRight(int percentSpeed);
        void stopMoving(void);
         
    private:
        float percentToValue(int percent, int max);
        void drive(bool richting, int speed);
}
#endif //LOW_LEVEL_H
