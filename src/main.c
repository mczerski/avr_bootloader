#include "header.h"

int main(void) {

    LED_init();
    USART_init();
    switch_init();
//    init_SPI();
    unsigned char c = switch_get_state();
    if (c) {
        LED_SET_D0
        USART_puts("BOOT>");
        hex_parser_write_file();
        LED_CLR_D0
    }
}
