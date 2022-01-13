#ifndef LDSW20RF_H_ 
#define LDSW20RF_H_  
#include "device.h"
#include "tcc.h"

extern struct tcc_module tcc_instance;
/**********************************************************************/
extern void PHY_SetChannel(uint8_t channel);
extern void initAtrf233(void);
extern void phyWriteRegister(uint8_t reg, uint8_t value);
extern uint8_t phyReadRegister(uint8_t reg);
extern void phyWaitState(uint8_t state);
extern uint32_t tcc_get_count_value(const struct tcc_module *const module_inst);
extern void phyTrxSetState(uint8_t state);
extern void phySetRxState(void);
extern void PHY_DataReq(uint8_t *data,uint8_t length);
extern void PHY_SetRxState(bool rx);

void RxdRF6936(unsigned char cmmdChanel);
void Ldsw20ACkPackage(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void SetbTimerOfRatio(pwNodeCondig WRConfig,unsigned char Rfchannel);
void CopyTXpackage2ReSend(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void CheckCollison(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void Getchannel_timer(pwNodeCondig WRConfig);
void radio_data_pn_code(pwNodeCondig  WRConfig,unsigned char cmmdChanel);
void RadioSetpreamPnCode(pwNodeCondig  WRConfig,unsigned char removal,unsigned char cmmdChanel);
void RadioSetSopPnCode(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void mov_data(unsigned char *source,unsigned char *dist,unsigned char lenth);
void memset0(unsigned char *ptr,unsigned char ch,unsigned long length);
void memblockCopy(unsigned char *sdestAddr,unsigned char *dSourAddr,unsigned char length);


/*********************************************************************/
unsigned char CRCis_Valid(void);
unsigned char Ldsw20ACKPackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay);
unsigned char Ldsw20ACKPackReci(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay);
unsigned char Ldsw20RfPackReci(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char Ldsw20RfpackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char JudegeWorkCh(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char judge_collision(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char SendRfpackOption(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);
unsigned char isValidAckForMe(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char ReciWakeupSignal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char IssiAverage(unsigned char *s,unsigned char lens);
unsigned char SendRfpackOptionP2P(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);
unsigned char RicCMD(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void setRfPowerOfDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void sendawakepackageDone(pwNodeCondig WRConfig,unsigned char cmmdChanel);
/******************************************************************************/

extern void radio_ini(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void initRFOfAll(void);
void check_crystal_stable(unsigned char cmmdChanel);
void SelectChanel(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char reg_rdstatus(unsigned char r_addr,unsigned char cmmdChanel);
extern unsigned char reg_wregister(unsigned char r_addr,unsigned char r_data,unsigned char cmmdChanel);
extern void delayMs(unsigned long dls);
extern void Timers_delay2(uint8_t timerVal);
extern unsigned int CRC_16( unsigned char *aData, unsigned char aSize );
extern void tcc_disable_callback(struct tcc_module *const module,const enum tcc_callback callback_type);
//extern unsigned char DecryptionLength(pwNodeCondig WRConfig,unsigned char cmmdChanel);

#endif