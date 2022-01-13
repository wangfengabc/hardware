#ifndef SOFTWARE_I2C_H
#define SOFTWARE_I2C_H

#include "port.h"
//#include "hal_mcu.h"
//#include "hal_defs.h"
//#include "hal_types.h"
//#include "hal_led.h"

//typedef unsigned char uint8;

void SoftI2C_start();
void SoftI2C_stop();

void SoftI2C_write_byte(uint8_t value);
uint8_t SoftI2C_read_byte(uint8_t ack);

//extern void GPIO_PortOutSetVal(GPIO_Port_TypeDef port, uint32_t val, uint32_t mask);
#endif
