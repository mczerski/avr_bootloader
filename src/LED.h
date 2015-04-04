#ifndef LED_H
#define LED_H

#define CLR_RED_D0 PORTB |= _BV(PB0);
#define SET_RED_D0 PORTB &= ~(_BV(PB0));
#define REV_RED_D0 PORTB ^= _BV(PB0);

#define CLR_GREEN_D0 PORTB |= _BV(PB1);
#define SET_GREEN_D0 PORTB &= ~(_BV(PB1));
#define REV_GREEN_D0 PORTB ^= _BV(PB1);

#define CLR_RED_D1 PORTB |= _BV(PB2);
#define SET_RED_D1 PORTB &= ~(_BV(PB2));
#define REV_RED_D1 PORTB ^= _BV(PB2);

#define CLR_GREEN_D1 PORTB |= _BV(PB3);
#define SET_GREEN_D1 PORTB &= ~(_BV(PB3));
#define REV_GREEN_D1 PORTB ^= _BV(PB3);

void initLED(void);

#endif
