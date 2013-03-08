#ifndef STRATEGY_H
#define STRATEGY_H
/**
	\class Strategy
	\brief Top level Strategy class
	\author Gert Mertes
*/

#include "tests/vision_data.h"
#include "tests/low_level.h"
#include "robot.h"
#include "keeper.h"
#include "kicker.h"

class Strategy {
	public:
		Strategy();
		~Strategy();
	
	/**
		Contains the endless loop used to execute the strategy.
	*/
		void run();
	/**
		Grabs the latest coordinates from wifi.
	*/

		void setCoords(VisionData *coords);
		
	private:
	/**
		Robots
	*/
		Keeper *keeper;
		Kicker *kicker;
	/**
		The actual coordinate and lowlevel objects.
	*/
		LowLevel ll;
	/**
		Set to keep, cleared to kick
	*/
		int mode;
};

#endif
