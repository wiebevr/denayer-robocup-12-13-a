# Project Overview #

---


## Table of Contents ##
||
|:|

## Introduction ##

For our course in Smart Embedded Systems at Lessius Mechelen Campus De Nayer, we have to create a Robocup SSL-project. The goal of this project is to create an autonomous robot, that can play a simplified version of soccer. Our team consists of 12 members, each given a single assignment.

## Architecture ##

The total architecture of this project is divided into 4 subsystems. First, the Image Processing-unit will process the images received by the camera. Then, the Wifi-unit will send the information from the local computer to the robot over Wifi. Afterwards, the Strategy-unit provides a strategy on what the robot should do. And finally, the Low Level Communication-unit will control the wheels of the robot. Every unit is explained more detailed underneath.

## Modules ##
### Image Processing (IP-unit) ###

A camera positioned above the field provides images to the central computer at a framerate of 4fps. These images are processed by the IP-unit. You can find an example of an image underneath.

<img src='http://denayer-robocup-12-13-a.googlecode.com/svn/wiki/images/afbeelding.jpg' alt='Pulpit rock' width='500' height='360'>

Out of these images, the coördinates of each object on the field will be calculated. With the field being green, the ball being orange, and a pattern present on the robot, the most logical technique to use, is Color Segmentation.<br>
<br>
Now that the coördinates are known, they have to be send to the robot. The coördinates are delivered to the WIFI-unit.<br>
<br>
The information received from the IP-unit has to be send to the robot. The Wifi unit collects the data and assembles it into 1 object. Via protocol buffers the data is transmitted over the WIFI-network. The protocol used for this transmission is UDP. There will be know acknowledgement from the robot that he's received the package. If he were to miss one package, the next one will arrive shortly without too much data-loss.<br>
<br>
<h3>Strategy</h3>

The robot needs to interpret the coordinates received over WIFI. The strategy determines whether the robot has to kick the ball, or keep the ball out of the goal. For example: in which direction does the robot need to turn, move or kick. These instructions are given to the low level communication-unit.<br>
<br>
<h3>Low-level Communication</h3>

The Low-level Communication-unit receives instruction from the strategy-unit. Based on these instructions and their parameters the robot has to drive forward or turn around until a stop-instruction is received. For this to happen, the engines of the robot have to be controlled.<br>
<br>
<h2>Technologies and Frameworks</h2>


<h3>Het project builden</h3>
Het bouwen van het project gebeurd bij voorkeur "out of source", dit betekent dat alle gegenereerde files (wat er bij cmake redelijk veel zijn) buiten de broncode-map worden gebuild. Dit zorgt ervoor dat de broncode boom mooi blijft en er geen clutter op de svn repo's komt.<br>
<br>
In de map Source is op svn als een map <code>build</code> aangemaakt. Svn is in deze map zo geconfigureerd dat alle files hierin genegeerd worden. Om te builden ga je eerst in een terminal naar de build map:<br>
<pre><code>cd Source<br>
</code></pre>
In de Source map type je:<br>
<pre><code>make robot <br>
make vision<br>
</code></pre>

Als het compileren zonder error's is verlopen worden alle gegenereerde executables in de map Source\build\robot of Source\build\vision gezet.<br>
<br>
<b>Zorg er steeds voor dat code die gecommit wordt naar de repo's<br>
compileerd zodat andere groepen deze code zonder problemen kunnen binnen halen en compileren.</b>

<h2>Documentation</h2>

The project is open source, and thus the code must be documented so that other people can work separatly on the code. We used doxygen, a programme that generates an HTML-file from the documented code. This HTML-file can be found at the following website:<br>
<br>
<a href='http://sakti.be/school/ROBODOC/html/annotated.html'>http://sakti.be/school/ROBODOC/html/annotated.html</a>