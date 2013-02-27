#ifndef ROBOT_H
#define ROBOT_H
/**
	\class Robot
	\brief Parent class for Kicker and Keeper
	\author Gert Mertes
*/
class Robot {
	public:
		Robot();
		~Robot(); 
	
		/*
			This function is repeatedly called to update the robot's position. 
			To be implemented by the child class.
		*/
		virtual void run();
		
		/*
			Kills the enemy robot. Weapon and method of choice to be decided.
			
			@returns true if successful. 
		*/
		bool kill();
		
	private:
		/*
			Pointers to the coordinate and lowlevel objects so that they can be accessed by the child robots.
		*/
		Coords *co;
		LowLevel *ll;
}

#endif