
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
//#include <fstream>
#include <iostream>
#include <iostream>
#include <wiringPi.h>
using namespace std;

// See http://pi.gadgetoid.com/pinout
#define RESOLUTION			10  // Can be 9 to 12 bits

using namespace std;


// Runs a command and return the response
std::string RunCmd(std::string cmd)
{
	std::string retVal;
	char resp[1035];
	FILE *fp;
   
	/* Open the command for reading. */
	fp = popen(cmd.c_str(), "r");
	if (fp == NULL) {
		printf("Failed to run command : %s\n", cmd.c_str());
		exit(1);
	}
 
    /* Read the output a line at a time - output it. */
	while (fgets(resp, sizeof(resp) - 1, fp) != NULL) {
		char* pch = strchr(resp, '\n');  // Get rid of any newline characters in reponse
		if (pch != NULL) {
			resp[pch - resp] = ' ';
		}
		retVal.append(resp);
	//	printf("%s", resp);
	}
	/* close */
	pclose(fp);
	return retVal;
}
	
	
	
string ReadTemperature()
{
	//  Find the temperature sensor
	string sensor = RunCmd("ls /sys/bus/w1/devices/");
	sensor = sensor.substr(0, sensor.find_first_of(" "));
	
	// Setup the sensor file name
	string sensorfile = "/sys/bus/w1/devices/";
	sensorfile.append(sensor);
	sensorfile.append("/w1_slave");
	
	// Read the sensor file contents and extract relevant data
	string cmd = "cat ";
	cmd = cmd.append(sensorfile);
	
	cmd = cmd.append(" | sed -n 's/^.*\\(t=[^ ]*\\).*/\\1/p' | sed 's/t=//' | awk '{x=$1}END{print(x/1000)}'");
	
	// Read the sensor data
	string temperature = RunCmd(cmd);
	return temperature;
}
	
	
	
int main(int argc, char *argv[])
{
	if (wiringPiSetup() == -1) {
		cout << "Could not set up wiringPi\r\n" << endl;
	}

	string temperature = ReadTemperature(); 
	cout <<  temperature <<  endl;
	return 0;
}