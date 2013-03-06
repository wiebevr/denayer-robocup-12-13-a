#ifndef STRATEGY_H
#define STRATEGY_H
/**
	\class Strategy
	\brief Top level Strategy class
	\author Gert Mertes
*/

#include "low_level/low_level.h"
#include "wifi/game.pb.h"
#include "robot.h"
#include "Keeper.h"
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
		void setGame(const Game & game);
		
	private:
	/**
		Robots
	*/
		Keeper *keeper;
		Kicker *kicker;
	/**
		The actual coordinate and lowlevel objects.
	*/
		Game & co;
		LowLevel ll;
};

#endif
