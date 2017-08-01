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
  		int i = 0;
  		for (i=0; i<67; i++)
  			*(s+i) = BTSerial.read();
  	}
  	else
  		s = {'E', 'R', 'R', 'O', 'R'};
}


/*
 * Function name: getPIDRollConstants
 * Function prototype: void getPIDRollConstants (char * s, int * p, int * i, int * d);
 * Description: Gets the PID constants for the roll controller
 * Parameter:
 *		char * s -- Pointer to the string containing the latest incoming signal
 *		int * p -- Pointer to the roll proportional constant
 *		int * i -- Pointer to the roll integral constant
 *		int * d -- Pointer to the roll differential constant
 */
void getPIDRollConstants (char * s, int * p, int * i, int * d)
{
	int start = 19;
	char * propSeg = {s[start], s[start+1], s[start+2], s[start+3]};
	char * intSeg = {s[start+4], s[start+5], s[start+6], s[start+7]};
	char * diffSeg = {s[start+8], s[start+9], s[start+10], s[start+11]};
	int prop = atoi(propSeg);
	int inte = atoi(intSeg);
	int diff = atoi(diffSeg);
	&p = prop;
	&i = inte;
	&d = diff;
}


/*
 * Function name: getPIDPitchConstants
 * Function prototype: void getPIDPitchConstants (char * s, int * p, int * i, int * d);
 * Description: Gets the PID constants for the pitch controller
 * Parameter:
 *		char * s -- Pointer to the string containing the latest incoming signal
 *		int * p -- Pointer to the pitch proportional constant
 *		int * i -- Pointer to the pitch integral constant
 *		int * d -- Pointer to the pitch differential constant
 */
void getPIDPitchConstants (char * s, int * p, int * i, int * d)
{
	int start = 31;
	char * propSeg = {s[start], s[start+1], s[start+2], s[start+3]};
	char * intSeg = {s[start+4], s[start+5], s[start+6], s[start+7]};
	char * diffSeg = {s[start+8], s[start+9], s[start+10], s[start+11]};
	int prop = atoi(propSeg);
	int inte = atoi(intSeg);
	int diff = atoi(diffSeg);
	&p = prop;
	&i = inte;
	&d = diff;
}


/*
 * Function name: getPIDYawConstants
 * Function prototype: void getPIDYawConstants (char * s, int * p, int * i, int * d);
 * Description: Gets the PID constants for the yaw controller
 * Parameter:
 *		char * s -- Pointer to the string containing the latest incoming signal
 *		int * p -- Pointer to the yaw proportional constant
 *		int * i -- Pointer to the yaw integral constant
 *		int * d -- Pointer to the yaw differential constant
 */
void getPIDYawConstants (char * s, int * p, int * i, int * d)
{
	int start = 43;
	char * propSeg = {s[start], s[start+1], s[start+2], s[start+3]};
	char * intSeg = {s[start+4], s[start+5], s[start+6], s[start+7]};
	char * diffSeg = {s[start+8], s[start+9], s[start+10], s[start+11]};
	int prop = atoi(propSeg);
	int inte = atoi(intSeg);
	int diff = atoi(diffSeg);
	&p = prop;
	&i = inte;
	&d = diff;
}


/*
 * Function name: getRoll
 * Function prototype: void getRoll(char * s, int * roll);
 * Description: Updates the roll value
 * Parameters:
 *		char * s -- Pointer to the string containting the incoming signal
 *		int * roll -- Pointer to the int storing the roll value
 */
void getRoll(char * s, int * roll);


/*
 * Function name: getPitch
 * Function prototype: void getPitch(char * s, int * pitch);
 * Description: Updates the pitch value
 * Parameters:
 *		char * s -- Pointer to the string containting the incoming signal
 *		int * pitch -- Pointer to the int storing the pitch value
 */
void getPitch(char * s, int * pitch);


/*
 * Function name: getYaw
 * Function prototype: void getYaw(char * s, int * yaw;
 * Description: Updates the yaw value
 * Parameters:
 *		char * s -- Pointer to the string containting the incoming signal
 *		int * yaw -- Pointer to the int storing the yaw value
 */
void getYaw(char * s, int * Yaw);


/*
 * Function name: getThrottle
 * Function prototype: void getThrottle(char * s, int * throttle);
 * Description: Updates the throttle value
 * Parameters:
 *		char * s -- Pointer to the string containting the incoming signal
 *		int * throttle -- Pointer to the int storing the throttle value
 */
void getThrottle(char * s, int * throttle);

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