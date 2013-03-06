#ifndef WIFI_H
#define WIFI_H

// Standard C++:
#include <string>
#include <iostream>
#include <vector>

// Protocol buffers:
#include "game.pb.h"

/**
    \class Wifi
    \brief Wifi class
*/
class Wifi
{
public:
    /** Constructor */
    Wifi();

    /** Destructor */
    virtual ~Wifi();
    
    /** Returns the game protocol buffer instance. Blocks until a new
     * packet is received. */
    const Game &getGame() const;

private:
    Game game;

};
#endif // WIFI_H
