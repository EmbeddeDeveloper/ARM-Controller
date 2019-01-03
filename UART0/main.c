//******************************************************************************
//
//                       	RS232-0 Test
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
// The firmware demonstrates the Transmit and Recieve test on UART0. Connect
// Arm7 development board to a computer using a serial cable on RS232-0 
// Interface. Open a Terminal program like HyperTerminal or Tera Term.
// Transmit some random data; the data transmitted will be echoed back.	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for ARM7 development board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP2 to connect RXD0 and TXD0 to RS232-0.	  
//
//  Switch Setting: None 
//
//	PINOUT:			Computer   -   LPC2148 
//					---------------------- 
//					RX		   -    TXD0 
//				    TX         -   	RXD0
//					GND        -    GND
//*****************************************************************************

//**************************INCLUDES*******************************************
#include "config.h"
//**********************End of INCLUDES****************************************
 
//************************Private Protoype*************************************
void _DelayMs(unsigned int count);
//*******************End of Private Protoype***********************************

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
	unsigned char str1[] = "The Data entered will be echoed\r\n";
    unsigned char str2[] = "Data Entered: ";

	IODIR1|=0xFFFE0000;				//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);		
    
    Uart0Init();					// Initialize UART module at 9600 bps
    _DelayMs(100);                  // Wait for UART module to stabilize

    // Following section of code demonstrates transmission of strings 
    // stored in program memory
    Uart0PutS("\r\n\r\n*** ARM7 Dev. Board Uart Demonstration ***\r\n");               
    Uart0PutS("       brought to you by eNTesla...\r\n");
    Uart0PutS("         www.entesla.com\r\n\r\n");
        
    // The Following section of code demonstrates transmission of strings 
    // stored in RAM 
    Uart0PutS(str1);
    Uart0PutS(str2);
    
    while (1) 
    {                     
        Uart0PutCh(Uart0GetCh());        // Echo data on terminal
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
