//******************************************************************************
//
//                  		Board Demo Code
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
// The firmware demonstrates the basic functionality of LCD 16X2 (CLCD) ,LED
// and Buzzer functionality as a demo code
//**********************Private Macro Definitions*******************************
#define LED1			(1<<18)		//Assign LED1 pin number 
#define LED2			(1<<19)		//Assign LED2 pin number
#define LED3			(1<<20)		//Assign LED3 pin number
#define LED4			(1<<21)		//Assign LED4 pin number
#define LED5			(1<<22)		//Assign LED5 pin number
#define LED6			(1<<23)		//Assign LED6 pin number
#define LED7			(1<<24)		//Assign LED7 pin number
#define LED8			(1<<25)		//Assign LED8 pin number
#define LEDS_ON()		IOPIN1	|=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);//LEDs ON
#define LEDS_OFF()		IOPIN1	&=  ~(LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);//LEDs OFF

#define BUZZ_PIN		(1<<21)			//P0.21 as Output to Buzzer
//*******************End of Private Macro Definitions***************************

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
	
	IODIR0	|=	BUZZ_PIN;		//Select the Buzzer pin as Output
	IOPIN0	&= ~(BUZZ_PIN);		//Clear the Buzzer pin 

	IODIR1 |=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);	//LED pins as output

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

	while (1) 
	{
		IOPIN0 |= BUZZ_PIN;		//Set the Buzzer pin High
        LEDS_ON();		//LEDs ON
        
        _DelayMs(1000);

		LEDS_OFF();		//LEDs OFF
		IOPIN0 &= ~BUZZ_PIN;	//Set the Buzzer pin Low

        _DelayMs(1000);
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
