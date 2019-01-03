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
//					DB7   -   	P0.20 			Buttons  -  LPC2148
//					RS    -   	P0.12 			-------------------
//					E     -   	P0.13 			   S1	 -	P0.16 (EINT0)
//					R/W   -   	GND				   S2	 -	P0.15 (EINT2)
//******************************************************************************

//**************************INCLUDES********************************************
#include <LPC214x.H>                       
#include "config.h"
//**********************End of INCLUDES*****************************************

//***********************Private Prototypes*************************************
void Button1Eint0(void) __irq;
void Button2Eint2(void) __irq;			
void _DelayMs(unsigned int count);
void Int0Init(void);
void Int2Init(void);
void Write2Eep(void);
//********************End of Private Prototypes*********************************

//**************************Extern Variables************************************
extern unsigned char readBuff[1]; 
//***********************End of Extern Variables********************************

unsigned int count=0,countlcd=0,counteep=0,countFlag=0;

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
	IODIR1|=0xFFFE0000;				//Clear all the LEDs on board
	IOPIN1&=~(0xFFFF0000);  

    //Initialization of CLCD
    ClcdInit();
    ClcdCursorOff();
	ClcdClear();
    //Display Demo Information
	ClcdGoto(1,1);
    ClcdPutS(" EXT Interrupts ");
    ClcdGoto(1,2);
    ClcdPutS(" EEP Rd/Wr Demo ");
    _DelayMs(2000);
    ClcdClear(); //clear display
   
	Int0Init();					//Initialize Button interrupt for S1
	Int2Init();					//Initialize Button interrupt for S2


    //Initialization of EEPROM and I2C
    EepromInit();

	ClcdGoto(1,1);           			// goto line 1
    ClcdPutS("WR data to EEP");     	// display astatus
	ClcdGoto(1,2);
	Write2Eep(); 	 					//Write "eNTesla" to EEP and display on CLCD

    _DelayMs(2000);

	//Display Demo Information
	ClcdGoto(1,1);
    ClcdPutS("S1-incr EEP Addr");	    //Press S1 to increment EEP read address
    ClcdGoto(1,2);
    ClcdPutS("S2-read from EEP");		//Press S2 to read from EEP address
    _DelayMs(3000);
    ClcdClear(); //clear display

	ClcdGoto(1,1);           			// goto line 1
	ClcdPutS("EEP Addr: ");     			
	ClcdGoto(10,1); 
	ClcdPutNum(count);					//Display count status

	//Int0Init();
	//Int2Init();
    while(1)
	{
		if(countFlag==1)
		{	
			ClcdGoto(10,1); 		//Cursor position
			ClcdPutNum(count);	//Displaying the count value
			countFlag=0;  		//Ensuring the interupt data is processed first
		}
		else
		{
		
		}
		
		if(counteep==1)
		{
			counteep=0;
			EepromByteRead(count);	
			ClcdGoto(1,2);         				// goto line 2
	    	ClcdPutS("Data Read: ");      		// display data read

			if(readBuff[0]==255)
				ClcdPutS("0xFF");
			else
			{
 	    		ClcdPutCh((unsigned int)readBuff[0]);
				ClcdPutS("   ");
			}
		}
		else
		{

		}
	_DelayMs(150);
	}
}

//*****************************************************************************
// Function:        void Write2Eep(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        ISR
//
// Note:            None
//*****************************************************************************
void Write2Eep(void)
{
	if(EepromByteWrite(1,'e')==1)			  //EEP address '1'
		ClcdPutCh(' ');
	else
		ClcdPutCh('e');

	_DelayMs(25);

	if(EepromByteWrite(2,'N')==1)			  //EEP address '2'
		ClcdPutCh(' ');
	else
		ClcdPutCh('N');

	_DelayMs(25);

	if(EepromByteWrite(3,'T')==1)			  //EEP address '3'
		ClcdPutCh(' ');
	else
		ClcdPutCh('T');

	_DelayMs(25);

	if(EepromByteWrite(4,'e')==1)			  //EEP address '4'
		ClcdPutCh(' ');
	else
		ClcdPutCh('e');

	_DelayMs(25);

	if(EepromByteWrite(5,'s')==1)			  //EEP address '5'
		ClcdPutCh(' ');
	else
		ClcdPutCh('s');

	_DelayMs(25);

	if(EepromByteWrite(6,'l')==1)			  //EEP address '6'
		ClcdPutCh(' ');
	else
		ClcdPutCh('l');

	_DelayMs(25);

	if(EepromByteWrite(7,'a')==1)			  //EEP address '7'
		ClcdPutCh(' ');
	else
		ClcdPutCh('a');
}

//*****************************************************************************
// Function:        void Int0Init(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        This function setups P0.16 as EINT0.
//
// Note:            None
//*****************************************************************************
void Int0Init(void)		 
{
	PINSEL1	|=	0x01;				// Initialize P0.16 as EINT0 		
 	EXTMODE	|= 0x01;					// EINT0 is edge sensitive
	EXTPOLAR |= 0x00;				// EINT0 in triggered on falling edge (low sensitive)
	
	//VICIntSelect |= (1<<14);		// Setting EINT0 as IRQ(Vectored)
	
	VICVectCntl1=0x00000020|14;		// Set as Highest Priority
									// Enable the Vectored IRQ and specify the interrupt
									// number (14 for EINT0)

	VICVectAddr1 = (long)Button1Eint0;	// Storing vector address of EINT0
	EXTINT |= 0x01;						// Clearing EINT0 flag	
	VICIntEnable |= (1<<14);			// Enable EINT0
}

//*****************************************************************************
// Function:        void Int2Init(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        This function setups P0.16 as EINT0.
//
// Note:            None
//*****************************************************************************
void Int2Init(void)		 
{
	PINSEL0	|=	0x80000000;			// Initialize P0.15 as EINT2 		
 	EXTMODE	|= 0x04;					// EINT2 is edge sensitive
	EXTPOLAR |= 0x00;				// EINT0 in triggered on falling edge (low sensitive)
	
	//VICIntSelect |= (1<<14);		// Setting EINT0 as IRQ(Vectored)
	
	VICVectCntl2=0x00000020|16;		// Set as Highest Priority
									// Enable the Vectored IRQ and specify the interrupt
									// number (14 for EINT2)

	VICVectAddr2 = (long)Button2Eint2;	// Storing vector address of EINT0
	EXTINT |= 0x04;						// Clearing EINT0 flag	
	VICIntEnable |= (1<<16);			// Enable EINT2
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
	if(countFlag==0)
	{  
		count++;
   		countFlag=1;
	}
	EXTINT |= 0x01;				//Clear EINT0 flag
	VICVectAddr = 0x01;   		//Acknowledge Interrupt
}
//*****************************************************************************
// Function:        void Button2Eint2(void) __irq 
//
// Input:           None
//
// Output:          None
//
// Overview:        ISR
//
// Note:            None
//*****************************************************************************
void Button2Eint2(void) __irq 		
{ 	
	counteep=1;					 //Read from EEPROM  
	
	EXTINT |= 0x04;				//Clear EINT0 flag
	VICVectAddr = 0x02;   		//Acknowledge Interrupt
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
