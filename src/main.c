#include "LED.h"
#include "USART.h"
#include "switch.h"
#include "hex_parser.h"
#include "app.h"

int main(void) {
    LED_init();
    USART_init();
    switch_init();

    unsigned c = switch_get_state();
    if (c) {
        LED_SET_D0;
        hex_parser_write_file();
        LED_CLR_D0;
    }
    app_run();
}
