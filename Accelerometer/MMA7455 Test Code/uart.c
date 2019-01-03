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
void _Itoa(int n, char *s);
void _Reverse(char *s);
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
void Uart0PutCh (int ch)   // Write character to Serial Port   
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
// Overview:        Read a character from serial port
//
// Note:            None
//*****************************************************************************
int Uart0GetCh (void)		// Read character from Serial Port   
{ 
	if (U0LSR & 0x01)
    {
        return (U0RBR);
    }
    else
    {
        return 0;
    }
}
//*****************************************************************************
// Function:        unsigned char Uart0GetChW (void)
//
// Input:           None
//
// Output:          Returns an ascii charcter.
//
// Overview:        wait until a character is received
//
// Note:            None
//*****************************************************************************
int Uart0GetChW (void)		// Read character from Serial Port   
{ 
	while ( (U0LSR & 0x01) == 0 ); //Wait for character
	return U0RBR;
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
void  Uart0PutS(const char *str)	 //A function to send a string on UART0
{ 
	char ch;
	 
	while((ch=*str))
	{  
	  Uart0PutCh(ch);
	  str++;	    
	}
}

//*****************************************************************************
// Function:        void reverse(char *s)
//
// Input:           A string
//
// Output:          None
//
// Overview:        reverse string s in place
//
// Note:            None
//*****************************************************************************
void _Reverse(char *s)
{
    unsigned char i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
 //*****************************************************************************
// Function:        void itoa(int n, char *s)
//
// Input:           An Integer.
//
// Output:          A character string.
//
// Overview:        convert integer n to characters in s.
//
// Note:            None
//***************************************************************************** 
void _Itoa(int n, char *s)
{
    int sign;
    unsigned char i;

    if ((sign = n) < 0)  		// record sign
        n = -n;          		// make n positive
    i = 0;
    do 
	{       					// generate digits in reverse order
        s[i++] = n % 10 + '0';  // get next digit
    } 
	while ((n /= 10) > 0);     	// delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    _Reverse(s);
} 
 //*****************************************************************************
// Function:        void Uart0PutNum(int n)
//
// Input:           An Integer.
//
// Output:          None
//
// Overview:        Dispalays the Integer on the UART.
//
// Note:            None
//***************************************************************************** 
void Uart0PutNum(const int n, const int width)
{
    char str[32];
	int spaces;
	    
    _Itoa(n, str);				//Integer to ascii conversion

    spaces=width-strlen(str);	//determine spaces to be added

	if (spaces < 0)
	{
		spaces = 0;
	}
	while (spaces--)
	{
		Uart0PutCh(' ');	   			//padding with spaces
	}

	Uart0PutS(str);				//print number
}
 //*****************************************************************************
// Function:        void Uart0PutFloat(float f)
//
// Input:           An Float.
//
// Output:          None
//
// Overview:        Dispalays the Float value on the CLCD.
//
// Note:            None
//*****************************************************************************
void Uart0PutFloat(float f)
{
    char str[7]={0};
    char a;
    
    _Itoa((int)f, str);
    Uart0PutS(str);
    Uart0PutCh('.');
    a = ((char)(100*(f - (int)f)));
    if(a<0)
	{
        a = -a;
    }    
    _Itoa(a, str);
    Uart0PutS(str);
}
