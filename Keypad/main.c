//******************************************************************************
//
//                       	Keypad Test
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
// The firmware demonstrates keypad scanning and displays the keypressed on the
// terminal.	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for ARM7 development board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP2 to connect RXD0 and TXD0 to RS232-0.	  
//
//  Switch Setting: None 
//
//	PINOUT:			Computer   -   LPC2148 			Keypad	-	LPC2148
//					---------------------- 			-------------------
//					RX		   -    TXD0 			  IP1	-	P1.18
//				    TX         -   	RXD0			  IP2	-	P1.19
//					GND        -    GND				  IP3	-	P1.20
//													  IP4	-	P1.21
//													  OP1	-	P1.22
//													  OP2	-	P1.23
//													  OP3	-	P1.24
//													  OP4	-	P1.25
//*****************************************************************************

//**************************INCLUDES*******************************************
#include "config.h"
//**********************End of INCLUDES****************************************
 
//************************Private Protoype*************************************
void _DelayMs(unsigned int count);
unsigned char _getKey(void);
//*******************End of Private Protoype***********************************


char keys[4][4] = {
  {'a', 'b', 'c', 'd'},	//1,2,3,4
  {'e', 'f', 'g', 'h'},	//5,6,7,8
  {'i', 'j', 'k', 'l'},	//9,10,11,12
  {'m', 'n', 'o', 'p'}	//13,14,15,16
};

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
	unsigned char keyStat[1]={0};

	IODIR1	|=	0x03C00000;				//P1.25 to P1.22 as Output
	IODIR1	&=	~(0x003C0000);			//P1.18 to P1.21 as Input

	ClcdInit();	
	ClcdClear();
	ClcdCursorOff();

	ClcdGoto(1,1);
	ClcdPutS("KeyPad Demo");
	_DelayMs(1000);
	ClcdGoto(1,1);
	ClcdPutS("Entered Key");
	
	while(1)
	{
		*keyStat=_getKey();		
		ClcdGoto(7,2);
		ClcdPutS(keyStat);
		_DelayMs(500);
		ClcdClear();
	}
	
}

//*****************************************************************************
// Function:        unsigned int _getKey(void)
//
// Input:           None
//
// Output:          Key Number
//
// Overview:        Scans for the keypressed
//
// Note:            It is a blocking call!
//*****************************************************************************
unsigned char _getKey(void)
{
	while(1)
	{
		IOPIN1	&=	~0x03C00000;
		IO1PIN |= (0x0F<<22);		//OP1 HIGH
		
		if(((IOPIN1&0x003C0000)>>18) == 0x0E)		
			return(keys[3][0]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0D)	
			return(keys[2][0]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0B)	
			return(keys[1][0]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x07)	
			return(keys[0][0]);

		IOPIN1	&=	~0x03C00000;
		IO1PIN |= (0x0B<<22);		//OP2 HIGH
		
		if(((IOPIN1&0x003C0000)>>18) == 0x0E)		
			return(keys[3][1]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0D)	
			return(keys[2][1]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0B)	
			return(keys[1][1]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x07)	
			return(keys[0][1]);

		IOPIN1	&=	~0x03C00000;
		IO1PIN |= (0x0D<<22);		//OP3 HIGH
		
		if(((IOPIN1&0x003C0000)>>18) == 0x0E)		
			return(keys[3][2]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0D)	
			return(keys[2][2]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0B)	
			return(keys[1][2]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x07)	
			return(keys[0][2]);

		IOPIN1	&=	~0x03C00000;
		IO1PIN |= (0x0E<<22);		//OP4 HIGH
		
		if(((IOPIN1&0x003C0000)>>18) == 0x0E)		
			return(keys[3][3]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0D)	
			return(keys[2][3]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x0B)	
			return(keys[1][3]);
		else if(((IOPIN1&0x003C0000)>>18) == 0x07)	
			return(keys[0][3]);
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
