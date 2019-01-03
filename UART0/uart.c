//*****************************************************************************
//
//                  UART Interface Library (C File)
//
//*****************************************************************************
//  FileName:           uart.c
//  Microcontroller:    LPC2148
//  Compiler:           C18
//  Target Hardware:    Arm7 Development Board
//  Company:            ENTESLA
//  Website:            www.entesla.com
//  Email:              feedbackATenteslaDOTcom
//*****************************************************************************

//**************************INCLUDES*******************************************
#include "config.h"
//**********************End of INCLUDES****************************************

//*****************************************************************************
// Function:        void Uart0Init (void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Initiaize UART0
//
// Note:            None
//*****************************************************************************
void Uart0Init (void)			    // Initialize Serial Interface       
{               	   
  	PINSEL0 |= 0x00000005;           //Enable RxD0 and TxD0                    
    U0LCR = 0x83;                   // 8 bits, no Parity, 1 Stop bit            
    U0DLL = 97;                     // 9600 Baud Rate @ 15MHz VPB Clock         
    U0LCR = 0x03; 					// DLAB = 0  
}

//*****************************************************************************
// Function:        void Uart0PutCh (unsigned char ch)
//
// Input:           An ascii character to be transmitted
//
// Output:          None
//
// Overview:        Transmits an ascii character to be transmitted
//
// Note:            None
//*****************************************************************************
void Uart0PutCh (unsigned char ch)   // Write character to Serial Port   
{                  		
   while (!(U0LSR & 0x20));
  	U0THR = ch;
}

//*****************************************************************************
// Function:        unsigned char Uart0GetCh (void)
//
// Input:           None
//
// Output:          Returns an ascii charcter.
//
// Overview:        Recieves an ascii character.
//
// Note:            None
//*****************************************************************************
unsigned char Uart0GetCh (void)		// Read character from Serial Port   
{            
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

//*****************************************************************************
// Function:        void  Uart0PutS(unsigned char *str)
//
// Input:           A string
//
// Output:          None
//
// Overview:        Transmits a string of ascii characters.
//
// Note:            None
//*****************************************************************************
void  Uart0PutS(unsigned char *str)	 //A function to send a string on UART0
{  
   while(*str)
   {  
      Uart0PutCh(*str++);	    
   }
}

//*****************************************************************************
// Function:        void Uart1Init (void)
//
// Input:           None
//
// Output:          None
//
// Overview:        Initiaize UART1
//
// Note:            None
//*****************************************************************************
void Uart1Init (void)			    // Initialize Serial Interface       
{               	   
  	PINSEL0 |= 0x00050000;           //Enable RxD1 and TxD1                     
    U1LCR = 0x83;                   // 8 bits, no Parity, 1 Stop bit            
    U1DLL = 97;                     // 9600 Baud Rate @ 15MHz VPB Clock         
    U1LCR = 0x03; 					// DLAB = 0  

}

//*****************************************************************************
// Function:        void Uart1PutCh (unsigned char ch)
//
// Input:           An ascii character to be transmitted
//
// Output:          None
//
// Overview:        Transmits an ascii character to be transmitted
//
// Note:            None
//*****************************************************************************
void Uart1PutCh (unsigned char ch)   // Write character to Serial Port   
{                  		
   	U1THR = ch;
	while (!(U1LSR & 0x20));
}

//*****************************************************************************
// Function:        unsigned char Uart1GetCh (void)
//
// Input:           None
//
// Output:          Returns an ascii charcter.
//
// Overview:        Recieves an ascii character.
//
// Note:            None
//*****************************************************************************
unsigned char Uart1GetCh (void)		// Read character from Serial Port   
{            
  while (!(U1LSR & 0x01));
  return (U1RBR);
}

//*****************************************************************************
// Function:        void  Uart1PutS(unsigned char *str)
//
// Input:           A string
//
// Output:          None
//
// Overview:        Transmits a string of ascii characters.
//
// Note:            None
//*****************************************************************************
void  Uart1PutS(unsigned char *str)	 //A function to send a string on UART1
{  
   while(*str)
   {  
      Uart1PutCh(*str++);	    
   }
}
