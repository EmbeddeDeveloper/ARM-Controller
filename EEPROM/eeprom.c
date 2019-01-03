//************************************************************************************
//
//                  EEPROM Interface Library (C File)
//
//************************************************************************************
//  FileName:           eeprom.c
//  Dependencies:       i2c.h
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 Development Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//************************************************************************************

//*******INCLUDES**********************************************************
#include    "config.h"  //Contains all the header files 
#include    "eeprom.h"                       
//****End of INCLUDES******************************************************

unsigned char readBuff[1]={0};	//call this in main as extern 

//*****************************************************************************
//  Function:       void EepromInit(void)
//
//  Input:          None
//
//  Output:         None
//
//  Overview:       Initialize I2C module
//
//  Note:           In order to change the Bit rate, user needs to edit
//                  BIT_RATE_I2C in i2c.h
//****************************************************************************
void EepromInit(void)
{
    I2c0Init();		//Initialize the I2C0 bus
}
    
//*****************************************************************************
//  Function:       unsigned char EepromByteWrite(unsigned char address, unsigned char data)
//
//  Input:          Address and Data
//
//  Output:         Staus of write
//
//  Overview:       Write a byte of Data at the given Address location
//
//  Note:           None
//****************************************************************************
unsigned char EepromByteWrite(unsigned char address, unsigned char data)
{
	I2c0Start();				// Send Start condition
	if(I2c0Status(0x08)==1)					
		return 1;				// A START condition has not been transmitted.

	I2C0DAT=SLAVE_ADDR;			// Send Slave Address
	if(I2c0Status(0x18)==1)		
		return 1;				// SLA+W has not been transmitted; 
								// or ACK has not been received.

	I2C0DAT=address;			// Send address of the EEPROM Map
	if(I2c0Status(0x28)==1)		
		return 1;				// Data byte in I2DAT has not been transmitted; 
								// or ACK has notbeen received.

	if(I2c0Write(data)==1)		// Write Data to EEPROM location and check write status
	{
		I2c0Stop();
		return 1;				// Data byte in I2DAT has been not been transmitted;
								// or ACK has not been received.
	}
	I2c0Stop();					// Stop I2C0
	return(0);   				// Data Transmitted and ACK recieved 
}
//*****************************************************************************
//  Function:       unsigned char EepromByteRead(unsigned int address)
//
//  Input:          Address
//
//  Output:         Status of read
//
//  Overview:       Read a Byte of Data from the given Address location
//
//  Note:           None
//****************************************************************************
unsigned char EepromByteRead(unsigned char address)
{
	I2c0Start();				//Send Start condition 
	if(I2c0Status(0x08)==1)	
		return 1;				// A START condition has not been transmitted.
			
	I2C0DAT=SLAVE_ADDR;			// Send Slave Address		
	if(I2c0Status(0x18)==1)	
		return 1;				// SLA+W has not been transmitted; 
								// or ACK has not been received.

	I2C0DAT=address;			// Send address of the EEPROM Map
	if(I2c0Status(0x28)==1)		
		return 1;				// Data byte in I2DAT has not been transmitted; 
								// or ACK has notbeen received

	I2c0Start();		    	// Send Repeated Start
	if(I2c0Status(0x10)==1)	
		return 1;				// A repeated START condition has been transmitted.

	I2C0DAT=SLAVE_ADDR | 0x01;	// Send Slave Address with Read condition
	if(I2c0Status(0x40))	
		return 1;				// SLA+R has been transmitted; ACK has been received.

	if(I2c0Read(readBuff)==1)	// Read Data from EEPROM location and check read status
	{
		I2c0Stop();
		return 1;				// Data byte in I2DAT has been not been transmitted;
								// or ACK has not been received.
	}
	I2c0Stop();
	return(0); 					// Data Read and ACK recieved
}
