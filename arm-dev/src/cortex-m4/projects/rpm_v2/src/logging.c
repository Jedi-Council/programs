#include "..\include\logging.h"
#include "..\include\usart.h"

#define TRUE	1
#define FALSE	0

void enableLogging()
{
		configureUsart();
}

void print(char* str, uint32_t data, uint8_t base)
{
	while(*str != '\0')
	{
		char c = str[0];
		USART_SendData(USART1, c);
		
		str++;
			
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};		
	}	
		
	if(base == HEX)
	{		
		char s[] = {'0', 'x', '\0'};
		
		for(int i = 0; i < 3; i++)
		{			
			USART_SendData(USART1, s[i]);

			//wait for TXE bit to be set before passing next character to TDR
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
				
			//wait until last transmission is complete
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};		
		}		
		
		char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		
		uint32_t quotient = 0;
		uint32_t remainder = 0;
		uint32_t divider = 268435456;
		uint8_t leading_zero = TRUE;
		
		do
		{
			quotient = data / divider;
			remainder = data % divider;
			
			if((quotient != 0) || (leading_zero == FALSE))
			{
				leading_zero = FALSE;
								
				USART_SendData(USART1, table[quotient]);
				
				//wait for TXE bit to be set before passing next character to TDR
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
					
				//wait until last transmission is complete
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};
			}
			
			divider /= 16;
			data = remainder;
		}
		while(divider != 1);
		
		USART_SendData(USART1, table[data]);
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};	
		
		USART_SendData(USART1, '\n');
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};

		USART_SendData(USART1, '\r');

		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};			
	}
	
	if(base == DEC)
	{
		char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		
		uint32_t quotient = 0;
		uint32_t remainder = 0;
		uint32_t divider = 1000000000;
		uint8_t leading_zero = TRUE;
		
		do
		{
			quotient = data / divider;
			remainder = data % divider;
			
			if((quotient != 0) || (leading_zero == FALSE))
			{
				leading_zero = FALSE;
								
				USART_SendData(USART1, table[quotient]);
				
				//wait for TXE bit to be set before passing next character to TDR
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
					
				//wait until last transmission is complete
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};
			}
			
			divider /= 10;
			data = remainder;
		}
		while(divider != 1);
		
		USART_SendData(USART1, table[data]);
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};	
		
		USART_SendData(USART1, '\n');
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};

		USART_SendData(USART1, '\r');

		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};			
	}
	
	if(base == BIN)
	{
		char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		
		uint32_t quotient = 0;
		uint32_t remainder = 0;
		uint32_t divider = 2147483648;
		uint8_t leading_zero = TRUE;
		
		do
		{
			quotient = data / divider;
			remainder = data % divider;
			
			if((quotient != 0) || (leading_zero == FALSE))
			{
				leading_zero = FALSE;
								
				USART_SendData(USART1, table[quotient]);
				
				//wait for TXE bit to be set before passing next character to TDR
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
					
				//wait until last transmission is complete
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};
			}
			
			divider /= 2;
			data = remainder;
		}
		while(divider != 1);
		
		USART_SendData(USART1, table[data]);
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};	
		
		USART_SendData(USART1, '\n');
		
		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};

		USART_SendData(USART1, '\r');

		//wait for TXE bit to be set before passing next character to TDR
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){};
			
		//wait until last transmission is complete
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};			
	}
}
