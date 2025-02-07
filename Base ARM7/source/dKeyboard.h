#ifndef DKEYBOARD_H
#define DKEYBOARD_H

/* IOs */
#define KBDDIR FIO4DIR

/* Keys Masks */
#define KEY0_MASK (1 << 8)  /* P4.8 */
#define KEY1_MASK (1 << 9)  /* P4.9 */
#define KEY2_MASK (1 << 10) /* P4.10 */
#define KEY3_MASK (1 << 11) /* P4.11 */
#define KEY4_MASK (1 << 12) /* P4.12 */

/* Keys Positions in the array */
#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4

/* Number of keys on the keyboard */
#define EXISTING_KEYS 5

/* Keys Enumerator */
typedef enum 
{
	keySW1,
	keySW2,
	keySW3,
	keySW4,
	keySW5,
	keyNoKey
}keyFunction;

/* Functions */
void init_keyboard(void);
keyFunction getKey(void);
void wait_key(keyFunction key);
keyFunction wait_key_press(void);
#endif
