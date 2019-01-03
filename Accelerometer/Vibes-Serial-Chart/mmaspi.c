//************************************************************************************
//
//                  MMASPI.c (Header File)
//
//************************************************************************************
//  FileName:           MMASPI.c
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//
//  Author              Date            Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  WebWarrior          30/06/12        Original
//*************************************************************************************
#include "mmaspi.h"
#include "config.h"

unsigned char gLevel=1;		// Global variable. Update this variable with 
							// GLEVEL_2,GLEVEL_4,GLEVEL_8 as required. 
							// If not defined, a gLevel of 8g is taken by default.

void _AccelDelayMs(unsigned int count);

//*****************************************************************************
// Function:        void AccelInit(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Initialize Accelerometer
//
// Note:            None
//*****************************************************************************
void AccelInit(void)
{
	unsigned char accelConfig=0;
	Spi0Init();							//Initialize SPI0
	SPI_IODIR |= (1<<SPI_SS_PIN);		//Initialize chip select
	SPI_PINSEL &= ~(3<<SPI_SS_FUNCBIT);
	//gLevel=0;
	accelConfig = (gLevel<<2)|(SPIMODE<<5)|(SELFTEST<<4)|(INTDATRDY<<6)|(ACCELMODE);
	AccelWrite(MODCON,accelConfig);		//Setup the accelerometer in 4-wire SPI mode
	//AccelWrite(MODCON,ACCELCONFIG);	
}

//*****************************************************************************
// Function:        void AccelWrite(unsigned char addr, unsigned char data)
//
// Input:           Address and Data
//
// Output:          None
//
// Overview:        Writes data to MMA7155
//
// Note:            None
//*****************************************************************************
void AccelWrite(unsigned char addr, unsigned char data)
{
	SELECT_SLAVE();
	Spi0Write(((addr&0x3F)|0x40)<<1);	//|W|ADDRESS|D/C| 
	Spi0Write(data);					//Write Data Byte	
	UNSELECT_SLAVE();
}	
//*****************************************************************************
// Function:        char AccelRead(unsigned char addr)
//
// Input:           Address
//
// Output:          None
//
// Overview:        Read data from address
//
// Note:            None
//*****************************************************************************
char AccelRead(unsigned char addr)
{
	unsigned char incoming;
	SELECT_SLAVE();
	Spi0Write((addr&0x3F)<<1);	//|R|ADDRESS|D/C|
	incoming=Spi0Read();
	UNSELECT_SLAVE();	
	return(incoming);		
}

//*****************************************************************************
// Function:        void AccelCalib(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Calibrates the readings by calculating the offset and writing
//					the offset values in the offset register of MMA7155
//
// Note:            Place the Device on a flat surface such that the X and the Y 
//					axis are parallel to the surface.
//*****************************************************************************
void AccelCalib(void)
{
	signed char x, y, z;
	float xoff=0, yoff=0, zoff=0, xoffd, yoffd, zoffd;

	do 
	{
		x = AccelRead(XAXIS);
		y = AccelRead(YAXIS);
		z = AccelRead(ZAXIS);
		xoffd = -2.1*(x);
		yoffd = -2.1*(y);
		zoffd = 2.1*(64-z);
		xoff += xoffd;
		yoff += yoffd;
		zoff += zoffd;
		AccelWrite(0x10, 0xFF&(char)xoff);
		AccelWrite(0x11, 0xFF&((char)xoff>>8));
		AccelWrite(0x12, 0xFF&(char)yoff);
		AccelWrite(0x13, 0xFF&((char)yoff>>8));
		AccelWrite(0x14, 0xFF&(char)zoff);
		AccelWrite(0x15, 0xFF&((char)zoff>>8));
		_AccelDelayMs(10);
	} 
	while ((xoffd) > 2.0 || (yoffd) > 2.0 || (zoffd) > 2.0);
}


//*****************************************************************************
// Function:        void _AccelDelayMs(unsigned int count) 
//
// Input:           Delay in milliseconds
//
// Output:          None
//
// Overview:        Generates a delay of specified number of milliseconds.
//
// Note:            None
//*****************************************************************************
void _AccelDelayMs(unsigned int count) 
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
