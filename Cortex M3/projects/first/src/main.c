#include "stm32f10x.h"

//Structure to hold configuration for PORTA
GPIO_InitTypeDef PortA_config;

int main(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
			
	while(1){}
}



