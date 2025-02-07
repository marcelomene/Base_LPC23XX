#ifndef DLED_H
#define DLED_H

#include <stdint.h>

/* IOs */
#define LEDDIR FIO4DIR
#define LEDIOSET FIO4SET
#define LEDIOCLR FIO4CLR

/* Leds Masks */
#define LED0_MASK (1 << 0) /* P4.0 */
#define LED1_MASK (1 << 1) /* P4.1 */
#define LED2_MASK (1 << 2) /* P4.2 */
#define LED3_MASK (1 << 3) /* P4.3 */
#define LED4_MASK (1 << 4) /* P4.4 */
#define LED5_MASK (1 << 5) /* P4.5 */
#define LED6_MASK (1 << 6) /* P4.6 */
#define LED7_MASK (1 << 7) /* P4.7 */
#define ALL_LEDS ( LED0_MASK | LED1_MASK | LED2_MASK | LED3_MASK | LED4_MASK | LED5_MASK | LED6_MASK | LED7_MASK )

/* Leds Values */
#define LED_0 0x01
#define LED_1 0x02
#define LED_2 0x04
#define LED_3 0x08
#define LED_4 0x10
#define LED_5 0x20
#define LED_6 0x40
#define LED_7 0x80

/* Functions */
void init_leds(void);
void turnOnLedOutput(uint8_t outValue);
void turnOffLedOutput(uint8_t outValue);
#endif
