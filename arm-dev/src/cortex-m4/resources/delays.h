/**
  ******************************************************************************
  * @file    blink\delays.h 
  * @author  Mark R. Jennings
  * @version V1.0
  * @date    01-January-2021
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAYS_H
#define __DELAYS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

void configDelays();

void delay_ms(__IO uint32_t nTime);
void delay_us(__IO uint32_t nTime);

#endif /* __DELAYS_H */

