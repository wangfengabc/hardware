#ifndef _IO_DEFINE_H_
#define _IO_DEFINE_H_
#include "port.h"

#define TRUE  1
#define FALSE 0

#define VibrateModule   0

#define OPENPOWER()		port_pin_set_output_level(PIN_PA07, 1)
#define CLOSEPOWER()	port_pin_set_output_level(PIN_PA07, 0)

#define LED2_OPEN()		port_pin_set_output_level(PIN_PA24, 1)
#define LED2_CLOSE()	port_pin_set_output_level(PIN_PA24, 0)
#define LED2_TOGGLE()	port_pin_toggle_output_level(PIN_PA24)

#define LED1_OPEN()		port_pin_set_output_level(PIN_PA15, 1)
#define LED1_CLOSE()	port_pin_set_output_level(PIN_PA15, 0)
#define LED1_TOGGLE()	port_pin_toggle_output_level(PIN_PA15)

#endif