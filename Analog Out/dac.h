//************************************************************************************
//
//                  dac.h (Header File)
//
//************************************************************************************
//  FileName:           dac.h
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//************************************************************************************
#ifndef DAC_H
#define DAC_H

//**********************User Setting*******************************
// DAC_BIAS Setting:
// 0 The settling time of the DAC is 1 µs max, and the maximum 
// current is 700 µA.
// 1 The settling time of the DAC is 2.5 µs and the maximum 
// current is 350 µA.

#define DAC_BIAS 0 
//*******************End of User Setting***************************

//*******Public Protoype***********************
void DacInit( void );
void DacOut( unsigned int val );
//*****End of Public Protoype//**************

#endif  //  DAC_H
