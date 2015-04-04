#include "header.h"


void initSD(void){
	PORTD = 0x00;
	DDRD = 0x00;
	PORTB &= 0xF3;
	DDRB &= 0xF3;
}
