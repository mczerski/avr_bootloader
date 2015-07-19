#include "ADC.h"

#include <avr/io.h>

void ADC_init()
{
    uint8_t admux = ADMUX & 0x3F;
    admux |= (1 << REFS0);
    admux |= (1 << REFS1);
    ADMUX = admux;
}

uint16_t ADC_getValue(int channel) {
    uint16_t value;

    uint8_t admux = ADMUX & 0xE0;
    admux |= channel;
    ADMUX = admux;

    ADMUX = admux;
    ADCSRA |= (1 << ADEN) | 6;
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    value = ADCL;
    value += ADCH << 8;

    return value;
}

int ADC_convert2mV(uint16_t v) {
    int voltage_mV = v * 1.1 * 1000 * 10 / 1024; //includes 1/10 divider
    return voltage_mV;
}
