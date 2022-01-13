/*
 * SleepTimer.c
 *
 * Created: 2018/11/13 16:26:47
 *  Author: Administrator
 */ 
#include <stdio.h>
#include "device.h"
#include "ldsw20.h"
#include "io_define.h"
#include "SleepTimer.h"
#include "power.h"
#include "delay.h"

#define RANDL_MAX 2147483647
#define MAXchannelNumb    2

extern swNOdeConfig WriterConfig;
static unsigned long next = 1;
static unsigned short randomtime;


int randl( void )
{
	return ( ( next = next * 1103515245 + 12345 ) % RANDL_MAX );
}

void srandl( unsigned int seed )
{
	next = seed;
}

unsigned long randr( unsigned long min, unsigned long max )
{
	return ( unsigned long )randl( ) % ( max - min + 1 ) + min;
}

unsigned short Randowdata(void)
{
	unsigned short ran;
	unsigned short rancle;
	//rancle = TMR2_ReadTimer();
	//readflash_byte(WriterConfig.IrqCng.pran,&rancle);//FLASH_ReadWord(WriterConfig.IrqCng.pran + (WriterConfig.AttrOfDevice.DeviceID)%5000);
	rancle = PHY_RandomReq();
	
	//while (1)
	//{
		//rancle = PHY_RandomReq();
		//randtest = rancle;
		//srandl(rancle);
		//ran = randr(36,300);
		//randtest = ran;
		//delay_ms(ran);
		//nop();
	//}
	
	
	//nop();
	//WriterConfig.IrqCng.pran += ((WriterConfig.AttrOfDevice.DeviceID)%10);
	//if(WriterConfig.IrqCng.pran - 0x1000 > ((WriterConfig.AttrOfDevice.DeviceID)%5000)+2048)
	//{
		//WriterConfig.IrqCng.pran = 0x1000;
	//}
	srandl(rancle);
	ran = randr(36,500);
	return ran;
}

unsigned short RandowdataOfCollision(void)
{
	unsigned short ran;
	unsigned short rancle;
	//readflash_byte(WriterConfig.IrqCng.pran,&rancle);//FLASH_ReadWord(WriterConfig.IrqCng.pran);
	//nop();
	//WriterConfig.IrqCng.pran += 2;
	//if(WriterConfig.IrqCng.pran - 0x107CC > 4068)
	//{
		//WriterConfig.IrqCng.pran = 0x107CC;
	//}
	rancle = PHY_RandomReq();
	srandl(rancle);
	ran = randr(100,800);
	return ran;
}

unsigned char CollisonCnt(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	if(WRConfig->IrqCng.CollisonInterval != 1)
		return FALSE;
	WRConfig->IrqCng.CollisonComppareCount++;
	if(WRConfig->IrqCng.CollisonComppareCount>WRConfig->IrqCng.CollisonIntervalCount)
	{
		WRConfig->IrqCng.CollisonInterval =0;
		WRConfig->IrqCng.CollisonComppareCount=0;
		WRConfig->IrqCng.timerOfCollison = WRConfig->DeviceChannel.AsleepConst+300;
		return FALSE;
	}
	return TRUE;
}

unsigned long DoSeelpOfCollision(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	if (CollisonCnt(WRConfig, cmmdChanel) != TRUE)
	{
		return 0;
	}
    randomtime = RandowdataOfCollision();
    WRConfig->IrqCng.timerOfCollison = ((WRConfig->IrqCng.timerOfCollison)/2);
    return (WRConfig->IrqCng.timerOfCollison + randomtime);
}

void TimeSleep(void)
{
	unsigned long sleepCnt=0;
	switch (CheckLEDStatus(&WriterConfig))
	{
		case 0:
			sleepCnt = JudgeTimeSleep();
		break;
		case 1:
			sleepCnt = 100;
		break;
		case 2:
			sleepCnt = 1000;
		break;
	}
	if(sleepCnt > 624450)
	{
		WriterConfig.IrqCng.LongSleep = 1;
		WriterConfig.IrqCng.sleeptimerCntMax = sleepCnt;
		sleepCnt = 8326;
	}
	if(sleepCnt <= 5){
		sleepCnt = WriterConfig.DeviceChannel.AsleepConst;
	}
	sleepCnt = (sleepCnt*2);
	tcc_init_self(sleepCnt);
}

unsigned long JudgeTimeSleep(void)
{
	unsigned long sleepCnt=0;
	unsigned short randtime;
	if(WriterConfig.IrqCng.CollisonInterval != 1)
	{
			if(!WriterConfig.IrqCng.Special2Flg)
			{
				if(WriterConfig.IrqCng.SleepDelayFlg == 1)
				{
					WriterConfig.IrqCng.SleepDelayFlg = 0;
					sleepCnt = WriterConfig.IrqCng.timeMargin;
					if(sleepCnt <= 5){
						sleepCnt = WriterConfig.DeviceChannel.AsleepConst;
					}
				}else
				{
					randtime = Randowdata();
					sleepCnt = (WriterConfig.DeviceChannel.AsleepConst) + randtime;
				}
			}
			else
			{
				sleepCnt = (WriterConfig.IrqCng.SpecialFrame2Time+300);
			}
		}else
		{
			sleepCnt = DoSeelpOfCollision(&WriterConfig,0);
		}
		return sleepCnt;
}




//void TimeSleep1(void)
//{
	//unsigned long sleepCnt=0;
	//unsigned short randtime;
	//nop();
	//
	//if(WriterConfig.IrqCng.CollisonInterval != 1)
	//{
		//if(WriterConfig.IrqCng.LedFlgTemp != 1){
			//if(!WriterConfig.IrqCng.Special2Flg)
			//{
				//if(WriterConfig.IrqCng.SleepDelayFlg == 1)
				//{
					//WriterConfig.IrqCng.SleepDelayFlg = 0;
					//sleepCnt = ((WriterConfig.IrqCng.timeMargin)/2);
					//if(sleepCnt <= 5){
						//sleepCnt = ((WriterConfig.DeviceChannel.AsleepConst)/2);
					//}
				//}else
				//{
					//randtime = Randowdata();
					//sleepCnt = (((WriterConfig.DeviceChannel.AsleepConst) + randtime)/2);
				//}
			//}
			//else
			//{
				//sleepCnt = (((WriterConfig.IrqCng.SpecialFrame2Time+300))/2);
			//}
			//}else{
				//if(((WriterConfig.IrqCng.LEDFlickerparems.LEDflgStatus)&0x0055) != 0){
						//sleepCnt = 20;  //40ms
					//}else if(((WriterConfig.IrqCng.LEDFlickerparems.LEDflgStatus)&0x00AA) != 0){
						//sleepCnt = 300; //600ms
					//}else{
						//randtime = Randowdata();
						//sleepCnt= (((WriterConfig.DeviceChannel.AsleepConst)+ randtime)/2);
				//}
		//}
	//}else
	//{
		////if(WriterConfig.IrqCng.LedFlgTemp != 1){
			//sleepCnt = DoSeelpOfCollision(&WriterConfig,0);
			//sleepCnt = ((sleepCnt)/2);
			////}else{
			////if(((WriterConfig.IrqCng.LEDFlickerparems.LEDflgStatus)&0x0055) != 0){
				////sleepCnt = 20;  //40ms
				////}else if(((WriterConfig.IrqCng.LEDFlickerparems.LEDflgStatus)&0x00AA) != 0){
				////sleepCnt = 300; //600ms
				////}else{
				//////LedBlueClose();
				//////LedGreenClose();
				//////WriterConfig.IrqCng.CollisonTimerCount = DoSeelpOfCollision(&WriterConfig,0);
				//////WriterConfig.IrqCng.CollisonTimerCount = ((WriterConfig.IrqCng.CollisonTimerCount)/2);
			////}
			////WriterConfig.IrqCng.CollisonTimerCount = DoSeelpOfCollision(&WriterConfig,0);
		////}
	//}
	//if(sleepCnt > 6244500000)
	//{
		//WriterConfig.IrqCng.LongSleep = 1;
		//WriterConfig.IrqCng.sleeptimerCntMax = sleepCnt/2;
		//sleepCnt = 8326;
	//}
	//tcc_init_self(sleepCnt);
//}
void EnterSleepModule(void)
{
        if((WriterConfig.IrqCng.Tag_ON_OFF != 0)){
            TimeSleep();
        }
        do{
            Tag_Led_Switch(&WriterConfig);
            LZWL_Into_long_Sleep();
        }while((WriterConfig.IrqCng.Tag_ON_OFF == 0));
//	PHY_Sleep();
//	//configure_power_manager();
//	system_voltage_reference_disable(SYSTEM_VOLTAGE_REFERENCE_BANDGAP);
//	cpu_irq_enable();
//	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
//	system_sleep();
}

void JYLZ_IntoIdleModule(uint32_t cnt)
{
		tcc_init_self(cnt);
		cpu_irq_enable();
		system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE_2);
		system_sleep();
}
void LZWL_Into_long_Sleep(void)
{
		PHY_Sleep();
		system_voltage_reference_disable(SYSTEM_VOLTAGE_REFERENCE_BANDGAP);
		cpu_irq_enable();
		system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
		system_sleep();
}