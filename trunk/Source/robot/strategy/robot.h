#ifndef ROBOT_H
#define ROBOT_H
/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/

#include "../low_level/low_level.h"
#include "../../image_processing/public data/vision_data.cpp"

class Robot {
	public:
		Robot();
		virtual ~Robot();

		void setGame(const VisionData & coords);
		void setll(LowLevel *ll);
        	/*
            		This function is called to initiate the robot, so it is ready to keep or kick.
			It is called once at the beginning.
            		The function is defined in each child class.
		*/
        	virtual void init();
		/*
			This function is repeatedly called to update the robot's position.
			To be implemented by the child class.
		*/
		virtual void run();

	private:
	protected:
		/*
			Pointers to the coordinate and lowlevel objects so that they can be accessed by the child robots.
		*/
		VisionData & co;
		LowLevel *ll;
		/*
            		Contains the current instruction fot the robot.
            		It will provide the functions to repeat the same instruction,
			and so advoid overkill to the steering unit of the robot.
		*/
		char lastInstruction;
};

#endif
