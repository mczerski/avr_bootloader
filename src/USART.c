#include "USART.h"

#include <avr/io.h>

const char XOFF = 19;
const char XON = 17;
#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*8l)-1)

void USART_putc(char c) {
    // wait until UDR ready
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;    // send character
}

void USART_puts(char *s) {
    //  loop until *s != NULL
    while (*s) {
        USART_putc(*s);
        s++;
    }
    USART_putc('\r');
    USART_putc('\n');
}

char USART_getc(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

int USART_gets(char *s, int max_len) {
    int read = 0;
    while (read < max_len - 1) {
        *s = USART_getc();
        if (*s == '\r')
            continue;
        if (*s == '\n')
            break;
        s++;
        read++;
    }
    *s = 0;
    return read;
}

void USART_init(void) {
    // set baud rate
    UBRR0H = (uint8_t) (UART_BAUD_CALC(BAUD,F_CPU) >> 8);
    UBRR0L = (uint8_t) UART_BAUD_CALC(BAUD, F_CPU);

    // set double speed mode
    UCSR0A = (1 << U2X0);

    // Enable receiver and transmitter; enable RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    //asynchronous 8N1
//    UCSR0C = (1 << URSEL0) | (3 << UCSZ0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

