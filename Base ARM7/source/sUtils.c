/*******************************************
	@file: sUtils.c
			Useful functions
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
********************************************/
#include <lpc23xx.h>
#include <stdint.h>
#include "sUtils.h"
#include "rtc.h"

#define TRUE 1
#define FALSE 0
#define CCLK 12000000

typedef uint8_t BOOL;
BOOL t0_enable = FALSE;

void init_tmr0(void)
{
	PCONP |= 2;	/* (Power up Timer 0) - PCONP register turns on and off the peripherals*/
	PCLKSEL0 = (PCLKSEL0 & (~0x0c)) | 0x04;	/* (Divide CCLK by 1 at T0) - PCKSEL0 register controls the rate of the clock signal in peripherals */
	T0TCR = 0;              /* Disable T0 */
	T0PR = CCLK/1000 - 1; /* Increments T0TC 1000 times per second (1000ms/1s) */
	T0TCR = 2;      /* Initialize T0 */
	T0TCR = 1;      /* Enable T0  */
	t0_enable = TRUE;
}

void wait_ms(uint32_t ms)
{
	if(t0_enable)
	{
		uint32_t tf;
		tf = T0TC + ms;          /* tf = future value of T0TC */
		while(tf != T0TC);      /* wait until tf is equal to T0TC */
	}
	else
	{
		init_tmr0();
		wait_ms(ms);
	}
}

int generate_random_number(unsigned int max)
{
	uint32_t random;
	uint32_t seed = rtc_get_timestamp();

	random = ((seed * 1103515245) + 12345) & 0x7FFFFFFF; https://stackoverflow.com/questions/11715794/understanding-the-rand-operation/
	random %= max; /* Random receives the module of the random divided by the max */
	
	return random;
}
