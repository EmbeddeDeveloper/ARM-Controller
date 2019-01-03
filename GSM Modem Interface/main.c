//******************************************************************************
//
//                  GSM Modem Interface to ARM7 Development Board
//
//******************************************************************************
// FileName:        main.c
// Microcontroller: LPC2148
// Compiler:        Keil
// Target Hardware: ARM7 Development Board
// Company:         ENTESLA
//******************************************************************************
//                          Description                     
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The firmware demonstrates SMS delivery system and Calling using a GSM Modem   
// connected to RS232-1 port of ARM7 Development Board.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                			 Hardware Settings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Microcontroller:LPC2148
//  Ext.Oscillator:	12 MHz
//  Jumper Setting:	Set jumper JP1 to connect RXD1 and TXD1 to RS232-1	  
//
//  Switch Setting: None 
//
//	PINOUT:			GSM Modem  -   ARM7 Dev Brd(RS232) 
//					--------------------------------- 
//					 	Rx			TXD1
//						Tx 			RXD1
//						GND			GND
//******************************************************************************

//**************************INCLUDES********************************************
#include "config.h"
//**********************End of INCLUDES***************************************** 

//************************Private Protoype**************************************
void _DelayMs(unsigned int);
unsigned char GsmSendMsg(unsigned char *msgStr);
void _DelayMs(unsigned int count);
//*******************End of Private Protoype************************************

//***********************Variable Declarations**********************************
unsigned char usrNumStr[20]="\"xxxxxxxxxx\"";	//Receiptent Mobile Number
//*******************End of Variable Declarations******************************

//*****************************************************************************
// Function:        int main(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Main enrty point.
//
// Note:            None
//*****************************************************************************
int main(void)
{
	IODIR1|=0xFFFF0000;			//Turn Off the LEDs on board
	IOPIN1&=~(0xFFFF0000);
	
    Uart1Init();
    ClcdInit();
    ClcdCursorOff();

    ClcdPutS(" ARM7 Dev. Board");
    ClcdGoto(1,2);
    ClcdPutS("    GSM Demo    ");
    _DelayMs(2000);
    ClcdClear();
    ClcdPutS("Initializing GSM");
    ClcdGoto(1,2);
    ClcdPutS("Modem");
	_DelayMs(15000);
    //  Echo off
    Uart1PutS("ATE0\r");
    _DelayMs(500);
   
	ClcdClear();
	Uart1PutS("ATDxxxxxxxxxx;\r");		  //replace xxxxxxxxxx with number to call
	ClcdGoto(1,1);
    ClcdPutS("Calling...  ");
    //For getting sms length during sms read      
//    Uart1PutS("AT+CSDH=1\r");
//    _DelayMs(500);
//
//    ClcdClear();
//    ClcdPutS("Sending msg to:");
//    ClcdGoto(1,2);
//    ClcdPutS(usrNumStr);
//    GsmSendMsg("Message from Entesla's ARM7 Dev. board");
//    ClcdGoto(1,1);
//    ClcdPutS("Msg sent to:    ");
    
	while(1);

}

//*****************************************************************************
// Function:        void _DelayMs(unsigned int count)
//
// Input:           Delay in milliseconds
//
// Output:          None
//
// Overview:        Generates a delay of specified number of milliseconds.
//
// Note:            None
//*****************************************************************************
void _DelayMs(unsigned int count) 
{
    volatile unsigned int j,k;
    for (j=0;j<count;j++) 
	{
        for (k=0;k<6000;k++) 
		{
            __asm 
			{
                nop;
                nop;
            }
        }
    }
}


//*****************************************************************************
// Function:        unsigned char GsmSendMsg(unsigned char *msgStr)
//
// Input:           A string
//
// Output:          None
//
// Overview:        Message to be transmitted with prefixes.
//
// Note:            None
//*****************************************************************************
unsigned char GsmSendMsg(unsigned char *msgStr)
{
    Uart1PutS("AT+CMGS=");
    Uart1PutS(usrNumStr);
    Uart1PutCh('\r');
    _DelayMs(100);  // timepass
    Uart1PutS(msgStr);
    _DelayMs(100);  // timepass
    Uart1PutCh(0x1A);
    _DelayMs(3000);  // timepass
    return (1);
}

