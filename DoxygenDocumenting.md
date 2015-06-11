# Introduction #

Om je code goed te documenteren gebruik je in je code enkele voorgedefinieerde structuren om aan te geven welk stukje code je gaat uitleggen.


# Details #

Een voorbeeldje:

Stel ik heb een functie die ik wil becommentariëren.

Op de standaard manier kan je commentaar schrijven

```

/*
*
* Om een aantal lijnen commentaar te voorzien.
*
*/

//Om een enkele lijn commentaar te maken
//Je kan ook gewoon voor elke lijn die je commentaar wil maken //gebruiken.

Sommige mensen prefereren zelfs hele blokjes voor mooie layout

//============================//
//        COMMENTAAR          //
//============================//

Allemaal goed, wat je het liefste wil!

Ook kan je in je commentaar aangeven waarover je commentaar geeft

iets wat iedereen wel kent

//de functie blabla doet het volgende en heeft volgende parameters
//@param de parameter joske is de waarde van de teller
void blabla(int joske);

Om maar een voorbeeld te geven, @param of \param wordt omgezet door Doxygen naar een mooie HTML-pagina met daarin overzichtelijk alle commentaar bij elke code.

Naast \param of @param zijn er nog andere structuren voorgedefinieerd waaronder de meest gebruikte voor ons

@author of \author 
@return of \return
@version of \version
@if of \if
@else of \else


```

Voor een volledige lijst:

http://www.stack.nl/~dimitri/doxygen/manual/commands.html


Veel plezier ermee :)