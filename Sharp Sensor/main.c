//************************************************************************************
//
//                      Sharp Sensor Test (C File)
//
//************************************************************************************
//  FileName:           main.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//************************************************************************************
//                          Description                     
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The firmware demonstrates interfacing a Sharp Sensor to the analog channel
// of LPC2148.The Sharp sensor detects an obstacle and reflects the distance from
// the obstacle by changing the analog voltage. The Analog readings are sampled by
// the 10-bit ADC on LPC2148 and converted to digital. The conrresponding digital
// values is converted into centimeters and displayed on the Chacrater LCD. 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for Pic Crush-1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	None	  
//
//  Switch Setting: None 
//
//	PINOUT:			Sharp Sensor   -   LPC2148 
//					-------------------------- 
//						Vo				P0.30
//
//***************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define SHARP_PIN		(1<<30)	//P0.29 as Input to Sharp Sensor
#define SHARP_PIN_DIR	(1<<28)	//Bit 29:28 of PINSEL1 register
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
	float temp=0.0;

	PINSEL1 |=	SHARP_PIN_DIR;	//Bit 29:28 of PINSEL1 register
	IODIR0	&=	~(SHARP_PIN);	//Select the AD0.3 of P0.28 as Input
	IODIR1|=0xFFFE0000;			//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);
	Adc0Init(10);				//Initialize ADC0 block with clockdiv=10 
								//Operate at 3MHz
	ClcdInit();					//Initialize the Character LCD
	ClcdCursorOff();			//Turn Off the blinking cursor

	ClcdGoto(5,1);
	ClcdPutS_P("Distance");
	ClcdGoto(11,2);
	ClcdPutS_P("cm");

    while(1)
	{
		temp=2*((2914 / ((float)Adc0Read(3) + 5)) - 1);
		ClcdGoto(5,2);
        ClcdPutFloat(temp);
        _DelayMs(100);       
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
