//******************************************************************************
//
//                  		LCD 16X2 (CLCD) Demo
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
// The firmware demonstrates the basic functionality of LCD 16X2 (CLCD) in 4-bit
// Interface for the ARM7 development Board. The firmware initializes the
// CLCD as defined in the user settings and displays a message on it.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for Pic Crush-1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
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
																				
//************************Private Protoype**************************************
void _DelayMs(unsigned int delay);
//*******************End of Private Protoype************************************

//**************************************************************************
// Function:        void main(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main program entry point.
//
// Note:            None
//**************************************************************************
int main(void) 
{
    char    visitUsAt[] =   "  Visit us at   ";
    char    entesla[]   =   "....ENTESLA....";
    unsigned char   i;

    PINSEL0 = 0;
	PINSEL1 = 0;
	PINSEL2 &= 0x0000000C;
	PINSEL2 |= 0x00000030;
    ClcdInit();
    ClcdCursorOff();   
    
    for(i=0; i<3; i++) 
	{
        ClcdGoto(9,1);
        ClcdPutCh(i+'1');
        ClcdGoto((1 + i*3),2);
        ClcdPutCh('*');
        ClcdPutCh('*');
        ClcdPutCh('*');
        ClcdGoto((14 - i*3),2);
        ClcdPutCh('*');
        ClcdPutCh('*');
        ClcdPutCh('*');
        _DelayMs(1000);
    }

    while(1)
	 {
        ClcdClear();
        ClcdGoto(1,1);
        ClcdPutS_P(" LCD 16X2 DEMO ");
        ClcdGoto(1,2);
        ClcdPutS(entesla);
        _DelayMs(2000);
        ClcdClear();
        ClcdGoto(1,1);
        ClcdPutS(visitUsAt);
        ClcdGoto(1,2);
        ClcdPutS_P("www.entesla.com");
        _DelayMs(2000);
    }        
}

//*****************************************************************************
// Function:        void _DelayMs(unsigned int count)
//
// Input:           count in milliseconds
//
// Output:          None
//
// Overview:        Delay in milliseconds.
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
