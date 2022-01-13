#ifndef LDSW20OFAUX_H_
#define LDSW20OFAUX_H_

#include "auxdevice.h"



unsigned char MakeDataTransFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void sendBackForRddataNews(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeUniversalFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char MakeTransFrameOf2Universal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char MakeTransFrameOfReturnNiversal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char excuteLDSW20(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void Calculate_Crc16(unsigned char * aData, unsigned char aSize ) ;
extern int USART1_TxBuf(uint8_t *buffer, int nbytes);
extern unsigned char MakeTransFrameOfWRiterUniversal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void radio_ini(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void RxdRF6936(unsigned char cmmdChanel);
extern void timer_delay(long dls);
void jump_bootload(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char WritedataToMap(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void  SendWritedataToMap(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char checkDevChain(unsigned short Attr);
void MakeWriteRsp(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeDataTransFrameForGPS(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeUniversalFrameForTEST(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void SendCallToNoExtendboard(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void clrMemeryOfAlarm(pwNodeCondig WRConfig);
void DoCallPackage(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeTransFrameOf1UniversalforTEST(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char LDSW_BoardcastFrameTest(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeTransFrameOf1UniversalforTEST(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char SendRfpackOptionFortag(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);
unsigned char sendDownToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeDataReturnFrameForTest(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char sendWdDownToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char sendUpToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel);

#endif
