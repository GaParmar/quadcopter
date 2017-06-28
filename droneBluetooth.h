/*
 * Filename: droneBluetooth.h
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
void setupCommunication();

/*
 * Function name: getRawBluetoothString();
 * Function prototype: void getRawBluetoothString(char * s);
 * Description: Reads the current string being sent over the channel.
 * Parameters: 
 *		char * s -- Pointer to the String where the incoming string
 *					is to be stored.
 * Return: none
 */
void getRawBluetoothString(char * s);

/*
 * Function name: getType();
 * Function prototype: char * getType(char * s);
 * Description: Gets the type of communication being recieved by the drone
 *	by parsing the first character.
 * Parameters:
 *		char * s -- The string of current transmission
 * Return - String (char array) representing the type of transmission
 */
char * getType(char * s);

/*
 * Function name: getValue();
 * Function prototype: int getValue(char * s);
 * Description: Gets the value of communication being recieved by the drone
 * Parameters:
 *		char * s -- The string of current transmission
 * Return - int representing the value of transmission
 */
int getValue(char * s);