#include <iostream>
#include <stdlib.h>  
#include <wiringPi.h>
#include "RPi_utils/RCSwitch.cpp"

using namespace std;

char* dummy_args[] = { "receive", "10000", NULL };

// See http://pi.gadgetoid.com/pinout
#define RF_RX_DATA_INT      2   // Receiver on interrupt 0 => that is pin #2
#define RF_RX_POWER_PIN     5   // RPi pin 18


// Button Press Debounce time in mS
#define DEBOUNCE_TIME 100


int main(int argc, char *argv[])
{
	unsigned long code = 0;
	uint  repeats = 0;
	RCSwitch rc = RCSwitch(); 
	unsigned long rxData = 0;
	
	//!!!!!!!!!!!!!!! Remove comments below for easy debugging (override command line parameters)  !!!!!!!!
	//argv = dummy_args;
	//argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	if (wiringPiSetup() == -1) {
		cout << "Could not set up wiringPi\r\n" << endl;
	}
	
	if (argc == 2)
	{
		bool retValue = false;
		RCSwitch rc = RCSwitch(); 
		unsigned long waittime = 0; 

		unsigned int period = atoi(argv[1]);   // Check how long
		pinMode(RF_RX_POWER_PIN, OUTPUT);      // Set the Receiver power pin to output mode, or input if state is 0
		digitalWrite(RF_RX_POWER_PIN, HIGH);   // Turn on power to the RF Receiver 
		rc.enableReceive(RF_RX_DATA_INT);      // Receiver on interrupt 1 => that is pin #2 on Arduino Micro board
		do
		{
			uint32_t endtime = millis() + 100;
			do {
				if (rc.available()) {
					rxData = rc.getReceivedValue();		
					retValue = true;
					rc.resetAvailable();
					endtime = millis();  // Exit loop
				}
			} while ((millis() < endtime) && (rxData == 0)); 
			waittime += 100;
		} while ((waittime < period) && (rxData == 0));

		if ((rxData > 0)) { cout << "received " << std::hex << rxData << endl; }
		else { cout << "Timeout" << endl; }

	}	
	else {
		cout << "Usage   : receive <period>" << endl;
		cout << "          Where is <period> is how long we monitor for received data in milliseconds" << endl; 
		cout << "Example : receive 10000  (monitor for 10 seconds if anything is received)" << endl;
	}
	return 0;
}

