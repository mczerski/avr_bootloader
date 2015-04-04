#include "header.h"

int getADCValue(unsigned char channel){
	//unsigned char DDRA_old = DDRA;
	int value;
	
	ADMUX = channel;
	ADCSRA |= (1<<ADEN)|6;
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1 << ADSC));

	
	value = ADCL;
	value += ADCH << 8;
	
	return value;
}
