//************************************************************************************
//
//                  EEPROM Interface Library (H File)
//
//************************************************************************************
//  FileName:           eeprom.h
//  Dependencies:       None
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 Developemnt Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//************************************************************************************
#ifndef EEPROM_H
#define EEPROM_H

    //*****USER SETTINGS************
    #define EEPROM_ADDR 0xA0
    #define A0          0
    #define A1          0
	#define A2			0
    //***End of USER SETTINGS*******

    //*****Defines******************
    #define READ_MODE   0x01
    #define WRITE_MODE  0x00
    #define SLAVE_ADDR  (((EEPROM_ADDR)|(A0<<1)|(A1<<2)|(A2<<3)))

 
    //*******Public Protoype//*********
    void EepromInit(void);
    unsigned char EepromByteWrite(unsigned char address,unsigned char data);
    unsigned char EepromByteRead(unsigned char address);
    //*****End of Public Protoype//*****

#endif //end EEPROM_H

