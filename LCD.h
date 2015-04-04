#ifndef LCD_H
#define LCD_H

#define RS PA7
#define RW PA6
#define E PA5

#define SET_E PORTA |= (1 << E)
#define CLR_E PORTA &= ~(1 << E)

#define SET_RS PORTA |= (1 << RS)
#define CLR_RS PORTA &= ~(1 << RS)

void printCHAR(unsigned char n);
void printSTRING(const unsigned char *txt);
void clearLCD(void);
void initLCD(void);
void printHEX(unsigned char c);
void printDEC(unsigned char c);

#endif
