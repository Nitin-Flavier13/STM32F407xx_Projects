/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Nitin Flavier
 * @brief          : It a seconds counter where TIM2 will give interrupt at every 1 second
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f407xx.h"


__vo uint32_t *APB1_CLK = (__vo uint32_t *)RCC_APB1ENR;
__vo uint32_t *TIM2_CR1_Reg = (__vo uint32_t *)TIM2_CR1;
__vo uint32_t *TIM2_CR2_Reg = (__vo uint32_t *)TIM2_CR2;
__vo uint32_t *TIM2_DIER_Reg = (__vo uint32_t *)TIM2_DIER;
__vo uint32_t *TIM2_SR_Reg = (__vo uint32_t *)TIM2_SR;
__vo uint32_t *TIM2_CNT_Reg = (__vo uint32_t *)TIM2_CNT;
__vo uint32_t *TIM2_PSC_Reg = (__vo uint32_t *)TIM2_PSC;
__vo uint32_t *TIM2_ARR_Reg = (__vo uint32_t *)TIM2_ARR;

__vo uint32_t *SYSCFG_EN = (__vo uint32_t *)RCC_APB2ENR;
__vo uint32_t *NVIC_iser0 = (__vo uint32_t *)NVIC_ISER0;
__vo uint32_t *NVIC_ipr8 = (__vo uint32_t *)NVIC_IPR8;
__vo uint32_t *NVIC_icpr0 = (__vo uint32_t *)NVIC_ICPR0;

void Interrupt_Config(void);
void TIM2_IRQ_Config(uint8_t IRQNumber,uint8_t IRQPriority,uint8_t ED);
int count=0;

int main(void)
{
	Interrupt_Config();

	/* Enabling the TIM2 clock peripheral */
	*APB1_CLK |= 1<<0;

	/* Enabling CEN (counter enable bit) */
	*TIM2_CR1_Reg |= 1<<0;

	/* Enabling ARPE bit */
	*TIM2_CR2_Reg |= 1<<7;

	/* Upcounting */
	*TIM2_CR2_Reg &= ~(1<<4);

	/* UDIS bit is set to zero */
	*TIM2_CR2_Reg &= ~(1<<1);

	/* Update interrupt enable */
	*TIM2_DIER_Reg |= 1<<0;

	/* prescaler as 16 */
	*TIM2_PSC_Reg = 16;

	/* setting auto-reload register */
	*TIM2_ARR_Reg = 0xF4240 - 1;

	while(1)
	{
		/*
		 *  waiting for the interrupt to be called
		 */
	}

}

void Interrupt_Config()
{
	*SYSCFG_EN |= 1<<14;

	TIM2_IRQ_Config(TIM2_IRQNumber,35,ENABLE);
}

void TIM2_IRQ_Config(uint8_t IRQNumber,uint8_t IRQPriority,uint8_t ED)
{
	if(ED == ENABLE)
	{
		*NVIC_iser0 |= 1<<IRQNumber;
		*NVIC_ipr8 |= 7<<((IRQPriority%4)*8);
	}

}

void TIM2_IRQHandler()
{
   count++;
   *TIM2_SR_Reg &= ~(1<<0);
   *NVIC_icpr0 |= 1<<TIM2_IRQNumber;
}
