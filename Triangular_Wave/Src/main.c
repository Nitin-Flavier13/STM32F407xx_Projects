/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Nitin Flavier
 * @brief          : Generating triangular wave.
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
#include <stdio.h>

unsigned int *RCC_APB1ENR_BUS = (unsigned int *)0x40023840;
unsigned int *DAC_CONTROL_REG = (unsigned int *)0x40007400;

volatile unsigned int *DAC_SW_TRIGGER = (volatile unsigned int *)0x40007404;
volatile unsigned int *DAC_DHR12R1 = (volatile unsigned int *)0x40007408; // DHRx which will have the 12 bits.
volatile unsigned int *DAC_ANALOG_OUTPUT = (volatile unsigned int *)0x4000742C;

// DEBUGGING
void outportD(unsigned int );
volatile unsigned int *GPIOD_MODER = (volatile unsigned int *)0x40020C00;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;

volatile void INIT_TIMER6(unsigned int );

int main(void)
{
	//*RCC_AHB1ENR |= 0x08;
	*GPIOD_MODER |= 0x55555555;
	/***********DEBUGGING*************/
 /*	while(1)
	{
		outportD(1 << 15);
		INIT_TIMER6(60000);
		outportD(1 << 13);
		INIT_TIMER6(60000);
	}*/
	/*********************************/


    *RCC_APB1ENR_BUS |= (1 << 29);     // enable peripheral clk

    *DAC_CONTROL_REG |= (1 << 0);      // connecting DAC channel to PORT PA4 or PA5

    //*DAC_DHR12R1 = 0x00;

    char flag = 1; // if going up then 1 , for down its 0.
    volatile unsigned int wave = 4;

    while(1)
    {
    	if((wave <= 4092) && (flag == 1))
    	{
    	    wave = wave + 4;
    	    *DAC_DHR12R1 = wave;
    		INIT_TIMER6(800);
    		if(wave >= 4096)
    		   flag = 0;
    	}
    	else if((wave >= 8) && (flag == 0))
    	{
    		wave = wave - 4;
    		*DAC_DHR12R1 = wave;
    		INIT_TIMER6(800);
    		if(wave <= 4)
    		   flag = 1;
    	}

    }
    return 0;
}
