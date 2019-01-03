//******************************************************************************
//
//                  		Analog In Demo
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
// The firmware demonstrates display of analog voltage on LCD. The analog voltage
// is varied using potentiometer connected to P0.28
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 		 Hardware Settings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP6 to connect Analog In to P0.28	  
//
//  Switch Setting: None 
//
//	PINOUT:			LCD   -   LPC2148 			POT		-	LPC2148
//					----------------- 			-------------------
//					DB4   -   	P0.17 			Vout		P0.28
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
 
//**********************Private Macro Definitions*******************************
#define ANALOG_IN		(1<<28)		//Assign Analog In to P0.28				   
#define ANALOG_IN_DIR	(1<<24)		//Assign Direction register bits 
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
	float val=0.0; 
 	
	PINSEL1 |=	ANALOG_IN_DIR;				//Bit 25:24 of PINSEL1 register
	IODIR0	&=	~(ANALOG_IN);				//Select the AD0.2 Input
	Adc0Init(10);   						//pass channel number and clkdiv 
											//Operate at 3MHz 
	IODIR1|=0xFFFE0000;						//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);
		
	ClcdInit();
	ClcdCursorOff();

	ClcdGoto(2,1);
	ClcdPutS_P("Analog In Demo");

	_DelayMs(1000);							//A delay of 1 second

	ClcdClear();							//Clear all contents on screen

	ClcdGoto(4,1);
	ClcdPutS_P("Analog In");
	ClcdGoto(10,2);
	ClcdPutS_P("V"); 

		

	while(1)
	{ 
		val=Adc0Read(1);					//Select channel number					 
		val= (val*3.3)/1023.0;        		//Converting in volts
		
		ClcdGoto(6,2);
		ClcdPutFloat(val); 					//Display Analog voltage on Character LCD

		_DelayMs(500); 						//A lil delay 
	}
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
