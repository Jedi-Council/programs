#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f4xx.h"
#include "logging.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
NVIC_InitTypeDef NVIC_Config;
GPIO_InitTypeDef GPIO_InitStructure;

volatile uint16_t TIM1_pulses = 0;
volatile uint16_t TIM2_pulses = 0;

uint32_t PWM_Frequency = 10000;	//Hz
uint32_t PWM_Steps = 0x0FFF;
uint16_t TimerPeriod = 10000;

uint16_t getPPS(uint16_t pulse_count);
uint32_t get_timer_clock_frequency (TIM_TypeDef *TIMx);

void configADC(void);
void configTIM1(void);
void configTIM2(void);
void configTIM3(void);
void configTIM4(void);

void TIM4_IRQHandler(void);
#endif