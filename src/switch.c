#include <util/delay.h>	
#include <avr/io.h>
#include "switch.h"

void switch_init(void){
    PORTC |= 0x20;
    DDRC &= ~0x20;
}

unsigned switch_get_state(void){
    return (~((PINC & 0x20) >> 5) & 0x01);
}

unsigned switch_getc(void){
    unsigned c;
    
    c = switch_get_state();
    
    _delay_us(100);
    
    do{
        if (c != switch_get_state()){
            _delay_us(100);
            if (c != switch_get_state())
                return switch_get_state();
        }
    }while(1);
    
    return 0;
}
