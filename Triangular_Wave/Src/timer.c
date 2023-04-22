// @Nitin Flavier  20/04/22
// BASIC TIMER 6
// to get precise delay in micro secs.
// mainly for giving delay w.r.t clock signal

unsigned short *TIM6_CONTROL_REG = (unsigned short *)0x40001000;
unsigned short *TIM6_CONTROL_REG2 = (unsigned short *)0x40001004;
unsigned short *TIM6_INTERRUPT_EN_REG = (unsigned short *)0x4000100C;
unsigned int *TIM6_RCC_APB1_BUS = (unsigned int *)0x40023840;

volatile unsigned short *TIM6_STATUS_REG = (volatile unsigned short *)0x40001010;
volatile unsigned short *TIM6_COUNTER = (volatile unsigned short *)0x40001024;
volatile unsigned short *TIM6_PRESCALER = (volatile unsigned short *)0x40001028;
volatile unsigned short *TIM6_AUTO_RELOAD = (volatile unsigned short *)0x4000102C;

// DEBUGGING
void outportD(unsigned int p) // PD15
{
	volatile unsigned int *GPIOD_ODR = (volatile unsigned int *)0x40020C14;
	*GPIOD_ODR = p;
}

volatile void INIT_TIMER6(unsigned int count)
{
	*TIM6_RCC_APB1_BUS |= 0x10;        // TIM6 Peripheral CLK enabled

	*TIM6_COUNTER = 0;
	//*TIM6_AUTO_RELOAD = 0;             // as reset value is 0xFFFF

	*TIM6_CONTROL_REG |= 0x81;         // ARPE = 1 and CEN = 1
	*TIM6_INTERRUPT_EN_REG |= 0x01;
	*TIM6_CONTROL_REG2 |= 0x10;        // CNT_EN after one clock CEN

	*TIM6_PRESCALER = 0x20;
	*TIM6_AUTO_RELOAD = count -1;

	while(!(*TIM6_STATUS_REG & 0x01));
    *TIM6_STATUS_REG = 0x00;

    *TIM6_CONTROL_REG &= ~(1 << 0);    // disable CEN to OFF TIMER6.
}




