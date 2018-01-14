#include <iostream>
#include <stdlib.h>     
#include <wiringPi.h>

using namespace std;

char* dummy_args[] = { "buzzer", "100", NULL };

// See http://pi.gadgetoid.com/pinout
#define BUZZER_POS              7   // RPi pin 7 
#define BUZZER_NEG              11  // RPi pin 16 

int main(int argc, char *argv[])
{
	//!!!!!!!!!!!!!!! Remove comments below for easy debugging (override command line parameters)  !!!!!!!!
	//argv = dummy_args;
	//argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	if (wiringPiSetup() == -1) { cout << "Could not set up wiringPi\r\n" << endl; }
	
	if (argc == 2) {
		unsigned int period = atoi(argv[1]);
		
		// NOTE : We toggle both the positive and negative supply sides of the buzzer.   This was done to prevent
		//        the buzzer from sounding while the RPi is busy boothing up.
		pinMode(BUZZER_POS, OUTPUT);
		pinMode(BUZZER_NEG, OUTPUT);
		digitalWrite(BUZZER_POS, HIGH);	    
		digitalWrite(BUZZER_NEG, LOW);
		delay(period);		
		digitalWrite(BUZZER_POS, LOW);	
		digitalWrite(BUZZER_NEG, HIGH);
	}
	else {
		cout << "Usage   : buzzer <period>" << endl;
		cout << "          Where is <period> is how long buzzer will sound in milliseconds" << endl; 
		cout << "Example : epBuzzer 100   (Turns buzzer on for 100ms)" << endl;
	}
	return 0;
}