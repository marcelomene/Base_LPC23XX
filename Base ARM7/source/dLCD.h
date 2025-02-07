#ifndef DLCD_H
#define DLCD_H

/* LCD Control Pins */
#define LCD_E  (1 << 24) 
#define LCD_RS (1 << 25) 
#define LCD_D  0xff

/* LCD Commands */
#define CFG_2L_8B 			  0x38 /* Set up LCD to work with 2 lines and 8bit interface */
#define CLEAR_DISPLAY 		0x01 
#define VISIBLE_CURSOR 		0x0e /* Cursor as a underline */
#define SOLID_CURSOR 		  0x0f /* Cursor as a solid block */
#define HIDES_CURSOR 		  0x0c
#define CURSOR_LINE1 		  0x80 /* Sets cursor at line 1 and at x column (send as CURSOR_LINE1 + column) */
#define CURSOR_LINE2 		  0xc0 /* Sets cursor at line 2 and at x column (send as CURSOR_LINE2 + column) */
#define MOVE_CURSOR_LEFT 	0x10 /* Moves cursor 1 character to left */
#define MOVE_CURSOR_RIGHT 0x14 /* Moves cursor 1 character to right */
#define SCROLL_LEFT 		  0x18
#define SCROLL_RIGHT 		  0x1E

/* Functions */
void lcd_putchar(char c);
void lcd_send_command(char c);
void init_lcd(void);
void lcd_puts(char *str);
void lcd_gotoxy(unsigned char l, unsigned char c);
void lcd_clear_screen(void);
void lcd_write(int l, int c, char *str);
#endif
