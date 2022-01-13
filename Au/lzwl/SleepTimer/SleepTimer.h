/*
 * SleepTimer.h
 *
 * Created: 2018/11/13 16:29:00
 *  Author: Administrator
 */ 


#ifndef SLEEPTIMER_H_
#define SLEEPTIMER_H_
extern void configure_power_manager(void);
extern void configure_tcc(unsigned long cnt);
extern void tcc_init_self(unsigned long cnt);
extern enum status_code readflash_byte(uint16_t const addr,uint16_t *const buffer);
extern void PHY_Sleep(void);
extern uint16_t PHY_RandomReq(void);
void EnterSleepModule(void);
void LZWL_Into_long_Sleep(void);
unsigned long JudgeTimeSleep(void);
unsigned long DoSeelpOfCollision(pwNodeCondig WRConfig,unsigned char cmmdChanel);

extern void Tcc_Disable_Init(void);
extern void _system_extint_init(void);
extern unsigned char CheckLEDStatus(pwNodeCondig WRConfig);
void JYLZ_IntoIdleModule(uint32_t cnt);
void LZWL_Into_long_Sleep(void);
extern void Tag_Led_Switch(pwNodeCondig WRConfig);

#endif /* SLEEPTIMER_H_ */