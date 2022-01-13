#ifndef MAIN_H_
#define MAIN_H_

#include "auxdevice.h"

extern swNOdeConfig WriterConfig;

extern void configure_nvm(void);
extern void iniFramMemery(void);
extern void initRFOfAll(void);
extern void RxdRF6936(unsigned char cmmdChanel);
extern unsigned char excuteLDSW20(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void Calculate_Crc16(unsigned char * aData, unsigned char aSize );
#endif /* INCFILE1_H_ */