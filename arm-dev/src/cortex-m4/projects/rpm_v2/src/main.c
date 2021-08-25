#include "stm32f4xx.h"
#include "..\include\main.h"

void delayMs(int delay)
{
    int i;
    for( ; delay>0 ; delay--)
    {
        for(i=0; i<3195; i++)
        {
        }
    }
}

uint32_t temp = 0;

int main(void)
{	
	enableLogging();
	configADC();
	configTIM1();
	configTIM2();
	configTIM3();
	configTIM4();	
		
	while(1)
	{
		TIM_SetCompare1(TIM3, ADC_GetConversionValue(ADC1));
		TIM_SetCompare2(TIM3, ADC_GetConversionValue(ADC1));

		print("Motor PPS: TIM1 -> ", getPPS(TIM1_pulses), DEC);
		//print("Motor RPM: TIM2 -> ", getRPM(TIM2_pulses), DEC);

		delayMs(150);
	}
}

uint16_t getPPS(uint16_t pulse_count)
{	
	return (pulse_count * 20);
}

uint32_t get_timer_clock_frequency (TIM_TypeDef *TIMx)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	
	uint32_t multiplier;
	
	if(TIMx == TIM1)
	{
		if (RCC_Clocks.PCLK2_Frequency == RCC_Clocks.SYSCLK_Frequency) 
		{
			multiplier = 1;
		} 
		else 
		{
			multiplier = 2;
		}
		
		return multiplier * RCC_Clocks.PCLK2_Frequency;
	}
	else
	{
		if (RCC_Clocks.PCLK1_Frequency == RCC_Clocks.SYSCLK_Frequency) 
		{
			multiplier = 1;
		} 
		else 
		{
			multiplier = 2;
		}		
		
		return multiplier * RCC_Clocks.PCLK1_Frequency;
	}
}

void configADC(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
  
	//Enable ADC1 and GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	
	//Configure PA.01 (ADC Channel) as analog input 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//ADC Common Init 
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);	

	//ADC3 Init
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	//ADC1 regular channel1 configuration 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);

	//Enable ADC1
	ADC_Cmd(ADC1, ENABLE);
	 
	// Start ADC1 Software Conversion 
	ADC_SoftwareStartConv(ADC1);
}

void configTIM1(void)
{
	//TIM1 clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	
	
	//GPIOA clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//Configure PA.12 as timer 2 External
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_TIM1);
	
	//set everything back to default values 
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	//TIM1 Peripheral Configuration 
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	TIM_SelectInputTrigger(TIM1, TIM_TS_ITR3);
	
	// set external clock mode 2
	TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
	
	//TIM1 counter enable
	TIM_Cmd(TIM1, ENABLE);
	
	//reset counter for TIMER
	TIM_SetCounter(TIM1,0);	
}

void configTIM2(void)
{
	//TIM2 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	
	//GPIOA clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//Configure PA.12 as timer 2 External
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//set everything back to default values 
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	
	//TIM2 Peripheral Configuration 
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR3);
	
	// set external clock mode 2
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
	
	//TIM2 counter enable
	TIM_Cmd(TIM2, ENABLE);
	
	//reset counter for TIMER
	TIM_SetCounter(TIM2,0);		
}

void configTIM3(void)
{
	//GPIOA and GPIOB clock enable 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//TIM3 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	

	//set everything back to default values 
	GPIO_StructInit(&GPIO_InitStructure);
	
	//PA6 and PA7 are set to generate PWM output on channels 1 and 2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	
	
	uint32_t TIMER_Frequency = get_timer_clock_frequency(TIM3);
	uint32_t CNT_Frequency = PWM_Steps * PWM_Frequency;
	uint32_t PrescalerValue = (TIMER_Frequency / CNT_Frequency) - 1;
	uint16_t ARR_Value = PWM_Steps - 1;
		
	//set everything back to default values 
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	//Time base configuration 
	TIM_TimeBaseStructure.TIM_Period = ARR_Value;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//set everything back to default values
	TIM_OCStructInit(&TIM_OCInitStructure);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	//PWM1 Mode configuration: Channel3 and Channel4 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);	

	//TIM3 enable counter 
	TIM_Cmd(TIM3, ENABLE);	
}

/*
	This function configure TIM4 as the Timebase for the measurement of the pulse from the encoder.
	The time is configures to generate an interrupts at intervals of TIMEBASE milliseconds. At the 
	end of each measurement interval the interrupt handler is invked and the measurements of the pulses
	counteed from the encoders from the left and right rear wheel motors are recorder, TIM_GetCounter(TIM1)
	and TIM_GetCounter(TIM2) respecttively. The UG bit is then set which generates the trigger on the TRGO 
	which resets TIM1 and TIM2 thus restarting the measurement cycle.
	
	Details of using a timer as a timebase generator can be found in AN4013 section 2.2
	The update event (UEV) will occur at a rate of 10HZ i.e 10 speed measurements per second 
	
	Update_event = TIM_CLK/((PSC + 1)*(ARR + 1)*(RCR + 1))
*/
void configTIM4(void)
{
	uint16_t TIMEBASE = 9999;	//ARR
	uint16_t UEV = 20;	//UEV frequency (Hz)
	uint32_t PrescalerValue = (get_timer_clock_frequency(TIM4)/((TIMEBASE + 1) * UEV) - 1);
	
	NVIC_Config.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Config); 
	
	//TIM4 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	
	//set everything back to default values 
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	//TIM4 Peripheral Configuration (Time Base configuration)
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIMEBASE;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//Source of update is counter overflow/underflow. 
	TIM_UpdateRequestConfig(TIM4, TIM_UpdateSource_Regular);
	
	//The UG bit in the TIM_EGR register is used as the trigger output(TRGO) 
	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Reset);

	//configure timer in master mode
	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
	
	//Enable TIM4 IRQ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	//TIM4 counter enable
	TIM_Cmd(TIM4, ENABLE);
	
	//reset counter for TIMER
	TIM_SetCounter(TIM4,0);
}

void TIM4_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
	TIM1_pulses = TIM_GetCounter(TIM1);
	TIM2_pulses = TIM_GetCounter(TIM2);
	
	TIM_GenerateEvent(TIM4, TIM_EventSource_Update);	
}
