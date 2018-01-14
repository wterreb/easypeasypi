#include <iostream>
#include <stdlib.h>     
#include <wiringPi.h>

using namespace std;

char* dummy_args[] = { "led", "0", "0", "0", NULL };

// See http://pi.gadgetoid.com/pinout
#define LED_RED              4   // RPi pin 16
#define LED_GREEN            8   // RPi pin 3 
#define LED_BLUE             1   // RPi pin 12

int main(int argc, char *argv[])
{
	//!!!!!!!!!!!!!!! Remove comments below for easy debugging (override command line parameters)  !!!!!!!!
	//argv = dummy_args;
	// = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	if (wiringPiSetup() == -1) { cout << "Could not set up wiringPi\r\n" << endl; }
	
	if (argc == 4) {
		unsigned int period = atoi(argv[1]);
		
		int redState = atoi(argv[1]);
		int greenState = atoi(argv[2]);
		int blueState = atoi(argv[3]);
		
		// NOTE : We toggle both the positive and negative supply sides of the buzzer.   This was done to prevent
		//        the buzzer from sounding while the RPi is busy boothing up.
		pinMode(LED_RED, OUTPUT);
		pinMode(LED_GREEN, OUTPUT);
		pinMode(LED_BLUE, PWM_TONE_OUTPUT);
	
		digitalWrite(LED_RED, redState);
		digitalWrite(LED_GREEN, greenState);
		
		//  The blue LED is connected to a PWM output so we control its brightness where 1023 is fully on
		if (blueState)
			pwmWrite(LED_BLUE, 1023);  // full power
		else
			pwmWrite(LED_BLUE, 0);     // off


	}
	else {
		cout << "Usage     : led <red> <green> <blue>" << endl;
		cout << "            Where <red> <green> <blue> indicate which colors to turn on" << endl; 
		cout << "Example 1 : led 1 0 0    -   This will turn the LED red" << endl;
		cout << "Example 2 : led 1 1 1    -   This will turn on on red, green and blue all together" << endl;
		cout << "Example 3 : led 0 0 0    -   LED will be completely off" << endl;
	}
	return 0;
}