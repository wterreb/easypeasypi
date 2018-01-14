Before you try to use the examples, make sure you have "git" and "WiringPi" installed on your raspberry pi.

To install GIT:
===============
sudo apt-get install git-core

If you get any errors here, make sure your Pi is up to date with the latest versions of Raspbian:

sudo apt-get update
sudo apt-get upgrade

To install WiringPi:
====================
git clone git://git.drogon.net/wiringPi


To install EasyPeasyPi on RPi:
===============================

To get the source code on your RPi:
git clone https://github.com/kiwisaner/easypeasypi.git

To compile any of the examples, so something like this:
gcc -Wall -o ./bin/led ./src/led.cpp -lwiringPi -lstdc++

Note :   There are several warning messages when you compile, but you can ignore them.

I also provided a scriptso you can compile all the examples together like this:
cd /easypeasypi/examples
sudo ./compile.sh
	 
Running the examples:
All the binaries for examples are in ./easypeasypi/examples/bin


LED Example
===========
sudo ./led

Usage     : led <red> <green> <blue>
            Where <red> <green> <blue> indicate which colors to turn on
Example 1 : sudo ./led 1 0 0    -   This will turn the LED red
Example 2 : sudo ./led 1 1 1    -   This will turn on on red, green and blue all together
Example 3 : sudo ./led 0 0 0    -   LED will be completely off

BUTTON example
==============
$ sudo ./button
Usage   : button <period>
          Where is <period> we monitor for button presses in milliseconds
Example : sudo ./button 10000   (Monitor for 10 seconds 

BUZZER example:
===============
sudo ./buzzer
Usage   : buzzer <period>
          Where is <period> is how long buzzer will sound in milliseconds
Example : sudo ./buzzer 100   (Turns buzzer on for 1/10th of second)

TEMPERATURE example:
====================
sudo ./temperature
26.687
Note :  This simply gives the temperature in degrees C.  There is no command line options.

TRANSMIT example:
=================
pi@raspberrypi ~/easypeasypi/examples/bin $ sudo ./transmit
Usage   : transmit <code> <repeats>
          Where is <code> is the code to send
          Where is <repeats> is how many times the code is repeated
Example : sudo ./transmit abcdef 10
pi@raspberrypi ~/easypeasypi/examples/bin $

RECEIVE example:
=================
sudo ./receive
Usage   : receive <period>
          Where is <period> is how long we monitor for received data in milliseconds
Example : sudo ./receive 10000  (monitor for 10 seconds if anything is received)



	 