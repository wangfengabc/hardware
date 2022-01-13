/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F27K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#include <stdint.h>
#include "adc.h"
#include "delay.h"
#include "function.h"
#include "ldsw20.h"
#include "device.h"
#include "io_define.h"
swNOdeConfig WriterConfig;

void TestPower(void){
    unsigned char i;
    for(i = 0;i < 51;i++){
        //LEDReverse(0);
        softtimer(300);
    }
}

void iniStatus(void)
{
    WriterConfig.IrqCng.LEDFlg = 0;
    WriterConfig.IrqCng.timeMargin = 0;
    WriterConfig.IrqCng.CollisonInterval=0;
    WriterConfig.IrqCng.SleepDelayFlg = 0;
    WriterConfig.IrqCng.shakeHsflg = 0;
    WriterConfig.IrqCng.workMode = NormalMode;
    WriterConfig.IrqCng.sleeptimerCnt = 0;
    WriterConfig.IrqCng.sleeptimerCntMax = 10;
    WriterConfig.IrqCng.LongSleep = 0;
    WriterConfig.IrqCng.DisassembleFlg = 0;
    WriterConfig.PowerValveThreshold = 2300;
    WriterConfig.IrqCng.VibrateFlg = 0;
    WriterConfig.IrqCng.VibrateKeyFlg = 0;
    WriterConfig.IrqCng.DisassembleKeyFlg = 0;
    WriterConfig.IrqCng.PowerAlarmKeyFlg = 0;
    WriterConfig.IrqCng.CollisonIntervalCount = 32;
    WriterConfig.IrqCng.timerOfCollison = WriterConfig.DeviceChannel.AsleepConst+300;
    WriterConfig.IrqCng.HeartBeatCountMax = (WriterConfig.AttrOfDevice.HeartBeatenTime)/(WriterConfig.DeviceChannel.AsleepConst)+20;
    WriterConfig.IrqCng.Tag_ON_OFF = 0;
    WriterConfig.IrqCng.KeyFlg = 2;
}

void initRFOfAll(void)
{
	radio_ini(&WriterConfig,0);
	SetRxModuleOfNormal(0);
	#ifdef AviationTag

	#else
	OPENPOWER();
	#endif
}

void iniRF(void)
{
   
}

unsigned char judgeLed(pwNodeCondig WRConfig)
{
	unsigned long temp;
	if (LEDStatusProcess(WRConfig) == FALSE)
	{
		return FALSE;
	}
	temp = LedFlickerTime(WRConfig);
	WRConfig->IrqCng.timeMarginCnt += temp;
    if(WRConfig->IrqCng.CollisonInterval ==1){
        if(WRConfig->IrqCng.timeMarginCnt < WRConfig->IrqCng.timerOfCollison){
            return TRUE;
        }
		if (DoSeelpOfCollision(&WriterConfig,0) == 0)
			return TRUE;
        WRConfig->IrqCng.timeMarginCnt = 0;
        return FALSE;
    }
    if(!WriterConfig.IrqCng.Special2Flg){
        if(WRConfig->IrqCng.timeMarginCnt < (WRConfig->IrqCng.timeMargin+500)){
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        if(WRConfig->IrqCng.timeMarginCnt < (WRConfig->IrqCng.SpecialFrame2Time+1000)){
            return TRUE;
        }else{
            return FALSE;
        }
    }
}

unsigned char judgePowerValue(pwNodeCondig WRConfig)
{
    WRConfig->PowerValve = adc_read_value();
    if(WRConfig->PowerValve >= WRConfig->PowerValveThreshold){
                WRConfig->AttrOfDevice.AlarmValid &= ~0x00000001;
		WRConfig->AttrOfDevice.AlarmStatus &= ~0x00000001;	
        return 0;
    }else{
		WRConfig->AttrOfDevice.AlarmValid |= 0x00000001;
		WRConfig->AttrOfDevice.AlarmStatus |= 0x00000001;
        return 1;
    }
}
unsigned char judgePower(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    if(judgePowerValue(WRConfig) == 0)
    {
        ChangeLEDStatus(WRConfig, 0, 2);
        WRConfig->IrqCng.PowerAlarmKeyFlg = 0;
        return FALSE;
    }else if(WRConfig->IrqCng.PowerAlarmFlg == 0){
		ChangeLEDStatus(WRConfig, 2, 2);
        if(WRConfig->IrqCng.PowerAlarmKeyFlg == 1){
            return TRUE;
        }
        MakeAlarmFrame(WRConfig,cmmdChanel,1);
        if(SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000)){
            WRConfig->IrqCng.PowerAlarmKeyFlg = 1;
        }else{
            WRConfig->IrqCng.PowerAlarmKeyFlg = 0;
        }
        return TRUE;
    }
    return FALSE;
}

unsigned char judgeLonsleep(pwNodeCondig WRConfig)
{
    if(WriterConfig.IrqCng.LongSleep && (WRConfig->IrqCng.sleeptimerCnt <= WRConfig->IrqCng.sleeptimerCntMax))
    {
        WRConfig->IrqCng.sleeptimerCnt = 0;
        WriterConfig.IrqCng.LongSleep = 0;
        return TRUE;
    }else{
        WRConfig->IrqCng.sleeptimerCnt++;
        return FALSE;
    }
    
}
unsigned char judgeVibrate(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    if(WRConfig->IrqCng.VibrateFlg != 1){
        return FALSE;
    }else{
		WRConfig->AttrOfDevice.AlarmValid |= 0x00000004;
		WRConfig->AttrOfDevice.AlarmStatus |= 0x00000004;
		MakeAlarmFrame(WRConfig,cmmdChanel,1);
        if(SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000) == TRUE){
            WRConfig->IrqCng.VibrateFlg = 0;
            return TRUE;
        }
    }
    return FALSE;
}

unsigned char judgeDataOfswriterRetuen(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  if(WriterConfig.IrqCng.Special2Flg!=TRUE)
  {
    return FALSE;
  }
  else
  {
    WRConfig->IrqCng.Special2Flg = 0;
    SendOfWakeup(WRConfig, cmmdChanel);
//    if(WRConfig->IrqCng.PtpWakeup != 1)
//    {
//      if (WRConfig->IrqCng.LEDFlg)
//      {
//        WRConfig->IrqCng.LEDFlg = 0;
//        SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
//        return TRUE;
//      }
//      SendRfpackOptionOfAwake(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
//      return TRUE;
//    }
//    else
//    {
//      WRConfig->IrqCng.PtpWakeup = 0;
//      if(SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000)==true)
//      {
//        ReciCmdProcesss(WRConfig,cmmdChanel);
//        return TRUE;
//      }
//    }
  }
  return TRUE;
}
void OutFromSleep(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    iniMcu();
    if(WRConfig->IrqCng.CollisonInterval ==1)
    {
        if(judgeLed(WRConfig) == true){
	        return;
        }
    	CollisionProcess(WRConfig,cmmdChanel);
    	return;
    }
	else
    {
    	if(judgeLonsleep(WRConfig)==TRUE)
    		return;
        if(judgeLed(WRConfig) == TRUE){
            return;
        }
    	if(judgeDataOfswriterRetuen( WRConfig,cmmdChanel)==TRUE)
    		return;
        judgePower(WRConfig,cmmdChanel);
	DoHeartBeat(WRConfig,cmmdChanel);
		
#if (CabinetTag)
			judgeDisassemble(WRConfig,cmmdChanel);
			judgeVibrate(WRConfig,cmmdChanel);
#endif

        switch(judegeCycleOfRAndW(WRConfig))
    	{
    		case 1:
     			NoCollisionProcess(WRConfig,cmmdChanel);
                break;
    		case 2:
     			LocationFramePack(WRConfig,cmmdChanel);
     			SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
                break;
	        default:
                break;
    	}
	} 
}

void CollisionProcess(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  memblockCopy(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].UartSendBuffer[0],\
    (WRConfig->uartParameter[cmmdChanel].UartSendBuffer[2]+5));
  SendRfpackOptionOfAwake(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
}

void NoCollisionProcess(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    if (JYZL_GetAwakeFrame(WRConfig,cmmdChanel,5) != TRUE)
 	return;
    if(ExcuteLDSW20(&WriterConfig,cmmdChanel)!=true)
        return;
}

unsigned char DoHeartBeat(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned long CntTemp;
  CntTemp = LedFlickerTime(WRConfig);
  WRConfig->IrqCng.HeartBeatCount += (CntTemp+6);
  if(WRConfig->IrqCng.HeartBeatCount < WRConfig->AttrOfDevice.HeartBeatenTime){
    return TRUE;
  }
  WRConfig->IrqCng.HeartBeatCount = 0;
  MakeHeartBeatFrame(WRConfig,cmmdChanel);
  if(SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000)){
    WriterConfig.IrqCng.KeyFlg = 0;
    return TRUE;
  }
  return TRUE;
}
void judgeDisassemble(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  if((WRConfig->IrqCng.DisassembleFlg == 0)&&(WRConfig->IrqCng.DisassembleKeyFlg == 0)){
    return;
  }else{
    WRConfig->AttrOfDevice.AlarmValid |= 0x00000002;
    WRConfig->AttrOfDevice.AlarmStatus |= 0x00000002;
    if(AlarmOfDisassemble(WRConfig,cmmdChanel) == true){
      WRConfig->IrqCng.DisassembleFlg = 0;
      WRConfig->IrqCng.DisassembleKeyFlg = 0;
    }else{
      WRConfig->IrqCng.DisassembleKeyFlg = 1;
    }
    return;
  }
}
unsigned long Quoting(unsigned long *addr)
{
	uint8_t *tmp;
	tmp = (uint8_t *)addr;
	return (*tmp | *(tmp+1)<<8 | *(tmp+2)<<16 | *(tmp+3)<<24);
}

/**
 End of File
*/