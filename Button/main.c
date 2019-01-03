//******************************************************************************
//
//                    Buzzer and Button Test
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
// The firmware demonstrates change in frequency of the sound from the buzzer on
// interrupt triggered button press of button on P0.16.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 		 Hardware Settings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz							                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//  Jumper Setting:	Set jumper JP8 to connect P0.21 to Buzzer	  
//
//  Switch Setting: None 
//
//	PINOUT:			Buzzer   	-   LPC2148 		Button	-	LPC2148
//					----------------------- 		-------------------
//					NPN-Base    -  	P0.21             S1 		 P0.16
//******************************************************************************

//**************************INCLUDES********************************************
#include  <lpc214x.h>					 
//**********************End of INCLUDES*****************************************
 
//**********************Private Macro Definitions*******************************
#define BUZZ_PIN		(1<<21)			 		//P0.21 as Output to Buzzer 
#define BUZZ_OFF()		IOPIN0	&= ~(BUZZ_PIN);	//Clear the Buzzer pin
#define BUZZ_ON()		IOPIN0 |= BUZZ_PIN;		//Set the Buzzer pin High
//*******************End of Private Macro Definitions***************************

//************************Private Protoype**************************************
void Button1Eint0(void) __irq;			
void _DelayMs(unsigned int count);
void INT0Init(void);
//*******************End of Private Protoype************************************

//***********************Variable Declarations**********************************
unsigned int count=0;
//*******************End of Variable Declarations*******************************

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
int  main(void)
{
	PINSEL1 |= 0x01;  
	PINSEL2 =  0x00000000;

	IODIR0	|=	BUZZ_PIN;			//Select the Buzzer pin as Output
	BUZZ_OFF(); 
	INT0Init();
	
	while(1)	
	{ 
		BUZZ_ON();
		_DelayMs(count);	 		//The count value is updated in the EINT0 ISR
		BUZZ_OFF();
		_DelayMs(count);
				
	}
}

//*****************************************************************************
// Function:        void INT0Init(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        This function setups P0.16 as EINT0.
//
// Note:            None
//*****************************************************************************
void INT0Init(void)		 
{
	PINSEL1	|=	0x01;				// Initialize P0.16 as INT0 		
 	EXTMODE	= 0x01;					// EINT0 is edge sensitive
	EXTPOLAR = 0x00;				// EINT0 in triggered on falling edge (low sensitive)
	
	VICIntSelect = 0x00000000;		// Setting EINT0 as IRQ(Vectored)
	
	VICVectCntl0=0x00000020|14;		// Set as Highest Priority
									// Enable the Vectored IRQ and specify the interrupt
									// number (14 for EINT0)

	VICVectAddr0 = (long)Button1Eint0;	// Storing vector address of EINT0
	EXTINT = 0x00;						// Clearing EINT0 flag	
	VICIntEnable = (1<<14);				// Enable EINT0
}

//*****************************************************************************
// Function:        void Button1Eint0(void) __irq 
//
// Input:           None
//
// Output:          None
//
// Overview:        ISR
//
// Note:            None
//*****************************************************************************
void Button1Eint0(void) __irq 		
{  
	if(count>1000) 
	{
		count=0;
	}
	else
	{
		count+=50;
	}   	
	EXTINT = 0x01;				//Clear EINT0 flag
	VICVectAddr = 0x00;   		//Acknowledge Interrupt
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
