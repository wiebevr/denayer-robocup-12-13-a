#include "robot.h"

using namespace std;

    ///@fn  Robot  constructor
    Robot::Robot()
    {
        ll = new LowLevel();
        co = new Coords();
        lastInstruction = '';
    }     //ctor

    ///@fn  ~Robot destructor
    Robot::~Robot()
    {
        //verwijder ll en co
    }    //dtor

    virtual void run() = 0;
    virtual void init();
