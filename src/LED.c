#include <avr/io.h>
#include "LED.h"

void LED_init(void){
    PORTB |= 0x20;
    DDRB |= 0x20;
}
