#include <iostream>
#include <stdlib.h>     
#include <wiringPi.h>

using namespace std;

char* dummy_args[] = { "button", "10000", NULL };

// See http://pi.gadgetoid.com/pinout
#define PUSH_BUTTON         6   // RPi pin 22 
// Button Press Debounce time in mS
#define DEBOUNCE_TIME 100


int main(int argc, char *argv[])
{
	//!!!!!!!!!!!!!!! Remove comments below for easy debugging (override command line parameters)  !!!!!!!!
	//argv = dummy_args;
	//argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	if (wiringPiSetup() == -1) {
		cout << "Could not set up wiringPi\r\n" << endl;
	}
	
	if (argc == 2) 
	{
		long period = atoi(argv[1]);
		unsigned int debounceTime = 0;
		unsigned long waittime = 0;
		bool buttonPressed = false;
		
		pinMode(PUSH_BUTTON, INPUT);
		do
		{
			if (digitalRead(PUSH_BUTTON) == HIGH) {
				// Wait for key to be released
				while (digitalRead(PUSH_BUTTON) == LOW) { usleep(1000); }
				
				// We have a valid button press
				buttonPressed = true;  	
			}
			usleep(1000 * 100);	 // Sleep for 100 ms
			waittime += 100;
		} while ((waittime < period) && (buttonPressed == false));

		if (buttonPressed) { cout << "ButtonPressed" << endl; }
		else { cout << "Timeout" << endl; }
	}	
	else {
		cout << "Usage   : button <period>" << endl;
		cout << "          Where is <period> we monitor for button presses in milliseconds" << endl; 
		cout << "Example : button 1000   (Monitor for 1 second (100ms)" << endl;
	}

	return 0;
}