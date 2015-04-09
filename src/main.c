#include <util/delay.h>
#include "header.h"

void blink() {
    while (1) {
        USART_puts("BOOT>");
        LED_REV_D0;
        _delay_ms(200);
    }
}

int main(void) {

    LED_init();
    USART_init();
    switch_init();
    unsigned c = switch_get_state();
    if (c) {
        LED_SET_D0;
        USART_puts("BOOT>");
        hex_parser_write_file();
        LED_CLR_D0;
    }
    app_run();
}
