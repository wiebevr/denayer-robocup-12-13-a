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
         */
	void calcKickPos();
	/** 
		Something small to calculate distances.
		Uses sqrt(), so try something els
		\param x horizontal length.
		\param y vertical length.
		\return long distance of the triangle
         */
	int pythagoras(int x, int y);
	/** 
		Turns towards a point.
		\param x horizontal coordinate.
		\param y vertical coordinate.
		\return gives 1 if turning completed, 0 if not
         */
	int turnTo(int x, int y);
	/** 
		Drive towards a point.
		\param x horizontal coordinate.
		\param y vertical coordinate.
		\return gives 1 if driving completed, 0 if not
         */
	int driveTo(int x, int y);

private:
	int kick_posx; //optimal position to start kicking from, X and Y coordinates
	int kick_posy;
	int kick_distance; //distance between ball and optimal kicking position
	int max_speed;	// maximum speed for lowlevel
	int walk_speed; // normal speed for lowlevel
	int rob_posx; // robot position x and y, for easier access
	int rob_posy;
	int ball_posx; // ball position x and y, for easier access
	int ball_posy;
	int rob_rot; // robot rotation in degrees
	int rob_roty // y value of robot rotation
};

#endif /* KICKER_H_ */