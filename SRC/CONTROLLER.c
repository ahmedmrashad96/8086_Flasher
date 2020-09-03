#include <reg52.h>
#include <stdio.h> 
#include <pins.h> 

char addh,addl,dataw,datar;

void delay(void)
{
   int n=1000;
   for(n=0; n>0; n--)  /* just loop */  ;
}
void UART_Init(int baudrate)
{ 
    SCON = 0x50;  // Asynchronous mode, 8-bit data and 1-stop bit
    TMOD = 0x20;  //Timer1 in Mode2.
    TH1 = 256 - (11059200UL)/(long)(32*12*baudrate); // Load timer value for baudrate generation
    TR1 = 1;      //Turn ON the timer for Baud rate generation
}

void UART_TxChar(char ch)
{
    SBUF = ch;      // Load the data to be transmitted
    while(TI==0);   // Wait till the data is trasmitted
    TI = 0;         //Clear the Tx flag for next cycle.
}

char UART_RxChar(void)
{
    while(RI==0);     // Wait till the data is received
    RI=0;             // Clear Receive Interrupt Flag for next cycle
    return(SBUF);     // return the received char
}

void PrintString(const char* s)
{
  while(*s)
  UART_TxChar(*(s++));
}
void init(void)
{
	Read 	= 1;
	Write = 1;
  Data	= 1;
  Code	= 1;
  led		= 1;
  Switch= 1;

	D0		= 0;	D1		= 0;	D2		= 0;	D3		= 0;	D4		= 0;	D5		= 0;	D6		= 0;	D7		= 0;
	A0		= 0;	A1		= 0;	A2		= 0;	A3		= 0;	A4		= 0;	A5		= 0;	A6		= 0;	A7		= 0;
	A8		= 0;	A9		= 0;	A10		= 0;	A11		= 0;	A12		= 0;	A13		= 0;	A14		= 0;	A15		= 0;
	
	UART_Init(9600);
	
}
void writeCode(char addh,char addl,char dataa)
{
	
	D0		= dataa & 0x01 ;	D1		= dataa & 0x02 ;	D2		= dataa & 0x04 ;	D3		= dataa & 0x08 ;	
	D4		= dataa & 0x10 ;	D5		= dataa & 0x20 ;	D6		= dataa & 0x40 ;	D7		= dataa & 0x80 ;
	
	A0		= addl  & 0x01 ;	A1		= addl  & 0x02 ;	A2		= addl  & 0x04 ;	A3		= addl  & 0x08 ;	
	A4		= addl  & 0x10 ;	A5		= addl  & 0x20 ;	A6		= addl  & 0x40 ;	A7		= addl  & 0x80 ;	
	
	A8		= addh  & 0x01 ;	A9		= addh  & 0x02 ;	A10		= addh  & 0x04 ;	A11		= addh  & 0x08 ;	
	A12		= addh  & 0x10 ;	A13		= addh  & 0x20 ;	A14		= addh  & 0x40 ;	A15		= addh  & 0x80 ;	
	
	Write = 0 ;
	
	Code	= 0 ;
	
	delay()	  ;
	
	Write = 1 ;
}

char readd(char addh,char addl)
{
	char dataa;
	D0		= 1;	D1		= 1;	D2		= 1;	D3		= 1;	D4		= 1;	D5		= 1;	D6		= 1;	D7		= 1;
	
	A0		= addl  & 0x01 ;	A1		= addl  & 0x02 ;	A2		= addl  & 0x04 ;	A3		= addl  & 0x08 ;	
	A4		= addl  & 0x10 ;	A5		= addl  & 0x20 ;	A6		= addl  & 0x40 ;	A7		= addl  & 0x80 ;	
	
	A8		= addh  & 0x01 ;	A9		= addh  & 0x02 ;	A10		= addh  & 0x04 ;	A11		= addh  & 0x08 ;	
	A12		= addh  & 0x10 ;	A13		= addh  & 0x20 ;	A14		= addh  & 0x40 ;	A15		= addh  & 0x80 ;	
	
	Read  = 0 ;
	
	Code	= 0 ;
	
	delay()	  ;
	dataa = (D0 & 0x01 ) & (D1 & 0x02 ) & ( D2 & 0x04 ) & ( D3 & 0x08 )& ( D4 & 0x10 ) & ( D5 & 0x20 ) & ( D6 & 0x40 ) & ( D7& 0x80 ) ;
	delay()	  ;
	Read  = 1 ;
	return dataa; 
}
int main (void)
{
	init();
	
	while(1)
	{
		while (1)
		{
			if (Switch)
			{
				led = led ^1;
				delay();
			}
		addh = UART_RxChar();
		addl = UART_RxChar();
		dataw= UART_RxChar();
		
		writeCode (addh,addl,dataw);
		datar= readd	(addh,addl);
		
		UART_TxChar(datar);
		delay();
		}
	}
	return 0;
}