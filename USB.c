#include "header.h"

#define SET_RD PORTD |= (1 << 4)
#define CLR_RD PORTD &= ~(1 << 4)

#define SET_WR PORTD |= (1 << 5)
#define CLR_WR PORTD &= ~(1 << 5)

#define TXE (PIND & 0x40)
#define RXF (PIND & 0x80)

void initUSB(void){

	PORTC = 0x00;	//8-bit palarell data
	PORTD &= 0x1F;	//4-bit handshake
	PORTD |= 0x10;
	DDRD |= 0x30;
	DDRD &= 0x3F;
}

unsigned char USB_getc(void){
	unsigned char c=0;
	DDRC = 0x00;
	
	while(RXF);
	
	CLR_RD;
	asm("NOP");
	c = PINC;
	SET_RD;
	
	//while(!RXF);

	return c;
}

void USB_putc(unsigned char c){
	
	DDRC = 0xFF;
	PORTC = c;
	
	while(TXE);
	
	SET_WR;
	asm("NOP");
	CLR_WR;
	
	while(!TXE);
}

