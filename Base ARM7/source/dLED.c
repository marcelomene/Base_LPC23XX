/*******************************************
	@file: dLED.c
		8 LED output driver
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
********************************************/

#include <lpc23xx.h>
#include "dLED.h"
#include <stdint.h>

void init_leds(void)
{
	LEDDIR |= ALL_LEDS; /* Set LEDs IOs as outputs */
	LEDIOSET = ALL_LEDS; /* Turn off all LEDs */
}

void turnOnLedOutput(uint8_t outValue)
{
	LEDIOCLR = outValue;
}

void turnOffLedOutput(uint8_t outValue)
{
	LEDIOSET = outValue;
}

