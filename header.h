#ifndef HEADER_H
#define HEADER_H

#define F_OSC F_CPU

#define UART_BAUD_RATE 105200
#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*8l)-1)

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/iom16.h>
#include <math.h>
#include "LED.h"
#include "LCD.h"
#include "PS2.h"
#include "ADC.h"
#include "RS232.h"
#include "switch.h"
#include "USB.h"
#include "SPI.h"
#include "SD.h"

#endif



