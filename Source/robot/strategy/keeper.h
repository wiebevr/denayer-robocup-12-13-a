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
        - constructor, destructor
        - init(): bereid de robot voor om te keeperen
        - run(): keeperen! Een van de volgende twee functies wordt aangesproken (hangt af van boolean 'initOK'):
        - GoToPlace(): initialiseer de keeper
            Kijkt na of de robot op de beginplaats staat (voor zijn goal). Indien dit niet het geval is zal de robot naar deze plaats rijden.
            Het rijden naar de startplaats gebeurt in rechte lijken (horizontaal en verticaal): anders moet nog een draaihoek worden berekend.
            Er wordt een boolean teruggestuurd die aangeeft of de initialisatie voltooid is.

                             O											                                        <br>
                             |											                                        <br>
                             |              O: mogelijke startplaats						                    <br>
                    X--------+              X: init. plaats voor het doel					                    <br>
                             |              -: af te leggen weg							                        <br>
                             |											                                        <br>
                             O											                                        <br>

        - goKeeping(): hol achter de bal aan
            Er wordt nagegaan of er naar boven of naar onder moet worden gereden om de bal te volgen. Er wordt alleen vooruit en achteruit gereden.
            Er wordt dus geen rekening gehouden met eventuele draai-afwijkingen van de robot.

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

/**
* @fn       Keeper          Constructor of the keeper = initialisation.
* @fn       ~Keeper         Deconstructor of the keeper.
* @fn       run             Keeping function of the robot (calls either the function 'goKeeping' or 'goToInitPlace').
* @fn       goKeeping       The actual keeping instruction.
* @fn       goToInitPlace   Move the keeper towards the init place, his goal. When the keeper is arrived, the function returns 'true'.
* @var      maxSpeed        Integer, contains the value for the maximum speed to move the robot
* @var      initOK          Boolean, indicates if the keeper has been initialised yet (= moved to his goal to start keeping)
*/
#ifndef KEEPER_H
#define KEEPER_H
#include "robot.h"
class Keeper : public Robot     //DE KLASSE KEEPER IS EEN UITBEREIDING VAN DE KLASSE ROBOT
{
    public:
        Keeper();               //CONSTRUCTOR
        ~Keeper();              //DESTRUCTOR
        void run();             //KEEPER ACTIVEREN VOOR DE HUIDIGE COORDINATEN (NAAR PLAATS GAAN + KEEPEN)
    protected:
    private:
        bool initOK;            //OM AAN TE DUIDEN OF DE ROBOT NOG NAAR ZIJN PLAATS (HET DOEL) MOET RIJDEN
        float goalx;              //INITPLAATS (X-CO)
        float goaly;              //INITPLAATS (Y_CO)
        void goKeeping();       //ACHTERVOLG DE BAL (PRIMITIEVE KEEPERFUNCTIE)
        bool goToInitPlace();   //INITIALISEER DE ROBOT DOOR NAAR ZIJN PLAATS (HET DOEL) TE RIJDEN
};

#endif // KEEPER_H
