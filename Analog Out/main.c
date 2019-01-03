//******************************************************************************
//
//                  		DAC Test
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
// The firmware demonstrates the Digital to Analog Conversion. A power amplifier
// with a gain of 20 is available on-board. A saw tooth waveform is generated on 
// P0.25. Observe the waveform on the oscilloscope by hooking a probe to P0.25.
// The waveform generated can also be heard as sound if headphones are plugged in 
// to the 3.5mm jack provided. 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for Pic Crush-1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP5 to connect Aout to Power Amplifier	  
//
//  Switch Setting: None 
//
//	PINOUT:			Power Amplifier   -   LPC2148 
//					----------------------------- 
//						VIN(+)   	  -   	P0.25 
//
//***************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define DAC_BIAS 0 
//*******************End of Private Macro Definitions***************************

//************************Private Protoype**************************************
void DacInit( void );
void _Delay45Us(void);
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
int main (void)
{
    unsigned int i = 0;

    DacInit();					//Initialize the DAC
	IODIR1|=0xFFFF0000;			//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);

    while (1) 
	{
		DacOut(i);
		i++;
		if ( i == 1023 )
		{
		    i = 0;
		}
		_Delay45Us();
    }
}

//*****************************************************************************
// Function:        void _ClcdDelay45Us(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        A 45 microseconds delay
//
// Note:            Calibrated for 12MHz crystal
//*****************************************************************************
void _Delay45Us(void) 
{
	volatile unsigned int k;
	for(k=0;k<409;k++)
	{
            __asm 
			{
                nop;
            }
	}
} 
