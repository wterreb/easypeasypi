#include <iostream>
#include <stdlib.h>  
#include <wiringPi.h>
#include "RPi_utils/RCSwitch.cpp"

using namespace std;

char* dummy_args[] = { "transmit", "12345", "10", NULL };

// See http://pi.gadgetoid.com/pinout
#define RF_TX_DATA_PIN      0  // RPi pin 11 
#define RF_TX_POWER_PIN     9  //  RPi pin 5
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
	
	unsigned long code = 0;
	uint  repeats = 0;
	RCSwitch rc = RCSwitch(); 
	
	if (argc > 1) { code = strtol(argv[1], NULL, 16); }
	if (argc == 3) { repeats = atoi(argv[2]); }

	

	if (argc == 3)
	{
		pinMode(RF_TX_POWER_PIN, OUTPUT);      // Set the Transmitter power pin to output mode
		digitalWrite(RF_TX_POWER_PIN, HIGH);   // Turn on power to the RF Transmitter 
		rc.setRepeatTransmit(repeats);         // Set the number of repeats
		rc.enableTransmit(RF_TX_DATA_PIN);     // Set Transmitter to the correct IO pin
		rc.send(code, 24);                     // Send the actual code
		digitalWrite(RF_TX_POWER_PIN, LOW);    // Turn off power to the RF Transmitter 
		cout << "sent " << std::hex << code << endl; 
	}	
	else {
		cout << "Usage   : transmit <code> <repeats>" << endl;
		cout << "          Where is <code> is the code to send" << endl; 
		cout << "          Where is <repeats> is how many times the code is repeated" << endl; 
		cout << "Example : transmit abcdef 10" << endl;
	}
	
	return 0;
}
