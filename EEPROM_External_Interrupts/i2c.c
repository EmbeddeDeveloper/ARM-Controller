//************************************************************************************
//
//                  I2C Interface Library (C File)
//
//************************************************************************************
//  FileName:           i2c.c
//  Dependencies:       LPC214x.h
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 Development Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//************************************************************************************

//*******INCLUDES**********************************************************
#include "config.h"
#include "i2c.h"
//****End of INCLUDES******************************************************

//*******Private Protoype//*********
void  __irq I2c0StatIntr(void);
//*****End of Private Protoype//*****

//*******Global variables//*********
unsigned char status=0;
unsigned char statFlag=0;
//*******Global variables//*********


//*****************************************************************************
//  Function:       void  __irq I2c0StatIntr(void);
//
//  Input:          None
//
//  Output:         None
//
//  Overview:       Interrupt call to check the status of I2C bus 
//
//  Note:           None
//****************************************************************************
void  __irq I2c0StatIntr(void)
{ 
  statFlag=0xFF; 				//update status flag
  status=I2C0STAT;				//Read Status byte
  I2C0CONCLR=0x28;				
  VICVectAddr = 0x00;   		//Acknowledge Interrupt
}

//*****************************************************************************
//  Function:       void I2c0Start(void)
//
//  Input:          None
//
//  Output:         None
//					
//  Overview:       A start condition
//
//  Note:           None
//****************************************************************************
void I2c0Start(void)
{
 I2C0CONSET=0x20;				//Set Start condition
}

//*****************************************************************************
//  Function:       void I2c0Stop(void)
//
//  Input:          None
//
//  Output:         None
//
//  Overview:       A stop condition
//
//  Note:           None
//****************************************************************************
void I2c0Stop(void)
{
 I2C0CONSET=0x10;				////Set Stop condition
}

//*****************************************************************************
//  Function:       void I2c0Init(void)
//
//  Input:          None
//
//  Output:         None
//
//  Overview:       Initialize I2C module
//
//  Note:           This function declares I2c0 as IRQ type interrupt with Slot 0(highest
//					priority slot).
//****************************************************************************
void I2c0Init(void)
{
	PINSEL0&=0xFFFFFF0F;		//Set P0.2,P0.3 as SCL,SDA respectively
	PINSEL0|=0x00000050;
	
	I2C0CONCLR=0x6C;
	I2C0CONSET=0x40;
	
	//For 100KHz when XTAL=12MHz,CCLK=60MHz
	//Hence CLK=60/4=15MHz =>I2cbit freq=15MHz/(100+50)=100kHz
	
	I2C0SCLH=100;	// High duty cycle register
	I2C0SCLL=50;	// Low  duty cycle register
	
	//VICIntSelect = 0x00;		// The interrupt request is assigned to the IRQ category.
	VICVectCntl0 = 0x29;			// Assigning Slot 0(highest prority) to I2C0 and enabling this slot
	VICVectAddr0 = (unsigned long)I2c0StatIntr; // Storing vector address of I2C0
	VICIntEnable |= (1<<9);			//Enable the I2c0 interrupt
}

//*****************************************************************************
//  Function:       unsigned char I2c0Write(unsigned char data)
//
//  Input:          Data to be written to the I2C0 bus
//
//  Output:         If write occurs without errors return 0;else return 1
//
//  Overview:       Write data to I2C0 bus and return the status.
//
//  Note:           None
//****************************************************************************
unsigned char I2c0Write(unsigned char data)
{
	I2C0DAT=data;	  
	if(I2c0Status(0x28)==1)	
		return 1;		  	//Data byte in I2DAT has been not been transmitted;
							//or ACK has not been received.
		    
	return (0);				//Data write successful and ACK returned
}


//*****************************************************************************
//  Function:       unsigned char I2c0Read(unsigned char *readBuff)
//
//  Input:          Pass the pointer location where the variable read is to be stored.
//
//  Output:         If read occurs without errors return 0;else return 1
//
//  Overview:       Read data from I2C0 Bus 
//
//  Note:           None
//****************************************************************************
unsigned char I2c0Read(unsigned char *readBuff)
{
   	I2C0CONCLR=0x04;		 //set NACK   
   	if(I2c0Status(0x58)==1)	 
   		return 1;			//Data byte has not been received; 
							//or NOT ACK has been not returned.

	*readBuff=I2C0DAT;		//Store the value read
	return (0);				//Data successfully read and NACK returned
}

//*****************************************************************************
//  Function:       unsigned char I2c0Status(unsigned char statCode)
//
//  Input:          Status code to be checked
//
//  Output:         If error occurs,returns 1; else return 0;
//
//  Overview:       Check the status of the i2C0 bus
//
//  Note:           The status Flag is updated in the interrupt routine.
//****************************************************************************
unsigned char I2c0Status(unsigned char statCode)
{
	while(statFlag==0);
	statFlag=0;
	if(status!=statCode)
		return 1;			//Error occured
	else 
		return 0;			//No error occured	
}

	

