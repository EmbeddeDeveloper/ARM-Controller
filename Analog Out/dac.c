//*****************************************************************************
//
//                  DAC Interface Library (C File)
//
//*****************************************************************************
//  FileName:           dac.c
//  Microcontroller:    LPC2148
//  Compiler:           C18
//  Target Hardware:    Arm7 Development Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//*****************************************************************************

//*******INCLUDES**********************************************************
#include "config.h"
#include "dac.h"
//****End of INCLUDES******************************************************

//*****************************************************************************
// Function:        DacInit( void )
//
// Input:           None
//
// Output:          None
//
// Overview:        Main enrty point.
//
// Note:            None
//*****************************************************************************
void DacInit( void )
{
    PINSEL1 |= 0x00080000;	//set P0.25 to DAC output    
}

//*****************************************************************************
// Function:        DacOut( unsigned int val )
//
// Input:           Digital value; min=0;max=1023.
//
// Output:          None
//
// Overview:        Writes the digital value to be converted to 
//					analog in DACR register.
//
// Note:            Initialize the DAC before using this function
//*****************************************************************************
void DacOut( unsigned int val )
{
    DACR = (val << 6) | (DAC_BIAS<<16);    
}
