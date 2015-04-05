#include "LED.h"

void LED_init(void){
    PORTB &= ~_BV(PB5);
    DDRB |= _BV(PB5);
}
