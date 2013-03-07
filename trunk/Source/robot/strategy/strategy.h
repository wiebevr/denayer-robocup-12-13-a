#ifndef STRATEGY_H
#define STRATEGY_H
/**
	\class Strategy
	\brief Top level Strategy class
	\author Gert Mertes
*/

#include "../low_level/low_level.h"
#include "../../image_processing/public data/vision_data.h"
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
		void setCoords(const VisionData & coords);
		
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
};

#endif
