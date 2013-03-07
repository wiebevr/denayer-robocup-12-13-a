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

                             O
                             |
                             |              O: mogelijke startplaats
                    X--------+              X: init. plaats voor het doel
                             |              -: af te leggen weg
                             |
                             O

        - goKeeping(): hol achter de bal aan
            Er wordt nagegaan of er naar boven of naar onder moet worden gereden om de bal te volgen. Er wordt alleen vooruit en achteruit gereden.
            Er wordt dus geen rekening gehouden met eventuele draai-afwijkingen van de robot.

                    GoToPlace()                                                 goKeeping()
    (0,0)---------------------------------------------      (0,0)---------------------------------------------
        |                                 |                     |                                 |
        |                                 |                     |                                 |
        |                                 |                     | ^                               |
        |            0                    |                     | |                               |
        |----        |                    |                     |----                             |
        |    |       |                  / | \                   | |  |                          / | \
        | X--|-------+                 |  o  |                  | X  |                         |  o  |
        |    |       |                  \ | /                   | |  |                          \ | /
        |----        |                    |                     |----                             |
        |            o                    |                     | |                               |
        |                                 |                     | V                               |
        |                                 |                     |                                 |
        |                                 |                     |                                 |
        ----------------------------------------------          ----------------------------------------------
*/

/**
* @fn       Keeper          De constructor van de keeper.
* @fn       ~Keeper         De deconstructor van de keeper.
* @fn       init            Initialiseer de robot als keeper.
* @fn       run             Laat de robot keeperen (roept de functie goKeeping of goToInitPlace op).
* @param    initOK          Om aan te duiden of de robot nog naar zijn plaats moet rijden (voor zijn doel).
* @fn       goKeeping       Voor de instructies uit om te keeperen.
* @fn       goToInitPlace   Deze functie zal de keeper voor zijn doel plaatsen, zodat hij kan keeperen. Returnt een boolean die de voltooing aangeeft.
*/
#ifndef KEEPER_H
#define KEEPER_H
#include "robot.h"
class Keeper : public Robot            //DE KLASSE KEEPER IS EEN UITBEREIDING VAN DE KLASSE ROBOT
{
    public:
        Keeper();               //CONSTRUCTOR
        ~Keeper();              //DESTRUCTOR
        void init();            //ZET ALLES KLAAR OM TE KUNNEN KEEPEN
        void run();             //KEEPER ACTIVEREN VOOR DE HUIDIGE COORDINATEN (NAAR PLAATS GAAN + KEEPEN)
    protected:
    private:
        int  maxSpeed;		//DE WAARDE VOOR DE MAXIMALE SNELHEID WAARMEE DE ROBOT KAN RIJDEN
        bool initOK;            //OM AAN TE DUIDEN OF DE ROBOT NOG NAAR ZIJN PLAATS (HET DOEL) MOET RIJDEN
        void goKeeping();       //ACHTERVOLG DE BAL (PRIMITIEVE KEEPERFUNCTIE)
        bool goToInitPlace();   //INITIALISEER DE ROBOT DOOR NAAR ZIJN PLAATS (HET DOEL) TE RIJDEN
};

#endif // KEEPER_H
