#ifndef	DEVICETEST_H_
#define DEVICETEST_H_

#include <compiler.h>
#include "device.h"

extern unsigned char MakeUniversalFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void  SendWritedataToMap(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned long Quoting(unsigned long *addr);

uint8_t TEST_WRTag(pwNodeCondig WRConfig,uint8_t cmmdChanel);

#endif