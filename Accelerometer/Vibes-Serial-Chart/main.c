//**************************************************************************
//
//           MMA7455 Accelerometer (SPI) + LEDs + SerialChart
//
//**************************************************************************
//  FileName:           main.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil C Compiler
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//
//  Author              Date            Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  WebWarrior          03/07/12        Original
//***************************************************************************
//  Description: The code demonstartes measurement of vibrations in 2g and 4g
//  more using MMA7455 accelerometer. The data is sent over serial and a 
//  waveform is plotted uusing an application like Serial Chart.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Hardware Settings for ARM7 Development Board
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP10 to connect LEDs	  
//
//  Switch Setting: None 
//
//	PINOUT:			LED    -   LPC2148 			MMA7455		-	LPC2148
//					------------------ 			-----------------------
//					LED1   -   	P1.18 			  MOSI		-	P0.6
//					LED2   -   	P1.19 			  MISO		-	P0.5
//					LED3   -   	P1.20			  SCK		-	P0.4
//					LED4   -   	P1.21 			  CS		-	P0.7
//					LED5   -   	P1.22 
//					LED6   -   	P1.23 
//					LED7   -   	P1.24
//					LED8   -	P1.25
//***************************************************************************

//*******INCLUDES************************************************************
#include "config.h"
//*******End of INCLUDES*****************************************************

void _DelayMs(unsigned int count) ;
void levelOnLed(void);
void sendSerial(void);
void INT0Init(void);
void Button1Eint0(void) __irq;

float yRead=0,xRead=0;
float yReadTemp=0,xReadTemp=0;

extern unsigned char gLevel;

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

//*****************************************************************************
// Function:        int main(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main entry Point
//
// Note:            None
//*****************************************************************************
int main(void)
{
	PINSEL1 |= 0x01; 
	PINSEL2 &= 0x0000000C;		
	PINSEL2 |= 0x00000030;
	IODIR1 |=  (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);	//LED pins as output
	INT0Init();
	AccelInit();	//Initialize the Accelerometer
	Uart0Init ();
	ClcdInit();
	ClcdClear();
	ClcdCursorOff();
	LEDS_ON();
	ClcdGoto(1,1);
	ClcdPutS_P("Calibrating...");
	ClcdGoto(1,2);
	ClcdPutS_P(" Do not shake.. ");
	_DelayMs(2500);	//Waiting for the device to stabalize from mechanical vibes
	AccelCalib();	//Calibrate the accelerometer
	LEDS_OFF();	
	ClcdClear();
	ClcdGoto(1,1);
	ClcdPutS_P(" S1 to toggle G");
	while(1)
	{
		xRead=yRead=0;
		ClcdGoto(8,2);
		ClcdPutCh((gLevel*2)+48);
		sendSerial();  //Send data on serial port
		levelOnLed();  //Show level of Y axis using on-board LEDs
	}	 
}

//*****************************************************************************
// Function:        void sendSerial(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Send data over serial
//
// Note:            None
//*****************************************************************************
void sendSerial(void)
{
	//Data is being sent in x,y format
	//Read Data
	yRead=AccelRead(YAXIS);	//Read Y Axis
	xRead=AccelRead(XAXIS);	//Read X Axis

	yRead+=AccelRead(YAXIS);
	yRead=(int)yRead/2.0;
	
	xRead+=AccelRead(XAXIS);
	xRead=(int)xRead/2.0; 

	if((yRead>192 && yRead<255 || yRead>0 && yRead<64) && (xRead>192 && xRead<255 || xRead>0 && xRead<64))
	{
		if (yRead>192)
			yReadTemp=yRead-256;
		else
		    yReadTemp=yRead;
	
		if (xRead>192)
			xReadTemp=xRead-256;
		else
		    xReadTemp=xRead;

		//Dislay Axis data on Serial port 
		Uart0PutNum((int)xReadTemp,4);
		Uart0PutCh(',');
		Uart0PutNum((int)yReadTemp,4);
		Uart0PutCh('\r');			//Carriage return
	}
	else
	{
		//Dislay Axis data on Serial port 
		Uart0PutNum(0,4);
		Uart0PutCh(',');
		Uart0PutNum(0,4);
		Uart0PutCh('\r');			//Carriage return	
	}
}

//*****************************************************************************
// Function:        void levelOnLed(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Send level over LEDs
//
// Note:            None
//*****************************************************************************
void levelOnLed(void)
{
 		//Display Level on LEDs
	 	if(yRead>=215 && yRead<225)
		{
			LEDS_OFF();	
			IOSET1	|= LED8;	
		}
		else if(yRead>=225 && yRead<235)
		{
			LEDS_OFF();
			IOSET1	|= LED7;
		}
		else if(yRead>=235 && yRead<245)
		{
			LEDS_OFF();
			IOSET1	|= LED6;
		}
		else if(yRead>=245 && yRead<253)
		{
			LEDS_OFF();
			IOSET1	|= LED5;
		}
		else if((yRead>=253 && yRead<=255)||(yRead>=0 && yRead<4))
		{
			LEDS_OFF();
			IOSET1	|= LED4;
			IOSET1	|= LED5;
		}
		else if(yRead>=4 && yRead<12)
		{
			LEDS_OFF();
			IOSET1	|= LED4;
		}
		else if(yRead>=13 && yRead<20)
		{
			LEDS_OFF();
			IOSET1	|= LED3;
		}
		else if(yRead>=20 && yRead<30)
		{
			LEDS_OFF();
			IOSET1	|= LED2;
		}
		else if(yRead>=30 && yRead<40)
		{
			LEDS_OFF();
			IOSET1	|= LED1;
		}
		_DelayMs(100);
				 
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
// Overview:        ISR to change G value on button press.
//
// Note:            None
//*****************************************************************************
void Button1Eint0(void) __irq 		
{  
	if(gLevel==1)
	{
		gLevel=2;
	}
	else if(gLevel==2)
	{
		gLevel=1;
	}
	AccelInit();
	EXTINT = 0x01;				//Clear EINT0 flag
	VICVectAddr = 0x00;   		//Acknowledge Interrupt
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
    for (j=0;j<count;j++) {
        for (k=0;k<6000;k++) {
            __asm {
                nop;
                nop;
            }
        }
    }
}
