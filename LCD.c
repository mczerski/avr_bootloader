#include "header.h"

volatile unsigned char cursorPos = 0;

void sendNibble(unsigned char n);
void writeLCD(unsigned char n);
void writeCommand(unsigned char n);

void sendNibble(unsigned char n){

	PORTA &= 0xE1;

	PORTA |= (n & 0x01)<<4;
	PORTA |= (n & 0x02)<<2;
	PORTA |= (n & 0x04);
	PORTA |= (n & 0x08)>>2;
}

void writeLCD(unsigned char n){
	SET_E;
	sendNibble(n>>4);
	CLR_E;
	_delay_ms(2);
	SET_E;
	sendNibble(n);
	CLR_E;
	_delay_ms(2);
}

void writeCommand(unsigned char n){
	CLR_RS;
	writeLCD(n);
}

void printCHAR(unsigned char n){
	

	if (cursorPos==16){
		//przejscie do drugiej linii
		writeCommand(0xc0);
	}
	if (cursorPos==32){
		//przejscie na poczatek
		cursorPos=0;
		writeCommand(0x80);
		writeCommand(0x01);//czyszczenie
	}

	SET_RS;
	writeLCD(n);
	cursorPos++;
}


void printSTRING(const unsigned char *txt){
	while(*txt)
		printCHAR(*txt++);

}

void clearLCD(void){
	cursorPos=0;
	writeCommand(0x80);
	writeCommand(0x01);//czyszczenie
}


void initLCD(void){
	char i;

	PORTA &= 0x01;
	DDRA |= 0xFE;
	
	_delay_ms(30);
	
	for(i=0;i<3;i++){
		SET_E;
		sendNibble(0x03);
		CLR_E;
		_delay_ms(5);	
		
	}
	
	SET_E;
	sendNibble(0x02);
	CLR_E;
	_delay_ms(5);


	writeCommand(0x08);//wszystko na off
	writeCommand(0x0F);//lcd, blinking, kursor on
	writeCommand(0x06);//sposob wyswietlania znakow
	writeCommand(0x01);//czyszczenie
	writeCommand(0x02);//cursor home
}

void printHEX(unsigned char c){
	unsigned char a,b;
	a = (c >> 4);
	b = c & 0x0F;
	if(a >= 10)
		printCHAR(a+0x40-9);
	else
		printCHAR(a+0x30);
	
	if(b >= 10)
		printCHAR(b+0x40-9);
	else
		printCHAR(b+0x30);
}

void printDEC(unsigned char c){
	unsigned char out[3],i,flag=0;
	out[2] = c % 10;
	out[1] = (c / 10) % 10;
	out[0] = (c / 100) % 10;
	for(i=0;i<3;i++)
		if(out[i] != 0 || flag != 0){
			printCHAR(out[i]+0x30);
			flag = 1;
		}
}


