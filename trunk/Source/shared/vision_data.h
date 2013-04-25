/**
 * @file vision_data.h
 * @class VisionData
 * @author Den Dooven Raphael
 *
 *  @brief The VisionData class Deze klasse zal aan de wifi door geven waar eigen Robot, (optioneel) andere robot, ball en goal zich bevind.
 * Elke robot heeft zijn eigen x, y coordinaten samen met 2 richtings coordinaten. De goal wordt opgedeelt in 2 x en y coordinaten,
 * een vor elke paal. De bal heeft enkel een x en y coordinaat.
 */

#ifndef VISION_DATA_H
#define VISION_DATA_H

#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

class VisionData 
{
public:
    /**
     * @brief VisionField Deze constructor zal de andere constructor oproepen met een
     * vaste grote van 300 op 300.
     * @param img camera beeld
     */
    float robot1x;
    float robot1y;
    float robot1rotx;
    float robot1roty;

    float robot2x;
    float robot2y;
    float robot2rotx;
    float robot2roty;

    float ballx;
    float bally;

    float goal1x;
    float goal1y;
    float goal2x;
    float goal2y;

    /**
     * @brief VisionData Deze constructor zal alle waardes op nul inisalizeren
     */
    VisionData();

    /**
     * @brief angle2cart De methode angle2cart zal een hoeg omzetten naar 
     * een cartisaanse voorstelling en tegelijk in de juiste variable zetten
     * @param angle hoek
     * @param robot de nummer van de robot
     */
    void angle2cart(float angle, int robot);

    string toString() const;
    void fromString (string& str);
    bool operator==(const VisionData &rhs);
    bool operator!=(const VisionData &rhs);
};

#endif // VISION_DATA_H