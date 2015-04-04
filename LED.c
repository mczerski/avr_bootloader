#include "header.h"

void initLED(void){

	PORTB |= 0x0F;
	DDRB |= 0x0F;
}
