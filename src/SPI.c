#include "SPI.h"

#include <avr/io.h>

void initSPI(void) {
    /* Set MOSI and SCK output, all others input */
    DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << PB4);
    DDRB &= 0xBF;
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE);
    CLR_SPI_SS
}

void SPI_putc(unsigned char cData) {
    /* ustaw cpld do odbierania*/
    PORTC &= 0xFE;
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
    /* odlacz cpld*/
    PORTC |= 0x01;
}
