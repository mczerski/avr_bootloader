#include "LED.h"
#include "USART.h"
#include "switch.h"
#include "ADC.h"
#include "hex_parser.h"
#include "app.h"

#include <util/delay.h>

int main(void) {
    LED_init();
    USART_init();
    switch_init();
    ADC_init();
    _delay_ms(100);
    LED_SET_D0;
    _delay_ms(100);
    LED_CLR_D0;
    _delay_ms(100);
    LED_SET_D0;
    _delay_ms(100);
    LED_CLR_D0;
    _delay_ms(100);
    unsigned c = switch_get_state();
    if (c) {
        LED_SET_D0;
        USART_puts("BOOT>");
        hex_parser_write_file();
        LED_CLR_D0;
    }
    app_run();
}
