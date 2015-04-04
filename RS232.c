#include "header.h"

//const char XOFF = 19;
//const char XON = 17;

void usart_putc(char c) {
	// wait until UDR ready
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = c;    // send character
}

void usart_puts(char *s) {
	//  loop until *s != NULL
	while (*s) {
		usart_putc(*s);
		s++;
	}
	usart_putc('\n');
	usart_putc('\r');
}

char usart_getc(void) {
	/* Wait for data to be received */
	while (!(UCSRA & (1 << RXC)))
		;
	/* Get and return received data from buffer */
	return UDR;
}

int usart_gets(char *s, int max_len) {
	int read = 0;
	while (read < max_len - 1) {
		*s = usart_getc();
		if (*s == '\n')
			continue;
		if (*s == '\r')
			break;
		s++;
		read++;
	}
	*s = 0;
	return read;
}

void initRS(void) {
	// set baud rate
	UBRRH = (uint8_t) (UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) >> 8);
	UBRRL = (uint8_t) UART_BAUD_CALC(UART_BAUD_RATE, F_OSC);

	// set double speed mode
	UCSRA = (1 << U2X);

	// Enable receiver and transmitter; enable RX interrupt
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	//asynchronous 8N1
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

//void disRSInt(void) {
//	UCSRB &= ~(1 << RXCIE);
//}
//
//void enaRSInt(void) {
//	UCSRB |= (1 << RXCIE);
//}
