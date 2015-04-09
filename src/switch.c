#include <util/delay.h>	
#include <avr/io.h>
#include "switch.h"

void switch_init(void) {
    MCUCR &= ~_BV(PUD);
    DDRD &= ~_BV(PD6);
    PORTD = _BV(PD6);
}

unsigned switch_get_state(void) {
    return ~((PIND & _BV(PD6)) >> 6) & 0x1;
}

unsigned switch_getc(void) {
    unsigned c;

    c = switch_get_state();

    _delay_us(100);

    do {
        if (c != switch_get_state()) {
            _delay_us(100);
            if (c != switch_get_state())
                return switch_get_state();
        }
    } while (1);

    return 0;
}
