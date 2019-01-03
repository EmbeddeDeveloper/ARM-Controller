//************************************************************************************
//
//                  SPI0 Interface Library for LPC21xx (C File)
//
//************************************************************************************
//  FileName:           spi0.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil C
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//
//  Author              Date            Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  WebWarrior          19/04/11        Original
//*************************************************************************************

//*******INCLUDES**********************************************************
#include    "spi0.h"
#include    "config.h"
//****End of INCLUDES******************************************************

//******************************************************************
//  Function:       void SpiInit(void)
//
//  Input:          None.
//
//  Output:         None.
//
//  Overview:       Initializes the SPI0 port.
//
//  Note:           None
//*******************************************************************
void Spi0Init(void)
{
	// setup GPIO
	SPI_IODIR |= (1<<SPI_SCK_PIN)|(1<<SPI_MOSI_PIN);
	SPI_IODIR &= ~(1<<SPI_MISO_PIN);
	
	// Set pclk to same as cclk 
	//VPBDIV=0x1;   //DANGER!!			

 	// set Chip-Select high - unselect slave
	UNSELECT_SLAVE();

	// reset Pin-Functions	
	SPI_PINSEL &= ~( (3<<SPI_SCK_FUNCBIT) | (3<<SPI_MISO_FUNCBIT) |
		(3<<SPI_MOSI_FUNCBIT) | (3<<SPI_SS_FUNCBIT) );

	SPI_PINSEL |= ( (1<<SPI_SCK_FUNCBIT) | (1<<SPI_MISO_FUNCBIT) |
		(1<<SPI_MOSI_FUNCBIT) );

 	//  SPI configuration:
	//  Master mode
	//  Sample on 1st edge of SCK
	//  SCK is active high
	//  MSB out first
	//  No interrupts

	S0SPCR = (SPI_SPCR_MSTR<<5) | (SPI_SPCR_CPHA<<3) | (SPI_SPCR_CPOL<<4) | (SPI_SPCR_LSBF<<6) | (SPI_SPCR_SPIE<<7);

	// low speed during init
	Spi0SetSpeed(24); 
}

//******************************************************************
//  Function:       void Spi0Write(unsigned char outgoing)
//
//  Input:          Byte to write.
//
//  Output:         incoming byte.
//
//  Overview:       Initializes the SPI0 port.
//
//  Note:           None
//*******************************************************************
void Spi0Write(unsigned char outgoing)
{
	S0SPDR = outgoing;
	//Wait for transmission complete
	while( !(S0SPSR & SPI_SPCR_SPIF) ) ; 
}

//******************************************************************
//  Function:       unsigned char Spi0Read(unsigned char outgoing)
//
//  Input:          Byte to write.
//
//  Output:         incoming byte.
//
//  Overview:       Initializes the SPI0 port.
//
//  Note:           None
//*******************************************************************
unsigned char Spi0Read(void)
{
	S0SPDR = 0x00;	//Dummy Write
	//Wait for transmission complete
	while( !(S0SPSR & SPI_SPCR_SPIF) ) ; 
	return(S0SPDR);
}

//******************************************************************
//  Function:       void Spi0SetSpeed(unsigned char speed)
//
//  Input:          Set Clock rate of SPI interface.
//
//  Output:         None.
//
//  Overview:       Sets the speed based greater than or equal to the 
//					set minimum speed.
//
//  Note:           None
//*******************************************************************
void Spi0SetSpeed(unsigned char speed)
{
	speed &= 0xFE;
	if ( speed < SPI_PRESCALE_MIN  ) speed = SPI_PRESCALE_MIN ;
	SPI_PRESCALE_REG = speed;
}



