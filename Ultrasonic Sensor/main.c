//******************************************************************************
//
//                  Maxbotics Ultrasonic Sensor Test
//
//******************************************************************************
// FileName:        main.c
// Microcontroller: LPC2148
// Compiler:        Keil
// Target Hardware: ARM7 Development Board
// Company:         ENTESLA
//******************************************************************************
//                          Description                     
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The firmware demonstrates reading Analog value from Sensor and display 
// distance in cm on the LCD.For 5V supply to sensor a 9.8mV/inch i.e approx. 
// an adc count of 1.2 is equal to 1cm
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 		 Hardware Settings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	None	  
//
//  Switch Setting: None 
//
//	PINOUT:			Ultrasonic Sensor   -   LPC2148 
//					------------------------------- 
//							AN				 P0.30
//
//***************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define ULTRASONIC			(1<<30)	//P0.29 as Input to Sensor
#define ULTRASONIC_PIN_DIR	(1<<28)	//Bit 29:28 of PINSEL1 register
//*******************End of Private Macro Definitions***************************

//************************Private Protoype**************************************
void _DelayMs(unsigned int count);
//*******************End of Private Protoype************************************

//*****************************************************************************
// Function:        int main(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main enrty point.
//
// Note:            None
//*****************************************************************************
int main() 
{
	PINSEL1 |=	ULTRASONIC_PIN_DIR;	//Bit 29:28 of PINSEL1 register
	IODIR0	&=	~(ULTRASONIC);		//Select the AD0.3 of P0.28 as Input
	IODIR1|=0xFFFE0000;				//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);
	Adc0Init(10);					//Initialize ADC0 block with clockdiv=10 
									//Operate at 3MHz
	ClcdInit();						//Initialize the Character LCD
	ClcdCursorOff();				//Turn Off the blinking cursor

	ClcdPutS("Ultrasonic Dist.");
	ClcdGoto(6,2);
	ClcdPutS("DEMO");
	_DelayMs(2000);
	ClcdClear();
	ClcdGoto(5,1);
	ClcdPutS_P("Distance");

    while(1)
	{		
		ClcdGoto(6,2);
		ClcdPutNum(Adc0Read(3)*0.8333);
		ClcdPutS("cms    ");
        _DelayMs(200);       
    }
}

//*****************************************************************************
// Function:        void _DelayMs(unsigned int count)
//
// Input:           Delay in milliseconds
//
// Output:          None
//
// Overview:        Generates a delay of specified number of milliseconds.
//
// Note:            None
//*****************************************************************************
void _DelayMs(unsigned int count) 
{
    volatile unsigned int j,k;
    for (j=0;j<count;j++) 
	{
        for (k=0;k<6000;k++) 
		{
            __asm 
			{
                nop;
                nop;
            }
        }
    }
}
