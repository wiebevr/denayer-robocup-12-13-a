#ifndef WIFI_H
#define WIFI_H

// Standard C++:
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// VisionData
#include "../../image_processing/public data/vision_data.h"

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
    // VisionData receiveVisionData();
    void sendVisionData(const VisionData &vision_data);

private:

};
#endif // WIFI_H
