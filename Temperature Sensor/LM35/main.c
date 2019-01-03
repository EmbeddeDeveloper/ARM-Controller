//******************************************************************************
//
//               Temperature Sensor Interface Library (C File)
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
// The firmware demonstrates temperature display on LCD using an analog 
// temperature sensor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for ARM7 Development Board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	None	  
//
//  Switch Setting: None 
//
//	PINOUT:			LCD   -   LPC2148 			LM35	-	LPC2148
//					----------------- 			-------------------
//					DB4   -   	P0.17 			 Vout 		 P0.29
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
#define TEMP_PIN		(1<<29)	//P0.29 as Input to Temperature Sensor
#define TEMP_PIN_DIR	(1<<26)	//Bit 27:26 of PINSEL1 register 
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
	float temperature=0.0;

	PINSEL1 |=	TEMP_PIN_DIR;	//Bit 27:26 of PINSEL1 register
	IODIR0	&=	~(TEMP_PIN);	//Select the AD0.3 of P0.28 as Input
	Adc0Init(10);				//Initialize ADC0 block with clockdiv=10 
								//Operate at 3MHz
	ClcdInit();					//Initialize the Character LCD
	ClcdCursorOff();			//Turn Off the blinking cursor

	IODIR1|=0xFFFE0000;			//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);

	ClcdGoto(4,1);
	ClcdPutS_P("Temperature");
	ClcdGoto(11,2);
	ClcdSendByte(0XDF,1);       // Print the degree character
	ClcdPutCh('C');

    while(1)
	{
        temperature = (((float)Adc0Read(2)/1023.0)*3.3*100);
		ClcdGoto(6,2);
        ClcdPutFloat(temperature);
        _DelayMs(1000);       
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
    for (j=0;j<count;j++) {
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
