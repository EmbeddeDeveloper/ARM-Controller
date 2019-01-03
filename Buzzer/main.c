//******************************************************************************
//
//                  			Buzzer Test
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
// The firmware demonstrates a simple Buzzer test. The Buzzer generates an audible
// tone with an ON/OFF time of 250 milliseconds.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for Pic Crush-1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP8 to connect P0.21 In to Buzzer	  
//
//  Switch Setting: None 
//
//	PINOUT:			Buzzer   -   LPC2148 
//					-------------------- 
//					NPN-base      P0.21
//
//***************************************************************************

//**************************INCLUDES********************************************
#include <LPC214x.h>
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define BUZZ_PIN		(1<<21)			//P0.21 as Output to Buzzer
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

int main(void)
{
	IODIR0	|=	BUZZ_PIN;		//Select the Buzzer pin as Output
	IOPIN0	&= ~(BUZZ_PIN);		//Clear the Buzzer pin

    while(1)
	{
		IOPIN0 |= BUZZ_PIN;		//Set the Buzzer pin High
		_DelayMs(250);	  		//A Delay
		IOPIN0 &= ~BUZZ_PIN;	//Set the Buzzer pin Low
		_DelayMs(250);	       	//A Delay
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
// Note:            Calibrated at 12MHz
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
