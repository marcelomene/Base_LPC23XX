/*******************************************
	@file: dLCD.c
			16X2 LCD Driver 
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
********************************************/
#include <lpc23xx.h>
#include <stdint.h>
#include "definitions.h"
#include "sUtils.h"
#include "dLCD.h"

void lcd_gotoxy(uint8_t l, uint8_t c)
{
	#if defined ( LCD_1602 )
		if(l == 0)
			lcd_send_command(CURSOR_LINE1 + c);
	else if(l == 1)
			lcd_send_command(CURSOR_LINE2 + c);
	else
	#endif
	if(l == 1)
		lcd_send_command(CURSOR_LINE1 + c);
	else if(l == 2)
		lcd_send_command(CURSOR_LINE2 + c);
	else
	    return;
}

void lcd_puts(char *str)
{
	uint8_t s_size = 0;
	
	#if defined ( LCD_1602 )
	while(*str != '\0' && s_size < 16)
	#endif
	#if defined ( LCD_2004 )
	while(*str != '\0' && s_size < 20)
	#endif
	{
		lcd_putchar(*str);
		str++;
		s_size++;
	}
}

void lcd_putchar(char c)
{
	FIO3PIN0 = c; /*Writes 'c' in first 8 bits of FIO3 (FIO3PIN0 corresponds to P3.0 to P3.7)*/
	FIO4SET = LCD_RS; /*Indicates that data will be sent to the LCD*/
	FIO4SET = LCD_E; /*Enables LCD data latch*/
	FIO4CLR = LCD_E; /*Unable LCD data latch*/
	wait_ms(8);
}

void lcd_send_command(char c)
{
	FIO3PIN0 = c; /* Writes 'c' in first 8 bits of FIO3 (FIO3PIN0 corresponds to P3.0 to P3.7) */
	FIO4CLR = LCD_RS; /* Indicates that a command will be sent to the LCD */
	FIO4SET = LCD_E; /* Enables LCD data latch */
	FIO4CLR = LCD_E; /* Unable LCD data latch */
	wait_ms(20);
}		 

void lcd_clear_screen()
{
	lcd_send_command(CLEAR_DISPLAY);
}

void lcd_write(int l, int c, char *str)
{
	lcd_gotoxy(l, c);
	lcd_puts(str);
}

void init_lcd(void)
{
	FIO3DIR |= LCD_D; /*First 8 bits of port 3 as output - data bus for the LCD*/
	FIO4DIR |= (LCD_E |LCD_RS); /*LCD Enable pin at P4.24 and Register Selector (RS = 0 - command | RS = 1 - writes data) pin at P4.25, both as output*/
	FIO4CLR = LCD_E; /*LCD_E is normally 0. Must be set to 1 before sending anything.*/
	wait_ms(60);/*Delay to wait LCD power up.*/
	lcd_send_command(CFG_2L_8B);
	lcd_send_command(CLEAR_DISPLAY);
	lcd_send_command(HIDES_CURSOR);
	lcd_send_command(CURSOR_LINE1);
}
