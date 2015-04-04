#include "header.h"

#define CLOCK (PINC & 0x80)
#define DATA ((PINC & 0x40) >> 6)
#define SET_CLOCK PORTC |= _BV(PC7);
#define CLR_CLOCK PORTC &= ~(_BV(PC7));
#define SET_DATA PORTC |= _BV(PC6);
#define CLR_DATA PORTC &= ~(_BV(PC6));

void initPS2(void){
	PORTC &= 0x3F;
	DDRC &= 0x3F;
}

unsigned char PS2_getc(void){
	unsigned char c = 0, i = 0, parity = 0;
	
	while(CLOCK);
	
	for(i = 0; i<8; i++){
		while(!CLOCK);
	
		while(CLOCK);
	
		c |= (DATA << i);
		if (DATA)
			parity++;
	}
	
	while(!CLOCK);
	while(CLOCK);
	if (DATA == (parity & 0x01))
		c = 0;
	while(!CLOCK);
	while(CLOCK);
	while(!CLOCK);
	
	return c; 
}

int PS2_putc(unsigned char c){
	unsigned char parity=0;
	int i;
	
	for (i=1; i<=128; i*=2){
		if (c & i)
			parity++;
	}
	
	DDRC |= 0xC0;
	
	CLR_CLOCK
	_delay_us(80);
	
	CLR_DATA
	SET_CLOCK
	
	DDRC &= 0x7F;
	
	while(CLOCK);
	
	for(i = 1; i<=128; i*=2){
		if (c & i)
			SET_DATA
		else
			CLR_DATA
			
		while(!CLOCK);
	
		while(CLOCK);
	}
	
	if (parity & 0x01)
		CLR_DATA
	else
		SET_DATA
		
	while(!CLOCK);
	while(CLOCK);
	
	DDRC &= 0x3F;
	
	while(!CLOCK);
	while(CLOCK);
	
	if (DATA)
		return 0;
	else
		return -1;
}
