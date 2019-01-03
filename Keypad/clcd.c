//************************************************************************************
//
//                  LCD 16X2 (CLCD) Interface Library (C File)
//
//************************************************************************************
//  FileName:           clcd.c
//  Microcontroller:    LPC2148
//  Compiler:           Keil
//  Target Hardware:    ARM7 development board
//  Company:            ENTESLA
//  website:            www.entesla.com
//  email:              feedbackATenteslaDOTcom
// ***********************************************************************************

//*******INCLUDES**********************************************************
#include    "clcd.h"
#include 	"string.h"
#include    "config.h"
//****End of INCLUDES******************************************************
 
//**********************Private Macro Definitions*****************************
#define _SET_RS()           CTRL_PORT_SET |= ((unsigned long)(1)<<CTRL_RS) 
#define _SET_EN()           CTRL_PORT_SET |= ((unsigned long)(1)<<CTRL_EN)          
#define _CLEAR_RS()         CTRL_PORT_CLR |= ((unsigned long)(1)<<CTRL_RS)
#define _CLEAR_EN()         CTRL_PORT_CLR |= ((unsigned long)(1)<<CTRL_EN)
#define _EnToggle()         {_SET_EN();__asm{nop;nop;}_CLEAR_EN();}
#define _TYPE_CMD            0
#define _TYPE_DATA           1
//*******************End of Private Macro Definitions*************************

//****Variable Declarations***************************************************
volatile unsigned char uSDelay;
//****End of Variable Declarations********************************************

//*******Private Protoype***************************************************
void _Itoa(int n, char *s);
void _Reverse(char *s);
void _ClcdDelayMs(unsigned int delay);
void _ClcdDelay45Us(void);
//*****End of Private Protoype//**********************************************


//*****************************************************************************
// Function:        void ClcdInit(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        CLCD initialization.
//
// Note:            None
//*****************************************************************************
void ClcdInit(void) 
{
    DATA_DIR |= (unsigned long)(DATA_PORT);		//initialize D4:D7 pins as output
    CTRL_DIR |= ((unsigned long)(1)<<CTRL_RS);	//initialize RS pins as output
    CTRL_DIR |= ((unsigned long)(1)<<CTRL_EN);	//initialize EN pins as output   
    _CLEAR_EN();                             	//clear EN
    _CLEAR_RS();                             	//clear RS
    _ClcdDelayMs(300);
    ClcdSendByte(0X03,0);       //Configure bus width as 8-bit
    _ClcdDelayMs(50);
    ClcdSendByte(0X02,0);       //Configure bus width as 4-bit, 1 line,5X7 dots
    _ClcdDelayMs(50);
    ClcdSendByte(0X28,0);       //Configure bus width as 4-bit, 2 line,5X7 dots
    _ClcdDelayMs(50);
    ClcdSendByte(0X10,0);       //Cursor move and Shift to left
    _ClcdDelayMs(1);
    ClcdSendByte(0x0D,0);       // DisplayOn,CursorOff
    _ClcdDelayMs(1);
    ClcdSendByte(0x06,0);       // EntryMode,Automatic Increment - No Display shift.
    _ClcdDelayMs(1);   
    ClcdSendByte(0x01,0);       //Clear Display and set address DDRAM with 0X00 
    _ClcdDelayMs(5);
}

//*****************************************************************************
// Function:        void ClcdSendByte(unsigned char byte,unsigned char type)
//
// Input:           A character byte and Type of Byte (command or data)
//
// Output:          None
//
// Overview:        Send a command or a data byte to the CLCD.
//
// Note:            None
//*****************************************************************************
void ClcdSendByte(unsigned char byte,unsigned char type)
{
    _CLEAR_EN();
    if(type==_TYPE_DATA)
	{
        _SET_RS();      // Selects data Register for read / write   
    }    
    else if(type==_TYPE_CMD)
	{
        _CLEAR_RS();    // Selects cmd  Register for write
    }    
    
	_ClcdDelay45Us();

    DATA_PORT_CLR |= DATA_PORT;		//Clear Data Port
    DATA_PORT_SET |= ((((unsigned long)byte >> 4) & 0x0F)<<D4);//Send byte to Data port   
	_EnToggle(); 
	_ClcdDelay45Us();  
	
    DATA_PORT_CLR |= DATA_PORT;		//Clear Data Port
    DATA_PORT_SET |= (((unsigned long)byte & 0x0F)<<D4);		//Send byte to Data port   
	_EnToggle();                                
	_ClcdDelay45Us();                             

}

//*****************************************************************************
// Function:        void ClcdPutS(void *str)
//
// Input:           A character string.
//
// Output:          None
//
// Overview:        Takes a string as input and displays it on the LCD
//
// Note:            Declare an array of type char in the calling function.
//                    Declaration example: char msg0[8]="ENTESLA";
//					Usage example: ClcdPutS(msg0);
//*****************************************************************************
void ClcdPutS(void *str)
{ 
    unsigned char	*str1 = (unsigned char*) str;
    while(*str1)							//Check for valid character  
	{              			  
        ClcdSendByte(*str1++,_TYPE_DATA); 	//Send out the current byte pointed to
    } 
}

//*****************************************************************************
// Function:        void ClcdPutS_P(const rom char *str)
//
// Input:           A character string.
//
// Output:          None
//
// Overview:        Takes a string as input and displays it on the LCD
//
// Note:            example: ClcdPutS_P("ENTESLA");
//*****************************************************************************
void ClcdPutS_P(const char *str)
{ 
    while(*str)							//Check for valid character    
	{                 		  
        ClcdSendByte(*str++,_TYPE_DATA);//Send out the current byte pointed to
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
// Function:        void LcdPutNum(int n)
//
// Input:           An Integer.
//
// Output:          None
//
// Overview:        Dispalays the Integer on the CLCD.
//
// Note:            None
//***************************************************************************** 
void ClcdPutNum(int n)
{
    char str[7];
    
    _Itoa(n, str);
    ClcdPutS(str);
}
 //*****************************************************************************
// Function:        void LcdPutFloat(float f)
//
// Input:           An Float.
//
// Output:          None
//
// Overview:        Dispalays the Float value on the CLCD.
//
// Note:            None
//*****************************************************************************
void ClcdPutFloat(float f)
{
    char str[7]={0};
    char a;
    
    _Itoa((int)f, str);
    ClcdPutS(str);
    ClcdPutCh('.');
    a = ((char)(100*(f - (int)f)));
    if(a<0)
	{
        a = -a;
    }    
    _Itoa(a, str);
    ClcdPutS(str);
}

//*****************************************************************************
// Function:        void ClcdGoto(unsigned char x,unsigned char y)
//
// Input:           X and Y co-ordinate.
//
// Output:          None
//
// Overview:        Moves the cursor to a position defined by x and y
//
// Note:            x = 1 to 16 for 16 column LCD.
//					y = 1 to 2 for 2 line LCD.
//*****************************************************************************
void ClcdGoto(unsigned char x,unsigned char y)
{
    switch(y)	
	{
        case 1:
            // position for line 1
            y=0x80 ;
            break;
            
        case 2:
            // position for line 2
            y=0xC0 ;
            break;
            
        case 3:
            // position for line 3
            y=0x94 ;
            break;
            
        case 4:
             // position for line 4
            y=0xD4 ;
            break;
            
        default:
            break;           
    }
    ClcdSendByte((x-1+y),_TYPE_CMD);	
}

//*****************************************************************************
// Function:        void ClcdClear()
//
// Input:           None
//
// Output:          None
//
// Overview:        Clears the CLCD screen.
//
// Note:            None
//*****************************************************************************
void ClcdClear()
{
    ClcdSendByte(0x01,_TYPE_CMD);    //Clear Display and set address DDRAM with 0X00 
    _ClcdDelayMs(2);                // delay after sending clear command
}

//*****************************************************************************
// Function:        void _ClcdDelayMs(unsigned int delay)
//
// Input:           Delay in milliseconds
//
// Output:          None
//
// Overview:        Generates a delay of specified number of milliseconds.
//
// Note:            Calibrated for 12MHz crystal
//*****************************************************************************
void _ClcdDelayMs(unsigned int count)
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
// Function:        void _ClcdDelay45Us(void)
//
// Input:           None
//
// Output:          None
//
// Overview:        A 45 microseconds delay
//
// Note:            Calibrated for 12MHz crystal
//*****************************************************************************
void _ClcdDelay45Us(void) 
{
	volatile unsigned int k;
	for(k=0;k<409;k++)
	{
            __asm 
			{
                nop;
            }
	}
} 
