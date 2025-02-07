/*******************************************
	@file: dKeyboard.c
		5 push-buttons keyboard driver 
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
********************************************/
#include <lpc23xx.h>
#include <stdint.h>
#include "dKeyboard.h"

void init_keyboard()
{
	KBDDIR &= ( ~KEY0_MASK | ~KEY1_MASK | ~KEY2_MASK | ~KEY3_MASK | ~KEY4_MASK);  /* Set the pins as input */
}

void wait_key(keyFunction key)
{
	while(getKey() != key);
}

keyFunction wait_key_press()
{
	keyFunction key = keyNoKey;
	
	while(key == keyNoKey)
		key = getKey();

	return key;
}

void get_keyboard_state(uint8_t *k_vector)
{
	k_vector[0] = !(FIO4PIN & KEY0_MASK);
	k_vector[1] = !(FIO4PIN & KEY1_MASK);
	k_vector[2] = !(FIO4PIN & KEY2_MASK);
	k_vector[3] = !(FIO4PIN & KEY3_MASK);
	k_vector[4] = !(FIO4PIN & KEY4_MASK);
}
keyFunction getKey()
{
	uint8_t k_vector[EXISTING_KEYS];
	uint8_t i;
	keyFunction key;
	
	get_keyboard_state(k_vector); /* k_vector gets the current state of buttons being pressed at the moment. */
	
	for(i = 0; i < EXISTING_KEYS; i++)
	{
			if((k_vector[i]) && (i == KEY_0))
			{
				key = keySW1;
				break;
			}
			else if((k_vector[i]) && (i == KEY_1))
			{				
				key = keySW2;
				break;
			}
			else if((k_vector[i]) && (i == KEY_2))
			{
				key = keySW3;
				break;
			}
			else if((k_vector[i]) && (i == KEY_3))
			{
				key = keySW4;
				break;
			}
			else if((k_vector[i]) && (i == KEY_4))
			{
				key = keySW5;
				break;
			}
			else
				key = keyNoKey;
	}
	return key;
}
