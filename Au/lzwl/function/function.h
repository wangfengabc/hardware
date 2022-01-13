#ifndef _MAINH_H_
#define _MAINH_H_
#include "device.h"
#define  NormalMode           0x00
#define  LocationMode         0x01
#define  InintativeReport     0x02

 
void iniMcu(void);
void OutFromSleep(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void initRFOfAll(void);
void iniRF(void);
void CollisionProcess(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void NoCollisionProcess(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void ini_exint(void);
//void ini_exint2(void);//????2
void ini_RfOfexInt(void);
void iniStatus(void);
void main(void);
unsigned char DoHeartBeat(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char judgeVibrate(pwNodeCondig WRConfig,unsigned char cmmdChanel);

unsigned char judgeDataOfswriterRetuen(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char judgeLonsleep(pwNodeCondig WRConfig);
unsigned char judgePowerValue(pwNodeCondig WRConfig);
unsigned char judgePower(pwNodeCondig WRConfig,unsigned char cmmdChanel);

extern unsigned char MakeHeartBeatFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void MakeAlarmFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned char AlarmFlg);
extern unsigned char ReciWakeupSignal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char ExcuteLDSW20(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void SetRxModuleOfNormal(unsigned char cmmdChanel);
extern void radio_ini(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void inToSleep(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void LocationFramePack(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void memblockCopy(unsigned char *sdestAddr,unsigned char *dSourAddr,unsigned char length);
extern unsigned char judegeCycleOfRAndW(pwNodeCondig WRConfig);
extern unsigned char SendRfpackOptionP2P(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);
extern unsigned char ReciCmdProcesss(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void Timers_delay2(uint8_t timerVal);
extern void Timers_delay1(uint16_t timerVal);


extern void RFinoSleep(void);
extern double GetAdcValue(void);
extern void LEDflicker(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void softtimer(unsigned short ms);
extern unsigned char AlarmOfDisassemble(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void judgeDisassemble(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char getKeyIoStatus2(void);
extern void Led2ReverseProcess(pwNodeCondig WRConfig);

extern unsigned long LedFlickerTime(pwNodeCondig WRConfig);
extern unsigned char LEDStatusProcess(pwNodeCondig WRConfig);
extern unsigned long DoSeelpOfCollision(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern void ChangeLEDStatus(pwNodeCondig WRConfig,unsigned char LSTmp,unsigned char LIDTmp);
//extern void inToSleep_test(pwNodeCondig WRConfig,unsigned char cmmdChanel);

extern uint8_t JYZL_GetAwakeFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel, uint32_t cnt);
extern uint8_t SendRfpackOptionOfAwake(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);

unsigned char SendOfWakeup(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned long Quoting(unsigned long *addr);
#endif

