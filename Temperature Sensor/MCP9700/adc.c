//*************************************************************************
//
//                  A/D Converter Library (C File)
//
//*************************************************************************
//  FileName:           adc.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
// ************************************************************************

//*******INCLUDES**********************************************************
#include "adc.h"
#include "config.h"
//****End of INCLUDES******************************************************

//**********************Private Macro Definitions**************************
#define _PDN_BIT 1<<21 
#define _ADCR_START_MASK 7<<24 
#define _ADCR_SEL_MASK 0x000000FF 
#define _ADC0_START 1<<24 
//*******************End of Private Macro Definitions**********************

//*************************************************************************
// Function:        void Adc0Init(unsigned char clkdiv)
//
// Input:           Clock Divide parameter
//
// Output:          None
//
// Overview:        Initializes the ADC0 Module; Sampling of Analog values  
//					according to clkdiv paramter
//
// Note:            None
//*****************************************************************************
void Adc0Init(unsigned char clkdiv)
{ 
	PCONP |= 0x00001000;                       	  //Power on the A/D converter 0 	
	//configure the A/D control register of A/D 0  
	AD0CR =((unsigned long)(clkdiv+1)<<8 ) | _PDN_BIT ; 
} 

//*****************************************************************************
// Function:        unsigned int Adc0Read(unsigned char channel)
//
// Input:           Channel number
//
// Output:          10-bit Decimal value of the digital equivalent
//
// Overview:        Reads the specified channel and gives an equivalent digital 
//					data.
//
// Note:            None
//***************************************************************************** 
unsigned int Adc0Read(unsigned char channel)
{ 
	static unsigned val;
	AD0CR &= ~(_ADCR_START_MASK|_ADCR_SEL_MASK);  //stop the A/D converter by masking the 
											  	  //start bits and channel selection bit     
	AD0CR |=((unsigned long)(1)<<channel);	 	  //Select the A/D channel
	AD0CR |=_ADC0_START;
	while(!(AD0GDR & (0x80000000)));  			  //Wait for the conversion to get over 
												  //by monitoring the 28th bit of A/D data register
	AD0CR &= ~(_ADCR_START_MASK|_ADCR_SEL_MASK);  //Stop the conversion by masking the start bits

	val = AD0GDR;
	val = ((val>>6 & 0x03FF));					  //Extract A/D result
	return(val);
}
