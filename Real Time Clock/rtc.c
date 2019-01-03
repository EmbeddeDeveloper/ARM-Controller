//******************************************************************************
//
//                 	 RTC Library (C File)
//
//******************************************************************************
//  FileName:           main.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
// *****************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
#include "rtc.h"
//**********************End of INCLUDES*****************************************

//*****************************************************************************
// Function:        RtcInit(void) 
//
// Input:           None
//
// Output:          None
//
// Overview:        Rtc Initialization.
//
// Note:            None
//*****************************************************************************
void  RtcInit(void) 
{
	PCONP  |= 0x00000200;   
	CCR     = 0x00000002;
	CIIR    = 0x00000000;
	AMR     = 0x000000FF;
	ILR     = 0x00000003;
	CCR     = 0x00000011;
}
//*****************************************************************************
// Function:        void RtcSetTime(void) 
//
// Input:           None
//
// Output:          None
//
// Overview:        Sets the time to the specified vales.
//
// Note:            None
//*****************************************************************************
void RtcSetTime(void) 
{
	CCR   = 0x00000002;
	YEAR  = YY;
	MONTH = MM;
	DOM   = DD;
	HOUR  = HH;
	MIN   = MN;
	SEC   = SS;
	CCR   = 0x00000011;
}
