#include <lpc23xx.h>
#include <stdio.h>
#include <type.h>
#include "sUtils.h"
#include "dLCD.h"
#include "dKeyboard.h"
#include "dLED.h"
#include "uart.h"

#include "irq.h"

void init_hardware(void);
void UART_SetStandartConfiguration();

int main(void)
{
	keyFunction key = keyNoKey;
	char greetings[15];
	int leds;
	int i = 0;
	char *data = "Teste";
	
	init_hardware();
	
	while(key == keyNoKey)
			key = getKey();
	
	if(key == keySW1)
	{
		lcd_puts("Teste SERIAL 0");
		
		UART_SetStandartConfiguration();
		
		while(i < 10)
		{
			//UART_PutChar(0x41);
			UART_WriteData(data,6);
			wait_ms(1000);
			i++
			;
		}
	}
}


void init_hardware()
{
	init_tmr0();
	init_lcd();
	init_keyboard();
	init_leds();
	UART_Initialize();
}

void UART_SetStandartConfiguration()
{
	UART_Parity parity = UART_PARITY_NONE;
	UART_DataBits dataBits = UART_DATA_BITS_8;
	UART_StopBits stopBits = UART_STOP_BITS_1;
	UART_FlowControl flowControl = UART_FLOW_CONTROL_NONE;
	
	UART_Configuration configuration;
	configuration.Baudrate = 9600;
	configuration.DataBits = dataBits;
	configuration.FlowControl = flowControl;
	configuration.Parity = parity;
	configuration.StopBits = stopBits;
	
	UART_SetConfiguration (&configuration);
}
void TargetResetInit(void)
{
}
