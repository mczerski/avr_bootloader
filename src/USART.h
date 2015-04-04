#ifndef USART_H
#define USART_H

//extern const char XOFF;
//extern const char XON;

void USART_putc(char c);
void USART_puts(char *s);
char USART_getc(void);
int USART_gets(char *s, int max_len);
void USART_init(void);

#endif //USART_H
