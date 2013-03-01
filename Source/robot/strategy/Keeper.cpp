/*
    Robocup De Nayer 2013
    (Labo ingebedde systemen)

    Onderstaande code geschreven door Roel Gooris
*/


/*
    idee om marge toe te voegen (positie is nooit exact):
    afronden van de binnengekregen coördinaten
*/


#include "Keeper.h"

using namespace std;

    ///@fn  Keeper  constructor
    Keeper::Keeper() {}     //ctor

    ///@fn  ~Keeper destructor
    Keeper::~Keeper() {}    //dtor

    ///@fn  init    maak de robot klaar om te keeperen
    void Keeper::init() {initOK = false;}   //de robot moet eerst naar zijn plaats rijden! De run functie doet dit als 'initOK' = false

    ///@fn  run Laat de robot keeperen. !! Indien de robot nog niet op zijn initplaats staat, laat hem dan naar zijn initplaats gaan.
    void Keeper::run()
    {
        if (initOK)                         //als de robot al aan de goal staat kan er gekeeperd wordern
            this.goKeeping();                   //achtervolg de bal (keeperen)
        else                                //als de robot nog ergens anders staat, moet er nog eerst naar de goal worden gegaan
            initOK = this.goToPlace();          //ga naar de goal en laat weten of we er zijn geraakt
    }

    ///@fn  goKeeping   Kijk of de bal op dit moment boven of onder de robot is (volgens de Y-as), en volg de bal.
    void Keeper::goKeeping()
    {
        //de coordinaten zitten in de hogere klasse, dus niet meer ophalen
        if (Robot.get_my_Yco() > Robot.get_ball_Yco())     //is de bal boven de robot?
        {
            Lowlevel.forward();                                 //ga naar boven (rij vooruit)
        }
        else                                               //de bal is onder de robot
        {
            Lowlevel.backward();                                //ga naar onder (rij achteruit)
        }
    }

    /**
    * @fn   goToPlace   Initialiseer de keeper: rij naar de startplaats (in rechte lijnen, alleen horizontaal en verticaal).
    * Er moet telkens nagegaan worden hoe ver de robot gevorderd is op dat moment: wordt in een lus aangeroepen met telkens een update van de coordinaten.
    * De teruggegeven boolean duid aan of de initialisatie is voltooid (robot staat voor de goal).
    */
    ///@return  Indien = 'true': de robot staat op de goede plaats (en in de goede richting). Indien = 'false': de robot staat nog niet goed.
    bool Keeper::goToPlace()
    {
        //staat de robot op de beginplaats?
        if (Robot.get_my_place().getX() == Robot.get_goal_place().getX() and Robot.get_my_place().getY() == Robot.get_goal_place().getY())
        {
            //staat de robot in de goede richting?
            if (Robot.get_my_dir() == 90)
                return true;                                                //de robot staat helemaal goed => stoppen
            else
            {                                                      //nog draaien zodat we naar boven kijken
                if (Robot.get_my_dir() < 90 and Robot.get_my_dir > -90)     //indien de robot naar rechts kijkt
                    Lowlevel.turnLeft();                                        //links draaien
                else                                                        //indien de robot naar links kijkt
                    Lowlevel.turnRight();                                       //rechts draaien
            }
        }
        else
        {                                                      //nog niet op de goede plaats
            //staat de robot op dezelfde hoogte (Y-co) als zijn doel?
            if (Robot.get_my_place().getY() == Robot.get_goal_place().getY())
            {
                //staat de robot in de goede richting?
                if (Robot.get_my_dir() == 180)
                    Lowlevel.forward();                                         //rechtdoor rijden
                else
                {                                                      //nog draaien zodat we naar links kijken
                    if (Robot.get_my_dir() < 180 and Robot.get_my_dir > 0)     //indien de robot naar boven kijkt
                        Lowlevel.turnLeft();                                        //links draaien
                    else                                                        //indien de robot naar onder kijkt
                        Lowlevel.turnRight();                                       //rechts draaien
                }
            }
            //de robot staat volledig uit positie
            else
            {
                //staat de robot in de goede richting?
                if (Robot.get_my_dir() == 90)
                    Lowlevel.forward();                                          //rechtdoor rijden
                else
                {                                                      //nog draaien zodat we naar boven kijken
                    if (Robot.get_my_dir() < 90 and Robot.get_my_dir > -90)     //indien de robot naar rechts kijkt
                        Lowlevel.turnLeft();                                        //links draaien
                    else                                                        //indien de robot naar links kijkt
                        Lowlevel.turnRight();                                       //rechts draaien
                }
            }
        }
        return false;                                               //indien we tot hier raken dan staat de robot nog niet op de goede plaats
    }
