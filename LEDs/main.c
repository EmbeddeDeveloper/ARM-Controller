//******************************************************************************
//
//                  LED Test on ARM7 Development Board
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
// The firmware demonstrates the basic blinking LED experiment. All the LEDs 
// on-board blink at an interval of 1 second. 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for ARM7 Development Board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP10 to connect LEDs	  
//
//  Switch Setting: None 
//
//	PINOUT:			LED    -   LPC2148 
//					------------------ 
//					LED1   -   	P1.18 
//					LED2   -   	P1.19 
//					LED3   -   	P1.20
//					LED4   -   	P1.21 
//					LED5   -   	P1.22 
//					LED6   -   	P1.23 
//					LED7   -   	P1.24
//					LED8   -	P1.25
//***************************************************************************

//**************************INCLUDES********************************************
#include <LPC214x.h>
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define LED1			(1<<18)		//Assign LED1 pin number 
#define LED2			(1<<19)		//Assign LED2 pin number
#define LED3			(1<<20)		//Assign LED3 pin number
#define LED4			(1<<21)		//Assign LED4 pin number
#define LED5			(1<<22)		//Assign LED5 pin number
#define LED6			(1<<23)		//Assign LED6 pin number
#define LED7			(1<<24)		//Assign LED7 pin number
#define LED8			(1<<25)		//Assign LED8 pin number
#define LEDS_ON()		IOSET1	|=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);//LEDs ON
#define LEDS_OFF()		IOCLR1	|=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);//LEDs OFF
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
int main (void) 
{
	PINSEL2 &= 0x0000000C;		
	PINSEL2 |= 0x00000030; 

	IODIR1 |=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);	//LED pins as output
	
    while (1) 
	{
        LEDS_ON();		//LEDs ON
        
        _DelayMs(1000);

		LEDS_OFF();		//LEDs OFF

        _DelayMs(1000);
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
void _DelayMs(unsigned int count) {
    volatile unsigned int j,k;
    for (j=0;j<count;j++) {
        for (k=0;k<6000;k++) {
            __asm {
                nop;
                nop;
            }
        }
    }
}
