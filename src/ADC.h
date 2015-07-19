#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_init(void);
uint16_t ADC_getValue(int);
int ADC_convert2mV(uint16_t);

#endif
