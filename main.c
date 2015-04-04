#include "header.h"
#include "HEXParser.h"

int main(void) {

	//unsigned char numbers[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	//int value; 
//	unsigned char c;
//	int i=1,j=0;

	initLED();
//	initLCD();
	//initPS2();
	initRS();
	//disRSInt();
	initSwitch();
	//initUSB();
//	initSD();
//	initSPI();
	unsigned char c = getSwitchState();
	if (c) {
		SET_RED_D0
		usart_puts("BOOT>");
		readFile();
		CLR_RED_D0
	}
//	while (1) {
		//	if(!CARD_A_DETECT)
		//		SET_RED_D0
		//	else
		//		CLR_RED_D0
//		_delay_ms(500);

//		hex_gets();
//		char c = usart_getc();
//		usart_putc(c);
//		if (c == 'x') {
//			REV_RED_D0
//			usart_putc(XOFF);
//			_delay_ms(500);
//			usart_putc(XON);
//			REV_RED_D0
//		}
//		REV_RED_D0
		//readFile();
//		hex_gets();

		//	usart_putc(XOFF);
		//	_delay_ms(1000);
		//	usart_putc(XON);
		//	REV_RED_D0
		//}
//	}
	typedef void (*AppPtr_t)(void) __attribute__ ((noreturn));
	AppPtr_t AppStartPtr = (AppPtr_t)0x0000;
	AppStartPtr();
}
