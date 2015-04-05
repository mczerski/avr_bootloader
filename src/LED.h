#ifndef LED_H
#define LED_H

#include <avr/io.h>

#define LED_CLR_D0 PORTB &= ~(_BV(PB5))
#define LED_SET_D0 PORTB |= _BV(PB5)
#define LED_REV_D0 PORTB ^= _BV(PB5)

void LED_init(void);

#endif //LED_H
