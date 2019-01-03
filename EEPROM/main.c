//******************************************************************************
//
//                  			I2C EEPROM Test
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
// The firmware demonstrates the Read and write functionality to AT24C02 EEPROM.
// The Read and write status is displayed on the LCD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     			Hardware Settings for ARM7 Development Board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	None	  
//
//  Switch Setting: None 
//
//	PINOUT:			LCD   -   LPC2148 			EEPROM	-	LPC2148
//					-----------------			-------------------	 
//					DB4   -   	P0.17 			  SCL	-	P0.2
//					DB5   -   	P0.18 			  SDA	-	P0.3	
//					DB6   -   	P0.19
//					DB7   -   	P0.20 
//					RS    -   	P0.12 
//					E     -   	P0.13 
//					R/W   -   	GND
//******************************************************************************

//**************************INCLUDES********************************************
#include <LPC214x.H>                       
#include "config.h"
//**********************End of INCLUDES*****************************************

//***********************Private Prototypes*************************************
void _DelayMs(unsigned int delay);
//********************End of Private Prototypes*********************************

//**************************Extern Variables************************************
extern unsigned char readBuff[1]; 
//***********************End of Extern Variables********************************

//*****************************************************************************
// Function:        int main (void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main Loop
//
// Note:            None
//*****************************************************************************
int main (void) 
{
	unsigned char wrnum=80;
	
	IODIR1|=0xFFFE0000;				//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);    

    //Initialization of CLCD
    ClcdInit();
    
    //Display Demo Information
    ClcdPutS("  I2C EEPROM    ");
    ClcdGoto(1,2);
    ClcdPutS("  Rd/Wr Demo    ");
    _DelayMs(1000);
    ClcdClear(); //clear display
    
    //Initialization of EEPROM and I2C
    EepromInit();
 
    //Writing to EEPROM
    if(EepromByteWrite(11,wrnum)==1) 		// write to the address location
	{
    	ClcdGoto(1,1);           			// goto line 1
    	ClcdPutS("   Write Fail   ");     	// display astatus		
	}
	else
	{
    	ClcdGoto(1,1);           			// goto line 1
    	ClcdPutS("Data Write: ");     		// display data written
    	ClcdPutNum(wrnum);
	}
    _DelayMs(100);
 
    //Reading from EEPROM
    if(EepromByteRead(11)==1)       		// read from address
	{
    	ClcdGoto(1,2);           			// goto line 2
    	ClcdPutS("   Read Fail    ");     	// display status		
	}
	else
	{
	    ClcdGoto(1,2);         				// goto line 2
	    ClcdPutS("Data Read: ");      		// display data read
 	    ClcdPutNum((unsigned int)readBuff[0]);
	}
	
    while(1);
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
