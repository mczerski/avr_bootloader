#include "header.h"

void initSwitch(void){
	PORTC |= 0x1C;
	DDRC &= 0xE3;
}

unsigned char getSwitchState(void){
	return (~((PINC & 0x1C) >> 2) & 0x07);
}

unsigned char switch_getc(void){
	unsigned char c;
	
	c = getSwitchState();
	
	_delay_us(100);
	
	do{
		if (c != getSwitchState()){
			_delay_us(100);
			if (c != getSwitchState())
				return getSwitchState();
		}
	}while(1);
	
	return 0;
}
