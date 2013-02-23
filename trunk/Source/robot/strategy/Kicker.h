/*
 * Kicker.h
 *
 *  Created on: 21-feb.-2013
 *      Author: Pascal Muys
 */


#ifndef KICKER_H_
#define KICKER_H_

class Kicker {
public:
	Kicker();
	virtual ~Kicker();
	void run();
	void calcKickPos();
	int pythagoras(int x, int y);

private:
	int kick_posX; //optimal position to start kicking from
	int kick_posY;
	int kick_distance; //distance between ball and optimal kickposition
};

#endif /* KICKER_H_ */
