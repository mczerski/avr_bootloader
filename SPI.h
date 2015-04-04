#ifndef SPI_H
#define SPI_H

#define CLR_SPI_SS PORTB |= _BV(PB4);
#define SET_SPI_SS PORTB &= ~(_BV(PB4));
#define REV_SPI_SS PORTB ^= _BV(PB4);

void initSPI(void);
void SPI_putc(unsigned char cData);

#endif
