/*
    Robocup De Nayer 2013
    (Labo ingebedde systemen)

    Onderstaande code geschreven door Roel Gooris
*/
/*
    idee om marge toe te voegen (positie is nooit exact):
    afronden van de binnengekregen coördinaten
*/

#include "keeper.h"
#include <iostream>

using namespace std;

    ///@fn  Keeper  constructor
    Keeper::Keeper()
    {
        initOK = false;     //the robot first has to go to the initialisation position! The function 'run' will do this when 'initOK' = false
        cout << "Keeper: new keeper is born!" << endl;
    }     //ctor
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@fn  ~Keeper destructor
    Keeper::~Keeper()
    {
        cout << "Keeper: keeper got killed!" << endl;
    }    //dtor
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@fn  run Let the robot keep. !! When the robot hasn't gone to the init place yet, he has to do this first (= initialisation)!!
    void Keeper::run()
    {
        cout << "Keeper: doing his job: ";
        if (initOK)                         //when the robot has been initialised, he can go keeping
            goKeeping();                        //persuit the ball (keeping)
        else                                //when the robot is not initialised yet, he has to do this first
            initOK = goToInitPlace();           //this means he has to go to the initialisation place (his goal). Save the status of the init.
    }
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@fn  goKeeping   Simply look if the ball is under of above the robot (according the Y-axis), and follow the ball.
    void Keeper::goKeeping()
    {
        cout << "keeping" << endl;
        //the coordinates are available in the class 'co', which is already implemented by the 'strategy' class
        if (co->bally > co->robot1y)          //is the ball above the robot?
            ll->driveForward(maxSpeed);         //go up (drive forward)
        else                                //the ball is below the robot
            ll->driveBackwards(maxSpeed);       //go down (drive backwards)
    }
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    /**
    * @fn   goToPlace   Initialise the keeper: drive to the init position (in straight lines, only horizontal en vertical).
    * Every time this function is called, the progress of the initialisation has to be checked:
    * this function is called in a loop, every time with an update of the coordinates.
    * The returned boolean marks the status of the initialisation (robot stands (not yet) at the goal).
    */
    ///@return  When 'true': the robot has reached the init place (and is turned to the right direction). When'false': not there yet.
    bool Keeper::goToInitPlace()
    {
        goalx = 0.9*(co->goal1x + co->goal2x)/2;    //calculate the x-place to go to (just before the goal)
        goaly = (co->goal1y + co->goal2y)/2;        //calculate the y-place to go to (between the two poles)
        cout << "moving to the goal(" << goalx << ";" << goaly << ")";
        if (co->robot1x == goalx and co->robot1y == goaly)            //robot reached the init place?
        {
            if (co->robot1roty == 1)                                     //... and turned towards the top?
            {
                ll->driveForward(0);                                        //stand still; stop moving
                cout << endl << "Keeper: arrived at the goal, can start with keeping" << endl;
                return true;                                                //init complete
            }
            else
            {                                                           //... and not yet turned towards the top
                cout << ", just need to turn" << endl;
                if (co->robot1rotx < 0)                                      //when the robot looks to the right
                    ll->turnLeft(maxSpeed);                                     //turn left
                else                                                        //when the robot looks to the left
                    ll->turnRight(maxSpeed);                                    //turn right
            }
        }
        else                                                        //robot has'n reached the init place yet
        {
            if (co->robot1y == goaly)                                   //But does he stands on the same vertical position? (y-axis)
            {
                if (co->robot1rotx == 1)                                     //... and is he turned towards the goal?
                {
                    cout << ", straight forward to the goal" << endl;
                    ll->driveForward(maxSpeed);                                 //then go forward
                }
                else
                {                                                           //... and not yet turned towards the goal
                    cout << ", turning towards the goal" << endl;
                    if (co->robot1roty > 0)                                      //when the robot looks to the top
                        ll->turnLeft(maxSpeed);                                     //turn left
                    else                                                        //when the robot looks to the bottom
                        ll->turnRight(maxSpeed);                                    //turn right
                }
            }
            else                                                        //When the robot is completely out of position
            {
                if (co->robot1roty == 1)                                     //... and the robot is turned towards the top
		{
		    cout << "driving to the middle of the field" << endl;
                    ll->driveForward(maxSpeed);                                 //then go forward
		}
                else                                                        //... and the robot is neither turned towards the top
                {
		    cout << "turning towards the middle of the field" << endl;
                    if (co->robot1rotx < 0)                                      //when the robot looks to the right
                        ll->turnLeft(maxSpeed);                                     //turn left
                    else                                                        //when the robot looks to the left
                        ll->turnRight(maxSpeed);                                    //turn right
                }
            }
        }
        return false;                                               //when the init is not terminated yet, then the initialisation is not completed yet
    }
