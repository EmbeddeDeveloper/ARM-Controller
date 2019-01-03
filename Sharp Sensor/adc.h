//************************************************************************************
//
//                  A/D Converter Library (Header File)
//
//************************************************************************************
//  FileName:           adc.h
//  Compiler:           Keil
//  Target Hardware:    ARM7 Development Board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//	**********************************************************************************
#ifndef ADC_H
#define ADC_H 

//*******Public Protoype*********************
void Adc0Init(unsigned char clkdiv); 
unsigned int Adc0Read(unsigned char channel);
//*****End of Public Protoype//**************

#endif  //ADC_H


