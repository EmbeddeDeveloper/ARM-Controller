//************************************************************************************
//
//                  MMASPI.h (Header File)
//
//************************************************************************************
//  FileName:           MMASPI.h
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
// Description: Header file for SPI interface of MMA7455 with LPC2148
//*************************************************************************************
#define SPI_PINSEL     PINSEL0
#define SPI_IODIR      IODIR0

#define SPI_SS_PIN	   		7   // Slave-Select P0.7 - GPIO out 
#define SPI_SS_FUNCBIT    	14

#define SELECT_SLAVE()   	IOCLR0 = (1<<SPI_SS_PIN)
#define UNSELECT_SLAVE()	IOSET0 = (1<<SPI_SS_PIN)

// MMA7455 Register Address
#define  MODCON		0x16	//Mode control register
#define	 XAXIS 		0x06	//8-bit register
#define	 YAXIS 		0x07	//8-bit register
#define	 ZAXIS 		0x08	//8-bit register


// Configuring the Accelerometer
#define  GLEVEL_D		2	// Default 4g
#define	 GLEVEL_8		0	// For 8g
#define	 GLEVEL_4		1	// For 4g
#define	 GLEVEL_2		2	// For 2g
#define	 SPIMODE		0	// 0=4-wire ; 1=3-wire
#define  SELFTEST		0	// 0=Self test disabled ; 1=Enabled

#define  INTDATRDY	1	// 0=DATRDY Interrupt status on INT1 ;
						// 1=DATRDY Interrupt disabled

#define  ACCELMODE	1   // 0=standyby 1=measurement 
						// 2=level detection 3=pulse detection

// Not for User Configuration
#define  GLEVEL         0
//#define  ACCELCONFIG	((GLEVEL<<2)|(SPIMODE<<5)|(SELFTEST<<4)|(INTDATRDY<<6)|(ACCELMODE))


void AccelInit(void);
void AccelWrite(unsigned char addr, unsigned char data);
char AccelRead(unsigned char addr);
void AccelCalib(void);
