# Coding Guidelines #
## Het gebruik van verschillende files ##
  * Er worden geen hoofdletters gebruikt in filenames, er wordt een `_` geplaatst tussen de verschillende woorden in de klasse naam.
> > De klasse `WifiCommunication` wordt bijvoorbeeld in de file wifi`_`communication.h en wifi`_`communication.cpp files geplaatst.
  * De klasse definitie in de header file wordt geplaatst tussen #ifndef preprocessor commando's, als volgt:
```
#ifndef WIFI_COMMUNICATION_H
#define WIFI_COMMUNICATION_H
class WifiCommunication
{
    ...
};
#endif // WIFI_COMMUNICATION_H
```
### Robot ###
  * Elke module krijgt een eigen map, de volgende structuur wordt gehanteerd.
    * Source
      * General
      * LowLevel
      * Strategy
      * Wifi

## Stijl ##
  * We maken gebruik van [Allman style](http://en.wikipedia.org/wiki/Indent_style#Allman_style), dit betekent dat elke accolade op een nieuwe regel komt.
> > Bijvoorbeeld:
```
while (x == y)
{
    something();
    somethingelse();
}
finalthing();
```
> > en niet:
```
while (x == y) {
    something();
    somethingElse();
}
finalThing();
```
  * Elke methode wordt gedeclareerd in een header (`.h`) file en geïmplementeerd in een .cpp file.
  * Namen van variabelen en objecten worden gescheiden door een `_`, voor methodes wordt lower camel case gebruikt en voor klassen upper camel case  bijvoorbeeld:
```
class VerySpecialClass
{
public:
    void myVeryOwnFunction(int argument_variable);

private:
    int my_integer;
}
```
  * Doxygen commentaar wordt in de header files geplaatst:
```
/**
    \class VerySpecialClass
    \brief A very special class */
class VerySpecialClass
{
public:
    /** This function does really special stuff.
        \param argument_variable this variable if used in the function. */
    void myVeryOwnFunction(int argument_variable);

private:
    /** Very special variable */
    int my_integer;
};
```
  * Een lijn heeft een maximale lengte van 80 tekens.
  * Expressies worden gescheiden met een spatie bv.: `x = 2 * y;` en niet `x=2*y`;
  * `#include ".."` wordt gebruikt voor eigen files en `#include <..>` voor andere.
  * Code wordt geïndenteerd met 4 spaties.
  * Commentaar en namen worden in het engels geschreven.
  * Plaatst boven elke functie een scheidingslijn als volgt:
```
// ---------------------------------------------------------------------------
void myVeryOwnFunction(int argument_variable)
{
    // Do something
}

// ---------------------------------------------------------------------------
void anotherVeryOwnFunction(int argument_variable)
{
    // Do something else
}
```