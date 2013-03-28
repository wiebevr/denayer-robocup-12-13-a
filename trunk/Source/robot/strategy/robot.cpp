/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "robot.h"
#include <iostream>

// ---------------------------------------------------------------------------
Robot::Robot()
{
        lastInstruction = 'a';
	co = 0;
}

// ---------------------------------------------------------------------------
Robot::~Robot()
{
	//unused
}

void Robot::setCoords(VisionData *coords)
{
	std::cout << "robot scoords" << std::endl;	
	this->co = coords;
}

void Robot::setll(LowLevel *lowl)
{
	this->ll = lowl;

}

void Robot::run()
{

}
// -----------------------------------------------------------------------------
private bool Robot::turnTo(float x float y)         //met x en y de coordinaten van de bal
{
    float Rx = co->robot1rotx;          //kijkrichting van de robot volgens de x-as
    float Ry = co->robot1roty;          //kijkrichting van de robot volgens de y-as
    float Bx = x - co->robot1x;         //richting naar de bal volgens de x-as
    float By = y - co->robot1y;         //richting naar de bal volgens de y-as

    if (Rx == 0)                        //indien de kijkrichting van de robot 0 is, dan kan het algoritme niet toegepast worden
    {
        if (y < co->robot1y)                //kijk nu gewoon naar het verschil tussen de y-vectoren
        {
            turnDown();                         //de robot kijkt teveel naar boven
        }
        else
        {
            turnUp();                           //de robot kijkt teveel naar beneden
        }
    }
    else                                //pas het algoritme toe
    {
        float factor = Bx / Rx;             //normalisatiefactor om de kijkrichting (x-vector) gelijk te stellen aan de richting naar de bal (x-vector)
        float RyNorm = Ry * factor;         //de genormaliseerde kijkrichting (y-vector) van de robot

        //nu hebben we dus Rx gelijk gesteld aan Bx, waardoor Ry omgevormd werd naar RyNorm.
        //Nu moeten we controleren of RyNorm = By, want dan kijkt de robot naar de bal
        if (RyNorm == By)
        {
            if (factor > 0)                     //OPGEPAST: de robot kan ook 180° gedraaid zijn en van de bal wegkijken in dezelfde lijn
            {
                return true;                        //indien dit niet het geval is: we zijn goed gedraaid => einde!!
            }
            else
            {
                turnDown();                         //indien dit wel het geval is: kies een kant om naar te draaien
            }
        }
        else                                //de robot kijkt niet naar de bal => bijdraaien
        {
            if (By < RyNorm)                    //de genormaliseerde y-vector is te groot
            {
                turnDown();                         //draai naar onder (maak hem kleiner)
            }
            else                                //de genormaliseerde y-vector is te klein
            {
                turnUp();                           //draai naar boven (maak hem groter)
            }
        }
    }
    return false;                       //we zijn nog niet goed gedraait
}
// ----------------------------------------------------------------------------------------------
private void Robot::turnUp()
{
    //draai de robot naar de bovenkant
    if (co->robot1x > 0)                //kijkt de robot naar links
    {
        ll.turnRight(maxSpeed);             //draai dan naar rechts
    }
    else
    {
        ll.turnLeft(maxSpeed);              //draai anders naar links
    }
}
// --------------------------------------------------------------------------------------------
private void Robot::turnDown()
{
    //draai de robot naar de onderkant
    if (co->robot1x > 0)                //kijkt de robot naar links
    {
        ll.turnLeft(maxSpeed);              //draai dan naar links
    }
    else
    {
        ll.turnRight(maxSpeed);             //draai anders naar rechts
    }
}
