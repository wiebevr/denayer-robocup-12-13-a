========================================================================
=                                                                      =
=  implementatie van de wifi communicatie met google protocol buffers  =
=  Author: Maarten Vandersteegen                                       =
========================================================================

Globaal:
--------

server -> externe computer
client -> robot

Op de externe computer draait een wifi server die op commando een bytestream kan broadcasten naar meerdere wifi clients die op de robots draaien.
De bytestream wordt samengesteld m.b.v. google protocol buffers en bevat dus de nuttige payload die gecommuniceert moet worden. 

De communicatie is unidirectioneel. De zender applicatie die gegevens wil doorsturen stelt de gegevens samen voor alle robots 
(met google protocol buffers). De wifi server codeert (serializing) en verpakt (headers toevoegen) de data zodat ze over het netwerk kan verzonden 
worden (IP broadcast).
De wifi client, waarvan er een op elke robot draait, ontvangt het broadcast pakket en pakt het opnieuw uit (de-serializing). 
De client geeft de uitgepakte data aan de ontvanger applicatie. 
Het pakket bevat gegevens over de posities van alle robots, de positie van de bal en de positie van de goals. Op die manier ontvangen alle robots
informatie over elkaar.  

Globaal schema:
---------------
    _________________Externe computer________________                      _______________________Robots________________________
   |                                                 |                    |                                                     |
        ___________________      _______________                                _______________      ______________________
       |                   |    |               |                              |               |    |                      |
       | zender applicatie |--->|  Wifi server  |---> *** Wifi netwerk *** --->|  Wifi client  |--->| ontvanger applicatie |
       |___________________|    |_______________|                              |_______________|    |______________________|
                                                                                _______________
                                                                               |
                                                                           --->|  Wifi client   --->
                                                                               |

De zender applicatie:
---------------------

De te verzenden parameters worden gestructureerd met google protocol buffers (zie google protoc buffers voor meer info over het principe).
Zie de game.proto file voor de inhoud van de data structuur.

De lijst is uitbreidbaar naar keuze (hou er rekening mee dat de .proto zowel bij zender als bij ontvanger aangepast moet worden). 
De naam van de overkoepelende protocol buffer message is Game (zie game.proto). 

Zie de test_server.cpp applicatie voor een gedocumenteerd voorbeeld dat een volledige Game message samenstelt en verzend.  
De zend applicatie geeft ook het commando om te zenden en bepaalt hierdoor ook effectief het broadcast tempo. 

De ontvanger applicatie:
------------------------

De ontvanger applicatie beschikt over dezelfde google protocol buffer implementatie. De game.proto file is hier uiteraard dezelfde als bij
de wifi server.

Zie de test_client.cpp applicatie voor een gedocumenteerd voorbeeld dat een volledige Game message ontvangt en gebruikt.

De ontvangen data wordt in een queue geplaatst door de wifi client. De ontvanger applicatie moet zelf het initiatief nemen om de receive 
methode op te roepen (m.a.w. hij moet de client pollen). De wifi client vertelt hem dan of er nieuwe data in de queue zit of niet. 
Als er nieuwe data is, converteert de wificlient (de-serializing) de oudste nog niet gelezen bytestream in de queue naar een Game object. 
Het game object is nu beschikbaar bij de ontvanger applicatie voor gebruik.

De wifi server:
---------------

Voor meer informatie zie de source files: wifiserver.h en wifiserver.cpp

De wifi client:
---------------

Voor meer informatie zie de source files: wificlient.h en wificlient.cpp	
		
