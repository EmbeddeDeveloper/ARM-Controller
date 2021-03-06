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

void Uart0Init (void);
void Uart1Init (void);
void Uart0PutCh (unsigned char ch);
void Uart1PutCh (unsigned char ch);
unsigned char Uart0GetCh (void);
unsigned char Uart1GetCh (void);
void  Uart0PutS(unsigned char *str);
void  Uart1PutS(unsigned char *str);

#endif  //  UART_H
