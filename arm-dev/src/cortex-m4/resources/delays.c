/**
  ******************************************************************************
  * @file    blink/delay.c 
  * @author  Mark R. Jennings
  * @version V1.0
  * @date    31-December-2020
  * @brief   Main program body.
  ******************************************************************************
  */

#include "delays.h"

void SysTick_Handler(void);

__IO uint32_t count_ms;
__IO uint32_t count_us;


void update_delay_us(void);
void update_delay_ms(void);

void SysTick_Handler(void)
{
  update_delay_us();
  update_delay_ms();
}


void delay_ms(__IO uint32_t nTime)
{ 
  count_ms = nTime * 1000;

  while(count_ms != 0);
}

void update_delay_ms(void)
{
  if (count_ms != 0x00)
  { 
    count_ms--;
  }
}


void delay_us(__IO uint32_t nTime)
{ 
  count_us = nTime;

  while(count_us != 0);
}

void update_delay_us(void)
{
  if (count_us != 0x00)
  { 
    count_us--;
  }
}

void configDelays()
{
	SysTick_Config(SystemCoreClock / 1000000);
}