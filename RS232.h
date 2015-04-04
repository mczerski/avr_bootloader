#ifndef RS_232_H
#define RS_232_H

//extern const char XOFF;
//extern const char XON;

void usart_putc(char c);
void usart_puts(char *s);
char usart_getc(void);
int usart_gets(char *s, int max_len);
void initRS(void);

#endif
