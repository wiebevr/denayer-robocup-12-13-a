/**
 *  @brief      Keeper function of the robot.
 *  @author     Roel Gooris
 *  @version    1.1
 *  @date       2013
 *  @pre        Initiate the robot
 */

/**
* @class    Keeper  Keeper.h
* Uitbereiding van de klasse 'Robot'.
* Deze klasse laat de robot keeperen.

    Keeperfunctie van de robot
    Versie 1:
    - "Domme functies, momentfuncties": functies die alleen rekening houden met de huidige situatie.
        Met de huidige posities wordt een instructie gegenereerd en de functie wordt beëindigd. (kijken-doen-sluiten)
        De functie zal dus niet actief blijven totdat het doel van die functie berijkt is.
        => de functie moet na aanroeping telkens nagaan hoe ver de robot al gevorderd is in dit doel!
    - De oorsprong van de coordinaten ligt in de linker bovenhoek (zie tekening onderaan de comentaar)
    - De robot moet het linker doel keepen

    - De functies:
**/
/*

                    GoToPlace()                                                 goKeeping()			            <br>
    	----------------------------------------------      	----------------------------------------------	<br>
        |                                 |                     |                                 |		        <br>
        |                                 |                     |                                 |		        <br>
        |                                 |                     | ^                               |		        <br>
        |            0                    |                     | |                               |		        <br>
        |----        |                    |                     |----                             |		        <br>
        |    |       |                  / | \                   | |  |                          / | \		    <br>
        | X--|-------+                 |  o  |                  | X  |                         |  o  |		    <br>
        |    |       |                  \ | /                   | |  |                          \ | /		    <br>
        |----        |                    |                     |----                             |		        <br>
        |            o                    |                     | |                               |		        <br>
        |                                 |                     | V                               |		        <br>
        |                                 |                     |                                 |		        <br>
        |                                 |                     |                                 |		        <br>
        ----------------------------------------------(0,0)     ------------------------------------------(0,0)	<br>
*/


#ifndef KEEPER_H
#define KEEPER_H
#include "robot.h"
class Keeper : public Robot     //DE KLASSE KEEPER IS EEN UITBEREIDING VAN DE KLASSE ROBOT
{
    public:
        /// @fn       Keeper          Constructor of the keeper = initialisation.
        Keeper();               //CONSTRUCTOR

        /// @fn       ~Keeper         Deconstructor of the keeper.
        ~Keeper();              //DESTRUCTOR

        /** @fn       run             Keeping function of the robot.
        **  At first, the function 'goToInitPlace()' will be called by this function, because the robot has to be initialised as keeper.
        **  (= go to the goal and turn towards the upper side)
        **  When the initialisation of the robot is not completed, the returned boolean of the init function will be false.
        **  So next time this function will be called again to complete the initialisation.
        **  When the robot is successfully initialisated, the returned boolean of the init function will be true.
        **  So next time, the robot can finally do his job (keeping).
        **  Therefore, the function 'goKeeping' will be called.

                             O											                                        <br>
                             |											                                        <br>
                             |              O: possible start place 						                    <br>
                    X--------+              X: init. place at the goal  					                    <br>
                             |              -: path to init place  						                        <br>
                             |											                                        <br>
                             O											                                        <br>
        **/
        void run();             //KEEPER ACTIVEREN VOOR DE HUIDIGE COORDINATEN (NAAR PLAATS GAAN + KEEPEN)
    protected:
    private:
         /** @fn       goKeeping       The actual keeping instruction.
         ** Compare the Y-coördinates of the ball and the robot. Descide weither the robot has to move upwards or downwards to follow the ball.
         ** This function is lik the Pong game.
         ** The robot will only drive forward and backwards, no turning. When the robot is turned (e.g.due to friction), this will not be corrected.
         **/
        void goKeeping();       //ACHTERVOLG DE BAL (PRIMITIEVE KEEPERFUNCTIE)

        /** @fn       goToInitPlace   Move the keeper towards the init place, his goal. When the keeper is arrived, the function returns 'true'.
        **  The init place is right before the goal. The robot must also face the top.
        **  The robot will only move in straight lines and turn 90°. This to avoid the calculation of the turning angles.
        **/
        bool goToInitPlace();   //INITIALISEER DE ROBOT DOOR NAAR ZIJN PLAATS (HET DOEL) TE RIJDEN

        /// @var      initOK          Boolean, indicates if the keeper has been initialised yet (= moved to his goal to start keeping)
        bool initOK;            //OM AAN TE DUIDEN OF DE ROBOT NOG NAAR ZIJN PLAATS (HET DOEL) MOET RIJDEN

        /// @var      goalx           X-coördinate of the goal. Used to initialise the keeper (drive to the goal)
        float goalx;              //INITPLAATS (X-CO)

        /// @var      goaly           Y-coördinate of the goal. Used to initialise the keeper (drive to the goal)
        float goaly;              //INITPLAATS (Y_CO)
};

#endif // KEEPER_H
