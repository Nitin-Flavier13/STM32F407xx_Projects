/*
 * main.c
 *
 *  Created on: 02-Jun-2022
 *      Author: Nitin Flavier
 */


#include <stdint.h>
#include "stm32f4xx.h"

void GPIO_Config(void );

void DAC_GPIO_Config(void );
void DAC_Init(void);
void DAC_Conv(uint16_t );
void delay_ms(uint32_t );

int main(void)
{
	
    GPIO_Config();
    DAC_Init();          // Initialize it
    DAC_GPIO_Config();   // PA4

    while(1)
    {
    	DAC_Conv(0x0FFF);
    	delay_ms(4000);
    	DAC_Conv(0x0BFD);
    	delay_ms(4000);
    	DAC_Conv(0x03FF);
    	delay_ms(4000);
    	DAC_Conv(0x0000);
    	delay_ms(4000);
    }

	return 0;

}


void DAC_Conv(uint16_t data)
{
	DAC1->DHR12R1 = data;
	volatile unsigned int delay = 1000;
	while(delay--);
}


void DAC_Init(void)
{
	RCC->APB1ENR |= 1<<29;         //Enable DAC clk
	DAC1->CR |= (1<<0);            // Enable DAC channel 1
	unsigned int d=10000;          // Output Buffer disable;
	while(d--);
}


void DAC_GPIO_Config(void)
{
	RCC->AHB1ENR |= 1<<0;  // enable GPIOA clk
	GPIOA->MODER |= 3<<8;  // Analog mode PA4
	GPIOA->PUPDR |= 2<<8;  // pull down
}

void delay_ms(uint32_t n)
{
	volatile uint32_t j;
	for(j = 0;j < (2000*n); j++);
}

void GPIO_Config(void)
{
	// LED PD13 just to Blink if an Error occurs
	RCC->AHB1ENR |= 1<<3;
	GPIOD->MODER |= 1<<30;
	GPIOD->PUPDR |= 1<<31;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;
}




