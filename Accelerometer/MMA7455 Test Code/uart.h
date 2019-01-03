//************************************************************************************
//
//                  uart.h (Header File)
//
//************************************************************************************
//  FileName:           uart.h
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
//************************************************************************************
#ifndef UART_H
#define UART_H

//*******Public Protoype***********************
void Uart0Init (void);
int Uart0GetCh (void);
int Uart0GetChW (void);
void Uart0PutCh (int ch);
void  Uart0PutS(const char *str);
void Uart0PutFloat(float f);
void Uart0PutNum(const int n, const int width);
//*****End of Public Protoype//**************

#endif  //  UART_H
