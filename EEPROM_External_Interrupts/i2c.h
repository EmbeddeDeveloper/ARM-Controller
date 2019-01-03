//************************************************************************************
//
//                  I2C Interface Library (H File)
//
//************************************************************************************
//  FileName:           i2c.h
//  Dependencies:       None
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 Developemnt Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//************************************************************************************

#ifndef I2C_H
#define I2C_H

//*******Public Protoype//*********
void I2c0Init(void);
void I2c0Start(void);
void I2c0Stop(void);
unsigned char I2c0Write(unsigned char data);
unsigned char I2c0Read(unsigned char *readBuff);
unsigned char I2c0Status(unsigned char statCode);
//*****End of Public Protoype//*****

#endif//I2C_H



