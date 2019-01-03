//******************************************************************************
//
//                  Real Time Clock Test
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
// The firmware displays the time on the Character LCD. The clock is derived 
// from on-chip RTC module connected to an external crystal of 32.768kHz
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   		              Hardware Settings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	Processor: 12 MHz, RTC:32.768kHz
//  Jumper Setting:	None	  
//
//  Switch Setting: None 
//
//	PINOUT:			LCD   -   LPC2148 		
//					----------------- 
//					DB4   -   	P0.17 
//					DB5   -   	P0.18 
//					DB6   -   	P0.19
//					DB7   -   	P0.20 
//					RS    -   	P0.12 
//					E     -   	P0.13 
//					R/W   -   	GND
//***************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
//**********************End of INCLUDES*****************************************

//***********************Private Fuction Prototypes****************************
void CLcdPutTime(void);
void _DelayMs(unsigned int count);
//*********************End of Private Fuction Prototypes*********************** 

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
	RtcInit();	   	//RTC Initialization
	ClcdInit();		//Clcd Initialization
	ClcdCursorOff();
	RtcSetTime();	//Sets time every time the system is reset
	ClcdGoto(1,1);
	ClcdPutS("Real Time Clock");
	ClcdGoto(6,2);
	ClcdPutS("Demo");
	_DelayMs(1000);
	ClcdClear();
	while(1)
	{
		ClcdGoto(5,1);
		CLcdPutTime();
	}
}

//*****************************************************************************
// Function:        void CLcdPutTime(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main enrty point.
//
// Note:            None
//*****************************************************************************
void CLcdPutTime(void)
{
    ClcdPutCh('0'+(HOUR/10));
    ClcdPutCh('0'+(HOUR%10));
    ClcdPutCh(':');
    ClcdPutCh('0'+(MIN/10));
    ClcdPutCh('0'+(MIN%10));
    ClcdPutCh(':');
    ClcdPutCh('0'+(SEC/10));
    ClcdPutCh('0'+(SEC%10));
}

//*****************************************************************************
// Function:        void _DelayMs(unsigned int delay)
//
// Input:           Delay in milliseconds
//
// Output:          None
//
// Overview:        Generates a delay of specified number of milliseconds.
//
// Note:            Calibrated for 12MHz crystal
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
