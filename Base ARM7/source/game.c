#include <lpc23xx.h>
#include <stdio.h>
#include <type.h>
#include "sUtils.h"
#include "dLCD.h"
#include "dKeyboard.h"
#include "dLED.h"
#include "rtc.h"
#include "fList.h"
#include "definitions.h"

#if SEND_GAME_RESULTS_UART
	#include "uart.h"
#endif

typedef enum 
{
	EASY,
	MEDIUM,
	HARD
} DifficultyLevel;

#if SEND_GAME_RESULTS_UART
typedef struct 
{
	DifficultyLevel *diff;
	int *score;
	uint8_t *roundCount;
} sGameInfo;
#endif

/* Start up */
void init_hardware(void);

/* Game functions */
void greetings(void);
void show_led_warning(void);
void choose_difficulty(DifficultyLevel *difficulty);
void generate_sequence(list_t **listGen, DifficultyLevel *difficulty);
void perform_sequence(list_t *listGen);
int validate_user_input(list_t **listGen, DifficultyLevel *difficulty, int *score);

/* Helper functions */
int get_key_value(keyFunction key);
int get_led(int num);
int get_iterations(DifficultyLevel *difficulty);

/* Uart functions  */
#if SEND_GAME_RESULTS_UART
void UART_SetStandartConfiguration(void);
void UART_SendGameData(sGameInfo *info);
#endif

#define GAME_ALL_LEDS ( LED7_MASK | LED6_MASK | LED5_MASK | LED4_MASK )
#define MAX_ROUNDS 20
#define WAIT_TIME 10000
#define WAIT_TIME_LED 6000

#define WAIT_KEY_RELEASE while(getKey() == keyNoKey)

int main(void)
{
	char str[20];
	int i, score;
	DifficultyLevel difficulty;
	list_t *listGen;
	
	#if SEND_GAME_RESULTS_UART
		uint8_t roundCount = 0;
		sGameInfo gameInfo;
	#endif
	
	init_hardware();	
	greetings();
	show_led_warning();
	choose_difficulty(&difficulty);
	
	lcd_write(0, 0, "Pressione SW1");
	lcd_write(1, 0, "para iniciar");
	wait_key(keySW1);
	
	turnOffLedOutput(GAME_ALL_LEDS);
	
	list_create_empty(&listGen);
	
	while(1)
	{
		lcd_clear_screen();
		
		for(i = 0; i < MAX_ROUNDS; i++)
		{
			lcd_clear_screen();
			lcd_write(0, 0, "Iniciando rodada");
			sprintf(str, "%d...", i+1);
			lcd_write(1, 0, str);
			
			#if SEND_GAME_RESULTS_UART
			roundCount++;
			#endif
			
			wait_ms(WAIT_TIME);
			lcd_clear_screen();
			
			lcd_write(0, 0, "Gerando...");
			generate_sequence(&listGen, &difficulty);
			lcd_clear_screen();
			
			lcd_write(0, 0, "Aguardando");
			lcd_write(1, 0, "entrada...");
			
			if(validate_user_input(&listGen, &difficulty, &score) == 0)
			{
				
				lcd_clear_screen();
				lcd_write(0, 0, "Errou!");
				sprintf(str, "Acertos: %d", score);
				lcd_write(1, 0, str);
				wait_ms(WAIT_TIME);
				
				#if SEND_GAME_RESULTS_UART
				
				gameInfo.diff = &difficulty;
				gameInfo.roundCount = &roundCount;
				gameInfo.score = &score;
				
				UART_SendGameData(&gameInfo);
				
				roundCount = 0;
				#endif
				
				score = 0;
				lcd_clear_screen();
				lcd_write(0, 0, "GG WP");
				lcd_write(1, 0, "Reset p/ iniciar");
				while(1);
			}
		}
	}
}

int get_iterations(DifficultyLevel *difficulty)
{
	int iterations;
	
	if(*difficulty == EASY)
		iterations = 1;
	else if(*difficulty == MEDIUM)	
		iterations = 2;
	else if(*difficulty == HARD)
		iterations = 4;
	
	return iterations;
}

int get_key_value(keyFunction key)
{
	int val;
	
	if(key == keySW1)
		val = 0;
	else if(key == keySW2)
		val = 1;
	else if(key == keySW3)
		val = 2;
	else if(key == keySW4)
		val = 3;
	
	return val;
}

int get_led(int num)
{
	int led;
		switch(num)
	{
		case 0:
			led = LED_7;
			break;
		case 1:
			led = LED_6;
			break;
		case 2:
			led = LED_5;
			break;
		case 3:
			led = LED_4;
			break;
	}
	
	return led;
}

int validate_user_input(list_t **listGen, DifficultyLevel *difficulty, int *score)
{
	int i, iter;
	keyFunction key;
	list_t *aux = *listGen;
	
	iter = list_length(listGen);
	
	for(i = 0; i < iter; i++)
	{
		key = wait_key_press();
		wait_ms(1000);
		while(getKey() != keyNoKey);
		
		if(aux != NULL && aux->data->data == get_key_value(key))
		{
			aux = aux->nxt;
			(*score)++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void perform_sequence(list_t *listGen)
{
	list_t *aux = listGen;
	
	if(listGen == NULL)
		return;
	
	while(aux != NULL)
	{
		turnOnLedOutput(get_led(aux->data->data));
		wait_ms(WAIT_TIME_LED);
		turnOffLedOutput(get_led(aux->data->data));
		wait_ms(WAIT_TIME_LED);
		aux = aux->nxt;
	}
}

void generate_sequence(list_t **listGen, DifficultyLevel *difficulty)
{
	int num, iterations, i;
	
	iterations = get_iterations(difficulty);
	
	//Performe sequence created so far
	perform_sequence(*listGen);
	
	for(i = 0; i < iterations; i++)
	{
		num = generate_random_number(4);
		list_insert_end(listGen, num);
		turnOnLedOutput(get_led(num));
		wait_ms(WAIT_TIME_LED);
		turnOffLedOutput(GAME_ALL_LEDS);
	}
}

void choose_difficulty(DifficultyLevel *difficulty)
{
	keyFunction key = keyNoKey;
	
	lcd_clear_screen();
	lcd_write(0, 0, "Dificuldade");
	lcd_write(1, 0, "1-F | 2-M | 3-D");
	
	while(key == keyNoKey)
		key = getKey();
	
	if(key == keySW1)
		*difficulty = EASY;
	else if(key == keySW2)
		*difficulty = MEDIUM;
	else if(key == keySW3)
		*difficulty = HARD;
	
	lcd_clear_screen();
}
void show_led_warning()
{
	lcd_clear_screen();
	lcd_write(0, 0, "Atencao!");
	lcd_write(1, 0, "Antes de iniciar");
	
	wait_ms(WAIT_TIME);
	lcd_clear_screen();
	
	lcd_write(0, 0, "Somente os LEDs");
	lcd_write(1, 0, "ON serao usados");
	turnOnLedOutput(GAME_ALL_LEDS);
	
	wait_ms(WAIT_TIME);
	lcd_clear_screen();
}

void init_hardware(void)
{
	init_tmr0();
	init_lcd();
	init_keyboard();
	init_leds();
	rtc_init(EXTERNAL_CLK_MODE);
	
	#if SEND_GAME_RESULTS_UART
		UART_Initialize();
		UART_SetStandartConfiguration();
	#endif
}

void greetings()
{
	unsigned char i;
	char v;
	lcd_clear_screen();
	lcd_write(0,0, "ARMGenius 1.0");
	lcd_write(1,0, "Marcelo Menezes");
	
	v = LED_0;
	
	for(i = 0; i < 8; i++)
	{
		turnOnLedOutput(v);
		wait_ms(100);
		v *= 2;
	}
	
	for(i = 0; i < 5; i++)
	{
		turnOnLedOutput(ALL_LEDS);
		wait_ms(500);
		turnOffLedOutput(ALL_LEDS);
		wait_ms(500);
	}
	
	v = LED_7;
	turnOnLedOutput(ALL_LEDS);
	
	for(i = 0; i < 8; i++)
	{
		turnOffLedOutput(v);
		wait_ms(200);
		v /= 2;
	}
	wait_ms(1000);
	lcd_clear_screen();
}

void TargetResetInit(void)
{
}	

#if SEND_GAME_RESULTS_UART
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
#endif

void UART_SendGameData(sGameInfo *info)
{
	uint8_t bytesToSend[6];
	int tempScore;
	
	switch(*(info->diff))
	{
		case EASY:
			bytesToSend[0] = 0;
		break;
		case MEDIUM:
			bytesToSend[0] = 1;
		break;
		case HARD:
			bytesToSend[0] = 2;
		break;
	}
	
	bytesToSend[1] = *(info->roundCount);
	
	
	tempScore = *(info->score);
	
	/* Breaks 32-bit Integer into bytes */
	bytesToSend[2] = (tempScore >> 24) & 0xff;
  bytesToSend[3] = (tempScore >> 16) & 0xff;
  bytesToSend[4] = (tempScore >> 8) & 0xff;
  bytesToSend[5] = tempScore & 0xff;
	
	UART_WriteData(&bytesToSend[0], 6);
}