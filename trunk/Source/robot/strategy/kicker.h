/*
 * kicker.h
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */


#ifndef KICKER_H_
#define KICKER_H_
/**
	\class Kicker
	\brief Executes the kicking algorithm.
	\author Pascal Muys
*/
class Kicker : public Robot
{
public:
	Kicker();
	virtual ~Kicker();
	/** 
		This function is repeatably called and decides next step from the new coordinates.
         */
	void run();
	/** 
		This function calculates the optimal kicking position to score a goal.
		After that, it tries to reach this point based on its current position and rotation
         */
	void calcKickPos();
	/** 
		Something small to calculate distances.
		Uses sqrt(), so try something else if it has to be fast
		\param x horizontal length.
		\param y vertical length.
		\return long distance of the triangle.
         */
	int pythagoras(int x, int y);
	/** 
		Turns towards a point.
		We do this by checking for the quadrants of robotvector and pointvector.
		Then try to get them in the same quadrant.
		Once thats done, use triangles to check if we're turned towards the point.
		\param x horizontal coordinate of point.
		\param y vertical coordinate of point.
		\return gives 1 if turning completed, 0 if not.
         */
	int turnTo(int x, int y);
	/** 
		Drive towards a point.
		\param x horizontal coordinate of point.
		\param y vertical coordinate of point.
		\return gives 1 if driving completed, 0 if not.
         */
	int driveTo(int x, int y);
	/** 
		Checks in which quadrant a point is.
		
		   -2   |  -1
		---------------
		    1   |   2

		\param x horizontal coordinate of point.
		\param y vertical coordinate of point.
		\return gives a number according to description if succesfull, 0 if not.
         */
	int Kicker::checkQuadrant(int x, int y)

private:
	int kick_posx; //optimal position to start kicking from, X and Y coordinates
	int kick_posy;
	int kick_distance; //distance between ball and optimal kicking position
	int max_speed;	// maximum speed for lowlevel
	int walk_speed; // normal speed for lowlevel
};

#endif /* KICKER_H_ */
