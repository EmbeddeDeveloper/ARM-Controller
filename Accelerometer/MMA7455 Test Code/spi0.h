//************************************************************************************
//
//                  SPI0 Interface Library for LPC21xx (H File)
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
//  WebWarrior          1/03/12        Original
//*************************************************************************************

#define SPI_IODIR      IODIR0
#define SPI_SCK_PIN    4   /* Clock       P0.4  out */
#define SPI_MISO_PIN   5   /* from Slave   P0.5  in  */
#define SPI_MOSI_PIN   6   /* to Slave     P0.6  out */


#define SPI_PINSEL     PINSEL0
#define SPI_SCK_FUNCBIT   8
#define SPI_MISO_FUNCBIT  10
#define SPI_MOSI_FUNCBIT  12


//SPI Register Configuration
#define SPI_SPCR_MSTR			1		
#define	SPI_SPCR_CPHA			0
#define	SPI_SPCR_CPOL			0		
#define	SPI_SPCR_LSBF			0
#define SPI_SPCR_SPIE			0
#define SPI_SPCR_SPIF			1<<7	//just Read for transmission complete

#define SPI_PRESCALE_REG  		S0SPCCR
#define SPI_PRESCALE_MIN  		8

//Function declaration
void Spi0Init(void);
void Spi0Write(unsigned char outgoing);
unsigned char Spi0Read(void);
void Spi0SetSpeed(unsigned char speed);

