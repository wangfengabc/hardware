#ifndef SOFTWARE_I2C_C
#define SOFTWARE_I2C_C

#include "SoftwareI2C.h"
#include "io_define.h"

//#define PIN_SCL_SET(x)     port_pin_set_output_level(PIN_PA17,x);
//#define PIN_SDA_SET(x)     port_pin_set_output_level(PIN_PA16,x);

#define SCL_OUTPUT(x)		port_pin_set_output_level(PIN_PA17,x)
#define PIN_SDA_GET()      (port_pin_get_input_level(PIN_PA16))

#define SDA_OUTPUT(x)  GPIO_Pinout(x)
#define SDA_INPUT(x)   GPIO_PinModeSet(x)

#define DelayTick 30


void GPIO_Pinout(uint8_t val)
{
	struct port_config pin_conf;
	
	port_get_config_defaults(&pin_conf);
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA16, &pin_conf);
	
	port_pin_set_output_level(PIN_PA16,val);	
}


void GPIO_PinModeSet(uint8_t val)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
		
	//pin_conf.direction=PORT_PIN_DIR_INPUT;
	//pin_conf.input_pull = SYSTEM_PINMUX_PIN_PULL_DOWN;

	port_pin_set_config(PIN_PA16, &pin_conf);	
}


void SoftI2C_delay(uint8_t i)
{
    while(i--);
}

void SoftI2C_stop()
{
    SCL_OUTPUT(1);
    SoftI2C_delay(DelayTick);
    SDA_OUTPUT(1);
    SoftI2C_delay(DelayTick);
}
void SoftI2C_start()
{
    SCL_OUTPUT(1);
    SDA_OUTPUT(1);
    SoftI2C_delay(DelayTick);
    SDA_OUTPUT(0);
    SoftI2C_delay(DelayTick);
    SCL_OUTPUT(0);
}

void SoftI2C_write_byte(uint8_t value)
{
    uint8_t i;
//    uint8_t result = 0;
    i = 8;
    while (i)
    {
      if (value & 0x80){
        SDA_OUTPUT(1);
      }
      else{
        SDA_OUTPUT(0);
      }
      SoftI2C_delay(DelayTick);
      SCL_OUTPUT(1);
      i--;
      value <<= 1;
      SoftI2C_delay(DelayTick);
      SCL_OUTPUT(0);
      SoftI2C_delay(DelayTick);
    }
    SDA_INPUT(0);
    SoftI2C_delay(DelayTick);
    SCL_OUTPUT(1);
    SoftI2C_delay(DelayTick);
    if(PIN_SDA_GET())
    {
      nop();
//        result = 1;
    }
    SCL_OUTPUT(0);
    SoftI2C_delay(10);
    SDA_OUTPUT(1);
}
uint8_t SoftI2C_read_byte(uint8_t ack)
{
    uint8_t i;
    uint8_t result = 0;
    i = 8;
    SDA_INPUT(0);
    while (i)
    {
        result <<= 1;
        SCL_OUTPUT(1);
        i--;
        SoftI2C_delay(DelayTick);
        if(PIN_SDA_GET())
        {
            result |= 0x01;
        }
        SCL_OUTPUT(0);
        SoftI2C_delay(DelayTick);
    }
    SDA_OUTPUT(1);
    if (ack){
        SDA_OUTPUT(1);
    }
    else{
        SDA_OUTPUT(0);
    }
    SoftI2C_delay(DelayTick);
    SCL_OUTPUT(1);
    SoftI2C_delay(DelayTick);
    SCL_OUTPUT(0);
    SDA_OUTPUT(0);
    SoftI2C_delay(3);
    return result;
}

#endif