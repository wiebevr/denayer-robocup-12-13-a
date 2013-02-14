
#include "RP6RobotBaseLib.h"
#define PSU
//#define BATT
#define Debug

char receiveBuffer[UART_RECEIVE_BUFFER_SIZE+1];
char Buf2[UART_RECEIVE_BUFFER_SIZE+1];
static uint8_t info_left = false;
static uint8_t info_right = false;

//-------------------------------------------------------------------//
void writeNewline(void)
{
	writeChar(10);
	writeChar(13);
}
//-------------------------------------------------------------------//

uint8_t getInputLine(void)
{ 
	static uint8_t buffer_pos = 0;
	if(getBufferLength()) 
	{							
		receiveBuffer[buffer_pos] = readChar();
		if(receiveBuffer[buffer_pos]==13)			// was '\n'
		{
			receiveBuffer[buffer_pos]='\0'; 
			buffer_pos = 0;
			return 1;
		}
		else if(buffer_pos >= 32)
		{									
			receiveBuffer[32]='\0';	
			buffer_pos = 0;
			return 2;
		}
		buffer_pos++;
	}
	return 0;
}
//-------------------------------------------------------------------//
void printUBat(uint16_t uBat)
{
	writeIntegerLength((((uBat/102.4f)+0.1f)), DEC, 2);
	writeChar('.');
	writeIntegerLength((((uBat/1.024f)+10)), DEC, 2);
	writeChar('V');
}
//-------------------------------------------------------------------//
void enterString(void)
{
	while(!getInputLine())
	{
		task_RP6System();
	}
}
//-------------------------------------------------------------------//
void testPowerOn(void)
{	
	writeString_P("PowerOn test started");
	writeNewline();
	task_RP6System();
	mSleep(1000);
	powerON();
	mSleep(1000);
	powerOFF();
	mSleep(1000);
	powerON();
	mSleep(2000);
	task_RP6System();
	powerOFF();
	mSleep(500);
	powerON();	
	writeString_P("PowerOn test finished");
	writeNewline();
}
//-------------------------------------------------------------------//
void testLED(void)
{	
	writeString_P("LED test started");
	writeNewline();
	uint8_t testLEDs = 1;
	uint8_t i;
	for(i = 0; i < 6; i++)
	{
		setLEDs(testLEDs); 
		testLEDs <<= 1; 		
		mSleep(400);
		task_RP6System();
	}
	writeString_P("LED test finished");
	writeNewline();	
}

//-------------------------------------------------------------------//
void testVoltageSensor(void)
{	
	uint16_t ubat;	
	writeString_P("Voltage = ");	
	ubat = readADC(ADC_BAT);
	printUBat(ubat);
	writeNewline();
			
	task_RP6System();	
	mSleep(200);
}
//-------------------------------------------------------------------//

void testLightSensors(void)
{	
	uint16_t sens_l;
	uint16_t sens_r;
	clearReceptionBuffer();
				
	sens_l = readADC(ADC_LS_L);
	sens_r = readADC(ADC_LS_R);
			
	writeString_P("L= ");
	writeIntegerLength(sens_l, DEC, 4);
	writeString_P(",  R= ");
	writeIntegerLength(sens_r, DEC, 4);
	writeNewline();
} 
//-------------------------------------------------------------------//
void acsStateChanged(void)
{
	writeString_P("L: ");
	if(obstacle_left) // Obstacle on the left
		writeChar('o');
	else
		writeChar(' ');
	writeString_P(" | R: ");
	
	if(obstacle_right) // Obstacle on the right
		writeChar('o');
	else
		writeChar(' ');
	writeNewline();
	statusLEDs.LED6 = obstacle_left && obstacle_right; // In the middle?
	statusLEDs.LED3 = statusLEDs.LED6;
	statusLEDs.LED5 = obstacle_left;	// Obstacle on the left
	statusLEDs.LED4 = (!obstacle_left); // LED5 inverted!
	statusLEDs.LED2 = obstacle_right;	// Hindernis on the right
	statusLEDs.LED1 = (!obstacle_right); // LED2 inverted!
	updateStatusLEDs();
}
//-------------------------------------------------------------------//
/**
 * This function works similar to the ACS function and gets called everytime the
 * Bumpers are hit (the Bumpers need to be pressed down for at least 100ms to make
 * sure that it is registered by the program!)
 */
void bumpersStateChanged(void)
{
	writeString_P("BPL: ");	
	if(bumper_left)  // Left Bumper
		writeChar('o');
	else
		writeChar(' ');
		
	writeString_P(" | BPR: ");
	
	if(bumper_right) // Right Bumper
		writeChar('o');
	else
		writeChar(' ');
	writeNewline();
}
//-------------------------------------------------------------------//
void ShowMenu(void)
{
	writeNewline();
	writeString_P("#################################################################"); 
	writeNewline();
	writeString_P("####################       Main Menu         ####################"); 	
	writeNewline();
	writeString_P("# m - Show Menu\t\t\t\t\t\t\t#"); 
	writeNewline();
	writeString_P("# p - PowerOn Test\t\t\t\t\t\t#"); 
	writeNewline();
	writeString_P("# t - LED Test\t\t\t\t\t\t\t#"); 
	writeNewline();
	writeString_P("# v - Voltage Sensor Test\t\t\t\t\t#"); 
	writeNewline();
	writeString_P("# d - Drive at specified speed [direction] [speed 1] [speed 2]\t#"); 		
	writeNewline();
	writeString_P("# e - Drive specified distance [direction] [speed] [distance]\t#"); 		
	writeNewline();
	writeString_P("# r - Rotate [direction] [speed] [degree]\t\t\t#"); 		
	writeNewline();
	writeString_P("# s - Stop driving\t\t\t\t\t\t#"); 	
	writeNewline();	
	writeString_P("# l - Light Sensor\t\t\t\t\t\t#");
	writeNewline();
	writeString_P("# a - ACS [status]\t\t\t\t\t\t#");
	writeNewline();
	writeString_P("#################################################################"); 
	writeNewline();		
}

//-------------------------------------------------------------------//

int main(void)
{	
	uint16_t dist = 0;
	uint16_t degree = 0;
	uint16_t speed_value_1 = 0;
	uint16_t speed_value = 0;
	uint16_t speed_value_2 = 0;
	
	
	//----- robot initialisation -----//
	initRobotBase();						
	setLEDs(0b111111);
	mSleep(1500);
	setLEDs(0b100001);
	//----- end robot initialisation -----//
	
	powerON(); 	// Turn Encoders, Motor Current Sensors 
				// (and ACS IR Receiver and PWRON LED) on.
				// ATTENTION: Automatic Motor control will not work without this!
				
	ShowMenu();
	
	BUMPERS_setStateChangedHandler(bumpersStateChanged); // moet dit niet in de while lus staan?
	// ---------------------------------------
	// Main loop:	
	
	while(true)
	{
		task_RP6System();				
		enterString();
		/*************************************************************/			
		if(receiveBuffer[0] == 'p')
		{
			testPowerOn();					// PowerOn Test
		}
		/*************************************************************/			
		if(receiveBuffer[0] == 't')
		{
			testLED();						// LED Test
		}
		/*************************************************************/			
		if(receiveBuffer[0] == 'v')
		{
			testVoltageSensor();			// Voltage sensor Tesy
		}
		/*************************************************************/			
		if(receiveBuffer[0] == 'd')			// drive in a specified direction at a specified direction
		{			
			if(receiveBuffer[2]=='L')		// Drive direction is Left
			{				
				writeString_P("L ");			
				changeDirection(LEFT);
			}else if(receiveBuffer[2]=='R')	// Drive direction is Right
			{
				#ifdef Debug
				writeString_P("R ");
				#endif
				changeDirection(RIGHT);
			}else if(receiveBuffer[2]=='F')	// Drive direction is Forward
			{
				writeString_P("F ");
				changeDirection(FWD);
			} else if(receiveBuffer[2]=='B') // Drive direction is Backward
			{
				writeString_P("B ");
				changeDirection(BWD);
			} else                     		// Drive direction was not recognised	
			{				
				continue;
			}
			
			char part[15];
			memcpy(part, receiveBuffer + 4 /* Offset */, 10 /* Length */);
			part[15] = 0; /* Add terminator */
			char * pEnd;			
			speed_value_1 = strtol (part,&pEnd,10);
			if(speed_value_1 > 200 || speed_value_1<0)	
			{
				writeString_P("Error1");	
				writeNewline();
				continue;
			}
			
			speed_value_2 = strtol (pEnd,&pEnd,10);			
			if(speed_value_2 > 200 || speed_value_2<0)	
			{
				writeString_P("Error2");	
				writeNewline();
				continue;
			}
			
			writeInteger(speed_value_1,DEC);	
			writeString_P(" ");					
			writeInteger(speed_value_2,DEC);	
			writeNewline();
			
			moveAtSpeed(speed_value_1,speed_value_2); // Set desired speed
						
		}	
		/*************************************************************/			
		if(receiveBuffer[0] == 'e')			// drive a certain distance
		{		
			char part[15];
			memcpy(part, receiveBuffer + 4 /* Offset */, 10 /* Length */);
			part[15] = 0; /* Add terminator */
			char * pEnd;			
			speed_value = strtol (part,&pEnd,10);			
			if(speed_value > 200 || speed_value<0)	
			{
				writeString_P("Error3");
				writeNewline();
				continue;	
			}
			
			dist = strtol (pEnd,&pEnd,10);			
			if(dist > 20000 || dist <0)
			{
				writeString_P("Error4");	
				writeNewline();
				continue;
			}										
			
			writeInteger(dist,DEC);	
			writeString_P(" ");
			writeInteger(speed_value,DEC);				
			
			if(receiveBuffer[2]=='F')
			{
				writeString_P("F ");
				move(speed_value,FWD,dist,false);
			}			
			if(receiveBuffer[2]=='B')
			{
				writeString_P("B ");
				move(speed_value,BWD,dist,false);
			}
		}	
		/*************************************************************/			
		if(receiveBuffer[0] == 'r')			// Rotate
		{		
			char part[15];
			memcpy(part, receiveBuffer + 4 /* Offset */, 10 /* Length */);
			part[15] = 0; /* Add terminator */
			char * pEnd;			
			speed_value = strtol (part,&pEnd,10);
			degree = strtol (pEnd,&pEnd,10);			
			writeInteger(speed_value,DEC);	
			writeString_P(" ");
			writeInteger(degree,DEC);	
					
			if(receiveBuffer[2]=='L')
			{
				writeString_P(" L");
				rotate(speed_value, LEFT, degree, true); // Rotate 180
			} else if(receiveBuffer[2]=='R')
			{
				writeString_P(" R");
				rotate(speed_value, RIGHT, degree, true); // Rotate 180
			}
			else
			{
				writeString_P(" Error5");				
			}			
		}	
		/*************************************************************/			
		if(receiveBuffer[0] == 's')			// stop
		{		
			moveAtSpeed(0,0); // Set desired speed
		}	
		/*************************************************************/			
		if(receiveBuffer[0] == 'l')			// testLightSensors
		{		
			testLightSensors();
		}
		/*************************************************************/			
		if(receiveBuffer[0] == 'a')			// ACS measurement
		{		
			if(receiveBuffer[2]=='1')
			{
				ACS_setStateChangedHandler(acsStateChanged);
				powerON(); // Activate the IR receiver (incl. encoders etc.)
				setACSPwrMed(); // set the ACS medium transmit power.
				writeString_P("ACS ON");
				writeNewline();
			}
			else if(receiveBuffer[2]=='0')
			{
				setACSPwrOff();
				writeString_P("ACS OFF");
				writeNewline();
			}
		}
		/*************************************************************/	
		if(receiveBuffer[0] == 'm')			// show menu
		{
			ShowMenu();
		}
							
	}
	// End of main loop
	// ---------------------------------------
	
	
	return 0;
}
