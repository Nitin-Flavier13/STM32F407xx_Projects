/*
 * stm32f407xx.h
 *
 *  Created on: Aug 9, 2022
 *      Author: Nitin Flavier
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_

#define __vo volatile

/*
 *  Base addresses of flash and SRAM memories
 */
#define FLASH_BASE_ADDR                 0x08000000U
#define SRAM1_BASE_ADDR                 0x20000000U
#define SRAM2_BASE_ADDR                 0x2001C000U
#define ROM_BASE_ADDR                   0x1FFF0000U        /* System memory */
#define SRAM                            SRAM1_BASE_ADDR


/*
 *  Base addresses of different bus domains.
 */
#define APB1_BASE_ADDR                  0x40000000U
#define APB2_BASE_ADDR                  0x40010000U
#define AHB1_BASE_ADDR                  0x40020000U
#define AHB2_BASE_ADDR                  0x50000000U

/*
 *  Base addresses of Peripherals
 */
#define TIM2_CR1                        (APB1_BASE_ADDR + 0x00U)
#define TIM2_CR2                        (APB1_BASE_ADDR + 0x04U)
#define TIM2_DIER                       (APB1_BASE_ADDR + 0x0CU)
#define TIM2_SR                         (APB1_BASE_ADDR + 0x10U)
#define TIM2_CNT                        (APB1_BASE_ADDR + 0x24U)
#define TIM2_PSC                        (APB1_BASE_ADDR + 0x28U)
#define TIM2_ARR                        (APB1_BASE_ADDR + 0x2CU)

#define RCC_BASE_ADDR                   0x40023800U
#define RCC_APB1ENR                     (RCC_BASE_ADDR + 0x40U)
#define RCC_APB2ENR                     (RCC_BASE_ADDR + 0x44U)
#define RCC_AHB1ENR                     (RCC_BASE_ADDR + 0x30U)
#define RCC_AHB2ENR                     (RCC_BASE_ADDR + 0x34U)

/*
 *   Interrupt Configuration
 */
#define TIM2_IRQNumber                  28

/*
 *   NVIC registers
 *   ISER is interrupt set enable register
 */
#define NVIC_ISER0                      0xE000E100  /* Enabling Interrupt on NVIC side */
#define NVIC_ISER1                      0xE000E104

#define NVIC_IPR0                       0xE000E400
#define NVIC_IPR8                       NVIC_IPR0 + 0x10 /* setting priority for TIM2 */

#define NVIC_ICPR0                      0XE000E280  /* to clear the pending bit after interrupt */

#define ENABLE     1
#define DISABLE    0

/*
 *  Structure definitions for different registers
 */

typedef struct
{
   __vo uint32_t CR;
   __vo uint32_t PLLCFGR;
   __vo uint32_t CFGR;
   __vo uint32_t CIR;
   __vo uint32_t AHB1RSTR;
   __vo uint32_t AHB2RSTR;
   __vo uint32_t AHB3RSTR;
   uint32_t RESERVED0;
   __vo uint32_t APB1RSTR;
   __vo uint32_t APB2RSTR;
   uint32_t RESERVED1[2];
   __vo uint32_t AHB1ENR;
   __vo uint32_t AHB2ENR;
   __vo uint32_t AHB3ENR;
   uint32_t RESERVED2;
   __vo uint32_t APB1ENR;
   __vo uint32_t APB2ENR;
   uint32_t RESERVED3[2];
   __vo uint32_t AHB1LPENR;
   __vo uint32_t AHB2LPENR;
   __vo uint32_t AHB3LPENR;
   __vo uint32_t RESERVED4;
   __vo uint32_t APB1LPENR;
   __vo uint32_t APB2LPENR;
   uint32_t RESERVED5[2];
   __vo uint32_t BDCR;
   __vo uint32_t CSR;
   uint32_t RESERVED6[2];
   __vo uint32_t SSCGR;
   __vo uint32_t PLLI2SCFGR;
   __vo uint32_t PLLSAICFGR;
   __vo uint32_t DCKCFGR;

}RCC_RegDef_t;

#endif /* STM32F407XX_H_ */
