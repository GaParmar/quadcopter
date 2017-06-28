/*
 * Filename: droneBluetooth.c
 * 
 * Author: Gaurav Parmar
 *
 * Description: Declares the subroutines for the communication between 
 * drone and the bluetooth controller device.
 */

#include <SoftwareSerial.h>

/*
 * Function Name: setupCommunication();
 * Function Prototype: void setupCommunication();
 * Description: Initializes the bluetooth communication with the
 *              controller.
 * Parameters: none
 * Return: none
 */
void setupCommunication()
{
	SoftwareSerial BTSerial(4, 5);
	BTSerial.begin(9600);
}

/*
 * Function name: getRawBluetoothString();
 * Function prototype: void getRawBluetoothString(char * s);
 * Description: Reads the current string being sent over the channel.
 *	If there is error communicating, the string is set to "ERROR".
 * Parameters: 
 *		char * s -- Pointer to the String where the incoming string
 *					is to be stored.
 * Return: none
 */
void getRawBluetoothString(char * s)
{
  	if (BTSerial.available())
  	{
    	*s = BTSerial.read();
    	*(s+1) = BTSerial.read();
    	*(s+2) = BTSerial.read();
    	*(s+3) = BTSerial.read();
    	*(s+4) = BTSerial.read();
  	}
  	else
  		s = {'E', 'R', 'R', 'O', 'R'};
}

/*
 * Function name: getType();
 * Function prototype: char * getType(char * s);
 * Description: Gets the type of communication being recieved by the drone
 *	by parsing the first character.
 * Parameters:
 *		char * s -- The string of current transmission
 * Return - String (char array) representing the type of transmission
 */
char * getType(char * s)
{
	switch(*s)
	{
		case 'r':
			return "roll";
		case 'p':
			return "pitch";
		case 'y':
			return "yaw";
		case 't':
			return "thrust";
		default:
			return "ERROR";
	}
}

/*
 * Function name: getValue();
 * Function prototype: int getValue(char * s);
 * Description: Gets the value of communication being recieved by the drone
 * Parameters:
 *		char * s -- The string of current transmission
 * Return - int representing the value of transmission
 */
int getValue(char * s)
{
	int Thousands = *(s+1) - 48;
	int Hundreds = *(s+2) - 48;
	int Tens = *(s+3) - 48;
	int Ones = *(s+4) - 48;
	return (Thousands*1000 + Hundreds*100 + Tens*10 + Ones);
}