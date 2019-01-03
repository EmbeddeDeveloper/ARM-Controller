//************************************************************************************
//
//                  RTC Library (Header File)
//
//************************************************************************************
//  FileName:           rtc.h
//  Compiler:           Keil
//  Target Hardware:    ARM7 Development Board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//	**********************************************************************************
#ifndef RTC_H
#define RTC_H 

//************User Settings*********************
#define SS	0	// Set seconds
#define MN	30	// Set Minutes
#define HH	10	// Set Hour
#define DD	30	// Set Date
#define MM	4	// Set Month
#define YY	2011// Set Year
//********End of User Settings****************

//*******Public Protoype***********************
void RtcInit(void);
void RtcSetTime(void);
//*****End of Public Protoype//**************

#endif  //RTC_H

