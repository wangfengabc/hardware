#include <string.h>
#include <stdint.h>

#include "at86rf233.h"
#include "trx_access.h"
#include "devicetest.h"
#include "io_define.h"
#include "ldsw20rf.h"
#include "eemFlash.h"
#include "ldsw20.h"
#include "power.h"
#include "delay.h"
#include "port.h"
#include "tcc.h"
#include "phy.h"


#define TEST_MAXWAITTIME	30000	//设置ID时最大等待时间
#define TEST_SENDCNT		14000	//最大功率发送时间
#define TEST_SLEEPTIME		3000	//睡眠时间

unsigned long temp_addr=0;

extern sLDSW20Frame sPointerOfLDSW20Frame[MAXchannelNumb];
extern swNOdeConfig WriterConfig;




unsigned char Ldsw20ACKPackReci(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay)
{
	unsigned char *adata;
	unsigned char status;
	unsigned char recilength;
	unsigned long i;
	WRConfig->DeviceChannel.channel_temp = 5;
	SelectChanel(WRConfig,cmmdChanel);
	SetRxModuleOfNormal(cmmdChanel);
//	disptemp = (WRConfig->AttrOfDevice.TimerOfRatio[cmmdChanel].tempWait);
	delay_ms(2);
	for (i = 0; i < 60; i++)
	{
		delay_us(10);
		status = RF_ReadReg(IRQ_STATUS_REG);
		if((status&(1<<TRX_END)) != 0x00)
		{
			break;
		}else if (i >= 59)
		{
			return FALSE;
		}
	}
	trx_frame_read(&recilength, 1);
	if((recilength>12)||(recilength<5))
	{
		WRConfig->DeviceChannel.channel_temp = 0;
		radio_ini(WRConfig,cmmdChanel);
		SetRxModuleOfNormal(cmmdChanel);
		return FALSE;
	}
	WriterConfig.IrqCng.RssiOfcollisonStrenth = (int8_t)phyReadRegister(PHY_ED_LEVEL_REG);
	adata = &WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2];
	trx_frame_read(adata, (recilength-1));
	WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2]=(recilength-2);   /*raw data length , crc not include*/
	if(((WRConfig->uartParameter[cmmdChanel].uartRxdtemp[3]&0xf0)>>4)!= FRAMEOFACK)
	{
		WRConfig->DeviceChannel.channel_temp = 0;
		radio_ini(WRConfig,cmmdChanel);
		SetRxModuleOfNormal(cmmdChanel);
		return FALSE;
	}
	return TRUE;
}
/******************???**************************
Function:      Ldsw20ACKPackSend
Description:  ????ACK
Input:        pAttrOfRalerNode WRConfig  ?????????????
unsigned char Rfchannel     ????????
Output:
Others:      1.2007,6,5 ????
author:   ?????
*************************************************/
unsigned char Ldsw20ACKPackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay)
{
	unsigned char length;
	unsigned char status;
	Ldsw20ACkPackage(WRConfig,cmmdChanel);
	WRConfig->DeviceChannel.channel_temp=5;
	SelectChanel(WRConfig,cmmdChanel);
	length = WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] + 2;
	PHY_DataReq(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],length);
	for (int i = 0;i<WRConfig->AttrOfDevice.TimerOfRatio[0].tempOver;i++)
	{
		status = phyReadRegister(IRQ_STATUS_REG);
		if((status&(1 << TRX_END)) != 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}
/*******************************************************************************
*
*函 数：Test_Init( )
*功 能：结构体参数初始化
*输 入：
*输 出：TRUE：成功，FLASE，失败
*作 者：
*时 间：2019.1.16
*备 注：初始化结构体ID：1043
*
********************************************************************************/
static uint8_t TEST_Init(void)
{
    unsigned long i,memLength;
    unsigned char *sdata;

	memLength = (sizeof(WriterConfig.DeviceChannel)+sizeof(WriterConfig.AttrOfDevice)+3);//sizeof(WriterConfig.Password)+3;
	//memLength += sizeof(WriterConfig.MaprecordOfAlarm);
	//memLength += sizeof(WriterConfig.UserTransArea);
	//memLength += sizeof(WriterConfig.LocationArea);
	//memLength += sizeof(WriterConfig.UserDataArea);
	WriterConfig.spiDataLength = memLength;
	
    sdata =(unsigned char *)&WriterConfig;
    for(i=0;i<(sizeof(WriterConfig)-4);i++)
    {
	    *sdata++ =0;
    }
    WriterConfig.DeviceChannel.channel_temp =7;
    WriterConfig.DeviceChannel.DataRat[0]=0x00;
    WriterConfig.DeviceChannel.DataRat[1]=0x00;
    WriterConfig.DeviceChannel.DataRat[2]=0x00;
    WriterConfig.DeviceChannel.DataRat[3]=0x00;
    WriterConfig.DeviceChannel.SFD_Value[0] =0x59;
    WriterConfig.DeviceChannel.SFD_Value[1] =0x59;
    WriterConfig.DeviceChannel.SFD_Value[2] =0x59;
    WriterConfig.DeviceChannel.SFD_Value[3] =0x59;
    WriterConfig.DeviceChannel.Pow[0] =0x00;
    WriterConfig.DeviceChannel.Pow[1] =0x00;
    WriterConfig.DeviceChannel.Pow[2] =0x00;
    WriterConfig.DeviceChannel.Pow[3] =0x00;
    WriterConfig.DeviceChannel.Reci[0]=0x00;
    WriterConfig.DeviceChannel.Reci[1]=0x00;
    WriterConfig.DeviceChannel.Reci[2]=0x00;
    WriterConfig.DeviceChannel.Reci[3]=0x00;
    WriterConfig.DeviceChannel.F0= 0x0F;
    WriterConfig.DeviceChannel.F1= 0x18;
    WriterConfig.DeviceChannel.F2= 0x0C;
    WriterConfig.DeviceChannel.F3= 0x11;
    WriterConfig.DeviceChannel.F4= 0x13;
    WriterConfig.DeviceChannel.F5= 0x15;
    WriterConfig.DeviceChannel.F6= 0x19;
    WriterConfig.DeviceChannel.F7= 0x19;
    WriterConfig.DeviceChannel.T0= 0x1A;
    WriterConfig.DeviceChannel.T1= 0x17;
    WriterConfig.DeviceChannel.T2= 0x17;
    WriterConfig.DeviceChannel.T3= 0x17;

    WriterConfig.AttrOfDevice.DeviceID=1043;
    WriterConfig.AttrOfDevice.GroupId=0x64;
    WriterConfig.AttrOfDevice.AlarmValid = 0x00000001;
    WriterConfig.AttrOfDevice.AlarmStatus = 0x00000002;
    Getchannel_timer(&WriterConfig);
    WriterConfig.IrqCng.CollisonIntervalCount = 32;
    //WriterConfig.DeviceChannel.timerOfAwake[0]=0x00000000;
    //WriterConfig.DeviceChannel.timerOfAwake[1]=0x00009c20;
    WriterConfig.AttrOfDevice.RspTime=1;
    WriterConfig.ini_flag[0]=0x5a;
    WriterConfig.ini_flag[1]=0x0a5;
    WriterConfig.ini_flag[2]=0x065;

    WriterConfig.DeviceChannel.AsleepConst = 2000;
    WriterConfig.AttrOfDevice.HeartBeatenTime = 300000;
    WriterConfig.IrqCng.timerOfCollison = WriterConfig.DeviceChannel.AsleepConst+300;
    WriterConfig.IrqCng.HeartBeatCountMax = (WriterConfig.AttrOfDevice.HeartBeatenTime)/(WriterConfig.DeviceChannel.AsleepConst);
    WriterConfig.IrqCng.pran = 0x1000;
    WriterConfig.DeviceChannel.TimeOfRandWofTag.TimeOfRandW = 0;
    WriterConfig.DeviceChannel.TimeOfRandWofTag.RandW[0] = 0;
    WriterConfig.DeviceChannel.TimeOfRandWofTag.RandW[1] = 0;
    WriterConfig.spiDataLength = memLength;
    //Write_flash((unsigned char *)&WriterConfig,(unsigned short)WriterConfig.spiDataLength);
    nop();
    GetLDSW20MapNews(&WriterConfig);	
    return true;
}

/*******************************************************************************
 *
 *函 数：TEST_RicCMD( )
 *功 能：
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：成功
 *作 者：
 *时 间：2019.1.14
 *备 注：
 *
 ********************************************************************************/
 static unsigned char TEST_RicCMD(pwNodeCondig WRConfig,unsigned char cmmdChanel)
 {
	 unsigned long dls;
	 unsigned char *aData;
	 unsigned char regStatus;
	 unsigned char recilength;
	 for(dls=0;dls<30;dls++)
	 {
		 delay_us(33);
		 regStatus = phyReadRegister(IRQ_STATUS_REG);
		 if(((regStatus&(1 << TRX_END))!=0x00))               //not empty interrupt status
		 {
			 regStatus =  phyReadRegister(PHY_RSSI_REG);
			 if (regStatus&(1 << RX_CRC_VALID) == 0)
			 {
				 return FALSE;
			 }
			 trx_frame_read(&recilength, 1);
			 if((recilength>127)||(recilength<3))
			 {
				 WRConfig->DeviceChannel.channel_temp=1;
				 radio_ini(WRConfig,cmmdChanel);
				 SetRxModuleOfNormal(cmmdChanel);
				 return FALSE;
			 }
			 WRConfig->uartParameter[cmmdChanel].IssiStrength = (int8_t)phyReadRegister(PHY_ED_LEVEL_REG);//read rssi;
			 aData = &WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2];
			 trx_frame_read(aData,(recilength-1));
			 WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]=recilength-4;   /*raw data length , crc not include*/
			 if(CRC_16(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],(recilength-2)) != 0x00)
			 {
				 return FALSE;
			 }
			 sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl=(pLdsw20FrameCtl)(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3]);
			 if((GetPointerOfCmd(WRConfig, cmmdChanel)==FALSE)||(FunctionGetAttrOfDestDev(cmmdChanel)!=deviceOfTYPE)||(CheckPassward(WRConfig,cmmdChanel)==FALSE))//?????????????????????????????
			 {
				 WRConfig->DeviceChannel.channel_temp=1;
				 radio_ini(WRConfig,cmmdChanel);
				 SetRxModuleOfNormal(cmmdChanel);
				 return FALSE;
			 }
			 if((FunctionGetAttrDESTADRESSVALID(cmmdChanel)==TRUE)\
			 &&(*(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress)==WRConfig->AttrOfDevice.DeviceID))
			 {
				 if((FunctionGetAttrDESTGROUPVALID(cmmdChanel)==TRUE))
				 {
					 if(*(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup)!=WRConfig->AttrOfDevice.GroupId)
					 {
						 WRConfig->DeviceChannel.channel_temp=1;
						 radio_ini(WRConfig,cmmdChanel);
						 SetRxModuleOfNormal(cmmdChanel);
						 return FALSE;
					 }
				 }
				 Ldsw20ACKPackSend(WRConfig,cmmdChanel,500);
				 nop();
				 return TRUE;
			 }
		 }
	 }
	 return FALSE;
 }

/*******************************************************************************
*
*函 数：TEST_JudegTestFrame( )
*功 能：判断ID是否在FLASH中存储成功
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：成功，FLASE，失败
*作 者：
*时 间：2019.1.16
*备 注：
*
********************************************************************************/
uint8_t TEST_JudegTestFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	uint32_t tempsaveid=0;

	if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[2])&0x0f)!= TESTDEVICE)
	{
		nop();
		return true;
	}
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[43],(uint8_t *)&tempsaveid,4);	
	//tempsaveid=WRConfig->AttrOfDevice.DeviceID;
	Read_flash((unsigned char *)WRConfig,(unsigned short)WRConfig->spiDataLength);
	if(WRConfig->AttrOfDevice.DeviceID!=tempsaveid)
	{
		nop();
		return FALSE;		
	}
	
	return TRUE;
}

/*******************************************************************************
*
*函 数：TEST_MakeFrame_To_Search( )
*功 能：搜索帧组包函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：成功
*作 者：
*时 间：2019.1.14
*备 注：
*
********************************************************************************/
static unsigned char TEST_MakeFrame_To_Search(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{	
	unsigned char *SendDataPointor;
	unsigned char lens,temp;
  
	SendDataPointor = &WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	SendDataPointor[0] = 0x55;
	SendDataPointor[1] = 0xaa;
	SendDataPointor[3] = SendDataPointor[3]&0x00|TESTDEVICE|(FRAMEOFTEST<<4);
  
	SendDataPointor[4] = SendDataPointor[4]&0x00|DataDirectUp|BROADCAST<<2|(0x0F<<4);

	SendDataPointor[5] = SendDataPointor[5]&0x00|SMARTNODE|(NOGROUP<<4)|(0<<7);
	SendDataPointor[6] = SendDataPointor[6]&0x00|0x00;
	SendDataPointor[7] = SendDataPointor[7]&0x00|TESTDEVICE;
	temp =SendDataPointor[4];
	SendDataPointor = SendDataPointor + 8;

	if((temp&0x20)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.GroupId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x10)!=0)
	{
		*SendDataPointor++ = 0x00;
		*SendDataPointor++ = 0x00;
		*SendDataPointor++ = 0x00;
		*SendDataPointor++ = 0x00;
	}

	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.GroupId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	*SendDataPointor++ = 0x11;		/**链路级数*/
	mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);	/*链路ID*/
	SendDataPointor=SendDataPointor+4;	
  
	*SendDataPointor++ = 0x01;		/**参数长度**/
	*SendDataPointor++ = 0x40;		/**用户数据区**/
	
	*SendDataPointor++ = 0x00;		/**偏移地址**/
	*SendDataPointor++ = 0x00;
	*SendDataPointor++ = 0x00;
	*SendDataPointor++ = 0x00; 
	
	*SendDataPointor++ = deviceOfTYPE; 
  
	lens = SendDataPointor - &WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] - 1;
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] = lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens);
	return TRUE;
 }

/*******************************************************************************
*
*函 数：TEST_MakeFrame( )
*功 能：读写100组包函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
		i,测试序号
*输 出：TRUE：成功
*作 者：
*时 间：2019.1.14
*备 注：
*
********************************************************************************/
static unsigned char TEST_MakeFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned long tag_cnt)
{
	unsigned char *SendDataPointor;
	unsigned char lens,temp;
  
	SendDataPointor = &WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	SendDataPointor[0] = 0x55;
	SendDataPointor[1] = 0xaa;
	SendDataPointor[3] = SendDataPointor[3]&0x00|TESTDEVICE|(FRAMEOFTEST<<4);
  
	SendDataPointor[4] = SendDataPointor[4]&0x00|DataDirectUp|NOBROADCAST<<2|(0x0F<<4);

	SendDataPointor[5] = SendDataPointor[5]&0x00|SMARTNODE|(NOGROUP<<4)|(0<<7);
	SendDataPointor[6] = SendDataPointor[6]&0x00|0x00;
	SendDataPointor[7] = SendDataPointor[7]&0x00|TESTDEVICE;
	temp =SendDataPointor[4];
	SendDataPointor = SendDataPointor + 8;

	if((temp&0x20)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.GroupId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x10)!=0)
	{
		//*SendDataPointor++ = 0xe3;
		//*SendDataPointor++ = 0x07;
		//*SendDataPointor++ = 0x00;
		//*SendDataPointor++ = 0x00;
		mov_data((unsigned char *)&temp_addr,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}

	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.GroupId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	*SendDataPointor++ = 0x11;		/**链路级数*/
	mov_data((unsigned char*)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
	SendDataPointor += 4;
  
	*SendDataPointor++ = 0x06;		/**参数长度**/
	*SendDataPointor++ = 0x50;		/**用户数据区**/
	
	*SendDataPointor++ = 0x00;		/**偏移地址**/
	*SendDataPointor++ = 0x00;
	*SendDataPointor++ = 0x00;
	*SendDataPointor++ = 0x00;
	
	*SendDataPointor++ = WriterConfig.DeviceChannel.Pow[0];	 /**参数数据**/
	mov_data((unsigned char *)&tag_cnt,SendDataPointor,4);
	SendDataPointor=SendDataPointor+4;
	//tag_cnt++;
	
	*SendDataPointor++ = deviceOfTYPE;	/**设备属性**/
  
	lens = SendDataPointor - &WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] - 1;
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] = lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens);
	return TRUE;
 }
 
 /*******************************************************************************
 *
 *函 数：TEST_SendRfpackOptionP2P( )
 *功 能：生产测试函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：测试成功,FALSE：测试失败
 *作 者：
 *时 间：2019.1.14
 *备 注：
 *
 ********************************************************************************/ 
static unsigned char TEST_SendRfpackOptionP2P(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay)
 {
	 unsigned char txcount = 0;
	 do{
		 if(Ldsw20RfpackSend(WRConfig,cmmdChanel)==TRUE)
		 {
			 if(((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[5]&0x80)>>7))
			 {
				 nop();
				 return TRUE;
			 }
			 if(Ldsw20ACKPackReci(WRConfig,cmmdChanel,0) == TRUE)
			 {
				 //if(isValidAckForMe(WRConfig,cmmdChanel) == TRUE)
				 //{
					 nop();
					 return TRUE;
				 //}
			 }
		 }
		 txcount++;
		 delay_ms(15);
	 }while(txcount<retry);
	 
	 return FALSE;
 }
 /*******************************************************************************
 *
 *函 数：TEST_excuteCmdOfLDSW20( )
 *功 能：指令接收处理函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：测试成功,FALSE：测试失败
 *作 者：
 *时 间：2019.1.16
 *备 注：
 *
 ********************************************************************************/   
static unsigned char TEST_excuteCmdOfLDSW20(pwNodeCondig WRConfig,unsigned char cmmdChanel)
 {
	 mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
	 
	 switch(checkLdsw20(WRConfig,cmmdChanel))
	 {
		 case  0x01:
		 switch(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0e00)>>9))
		 {
			 case CmdAttrOfRD:
				 MakeUniversalFrame(WRConfig,cmmdChanel);
				 nop();
				 nop();
			 break;
			 case CmdAttrOfWD:
				 SendWritedataToMap(WRConfig,cmmdChanel);
				 Write_flash((unsigned char *)WRConfig,(unsigned short)WriterConfig.spiDataLength);
				 nop();
				 nop();
			 break;
			 case CmdAttrOfCLRbuffer:
			 break;
			 case CmdAttrOfRDRbuffer:
			 break;
			 case CmdAttrOfRStart:
			 break;
			 case CmdAttrOfREnd:
			 break;
			 default:
			 break;
		 }
		 break;
		 case 0x02:
		 break;
		 case 0x03:
		 break;
		 case 0x04:
		 break;
		 default:
		 return FALSE;
	 }
	 return  TRUE;
 }
 

 /*******************************************************************************
 *
 *函 数：TEST_ReciCmdProcesss( )
 *功 能：生产测试接收函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：测试成功,FALSE：测试失败
 *作 者：
 *时 间：2019.1.16
 *备 注：如果上位机没有收到返回信息则一直处于接受状态，只有当接收到第二帧读命令时才返回成功。
 *
 ********************************************************************************/  
static unsigned char TEST_ReciCmdProcesss(pwNodeCondig WRConfig,unsigned char cmmdChanel)
 {
	 unsigned long MAXCnt,TCnt;
	 
	 TCnt = 0;
	 MAXCnt = (unsigned long)(TEST_MAXWAITTIME/2.53);				//((WRConfig->IrqCng.waitSleepTime)/2.53);
	 WRConfig->DeviceChannel.channel_temp = 1;
	 radio_ini(WRConfig,cmmdChanel);
	 SetRxModuleOfNormal(cmmdChanel);
	 nop();
	 do{
		 if(TEST_RicCMD(WRConfig,cmmdChanel) == true)
		 {
			 TEST_excuteCmdOfLDSW20(WRConfig,cmmdChanel);
			 delay_ms(100);
			 
			 switch(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0e00)>>9))	//判断读写属性
			 {
				 case CmdAttrOfRD:
				 
				 nop();
				 
				 break;
				 		 
				 case CmdAttrOfWD:		
				 
				 if(TEST_JudegTestFrame(WRConfig,cmmdChanel)!=true)
				 {
					 nop();
					 continue;
				 }
				 
				 break;
			 }
			 
			 if(TEST_SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,10,2000) == true)
			 {
				 if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0e00)>>9)==CmdAttrOfRD)
				 {
					 nop();
					 return TRUE;
				 }
				
			 }
			WRConfig->DeviceChannel.channel_temp = 1;
			SelectChanel(WRConfig,cmmdChanel);
			SetRxModuleOfNormal(cmmdChanel);
		 }
		 TCnt++;
	 }while(TCnt < MAXCnt);
	 
	 WRConfig->DeviceChannel.channel_temp = 0;
	 radio_ini(WRConfig,cmmdChanel);
	 SetRxModuleOfNormal(cmmdChanel);
	 
	 return FALSE;
 }
 
  /*******************************************************************************
 *
 *函 数：TEST_Sleep( )
 *功 能：睡眠测试函数
 *输 入：
 *输 出：
 *作 者：
 *时 间：2019.1.17
 *备 注：
 *
 ********************************************************************************/
 static void TEST_Sleep(void)
 {
	tcc_init_self(TEST_SLEEPTIME);
	PHY_Sleep();
	cpu_irq_enable();
	system_voltage_reference_disable(SYSTEM_VOLTAGE_REFERENCE_BANDGAP);
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();	 
 }
 
/*******************************************************************************
 *
 *函 数：TEST_Power( )
 *功 能：功率测试函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：
 *作 者：
 *时 间：2019.1.17
 *备 注：
 *
 ********************************************************************************/
 static void TEST_Power(pwNodeCondig WRConfig,uint8_t cmmdChanel)
 {
	uint16_t i=0;
	uint8_t SendTest_Buff[127]={0x7d,0x55,0xaa,0x00,0x00};
	 
	WRConfig->DeviceChannel.channel_temp = 6;		//修改长发射频通道为6
	SelectChanel(WRConfig,cmmdChanel);

	for(i=0;i<TEST_SENDCNT;i++)
	PHY_DataReq(SendTest_Buff,SendTest_Buff[0]);
 }
 
/*******************************************************************************
 *
 *函 数：TEST_SuccessRate( )
 *功 能：读写成功率测试函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：
 *作 者：
 *时 间：2019.1.17
 *备 注：
 *
 ********************************************************************************/ 
static void TEST_SuccessRate(pwNodeCondig WRConfig,uint8_t cmmdChanel)
{
	unsigned long i=0;
	
 	memset(WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,0,127);	//清除发送缓存区
 	
 	for(i=1;i<101;i++)
 	{
	 	TEST_MakeFrame(WRConfig,cmmdChanel,i);
	 	SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,1,2000);
	 	delay_ms(100);
 	}
 	
 	memset(WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,0,127);
}

/*******************************************************************************
 *
 *函 数：TEST_SearchDevice( )
 *功 能：搜索设备函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：测试成功,FALSE：测试失败
 *作 者：
 *时 间：2019.1.17
 *备 注：
 *
 ********************************************************************************/ 
static uint8_t TEST_SearchDevice(pwNodeCondig WRConfig,uint8_t cmmdChanel)
{
	uint8_t i=0;
	
	TEST_MakeFrame_To_Search(WRConfig,cmmdChanel);
		
	for(i=0;i<3;i++)
	{
		if(SendRfpackOptionP2P(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000)==TRUE)
		{
			mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdtemp[10],(unsigned char *)&temp_addr,4);	//从返回的ACK中存储源设备ID
			break;
		}
		delay_ms(100);
	}
	
	if(i>=3) 
		return FALSE;
	else
		return TRUE;
}

 /*******************************************************************************
 *
 *函 数：TEST_WRTag( )
 *功 能：生产测试函数
 *输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
 *输 出：TRUE：测试成功,FALSE：测试失败
 *作 者：
 *时 间：2019.1.14
 *备 注：
 *
 ********************************************************************************/
uint8_t TEST_WRTag(pwNodeCondig WRConfig,uint8_t cmmdChanel)
{
        TEST_Init();
	PHY_SetTxPower(0xF);	//修改发射功率
		
	RedLED_OPEN();			//开功放
	//OPENPOWER();			
		
	/*搜索测试设备*/	
	if(TEST_SearchDevice(WRConfig,cmmdChanel)!=TRUE)	
	{
		nop();
		return FALSE;		//如果搜索不到就退出测试函数
	}
		
	/*睡眠测试6秒*/	
	TEST_Sleep();
	
	/*长发送6秒*/	
	TEST_Power(WRConfig,cmmdChanel);
		
	/*读发测试100次*/	
	TEST_SuccessRate(WRConfig,cmmdChanel);
		
	/*修改设备ID*/				
	if(TEST_ReciCmdProcesss(WRConfig,cmmdChanel)==true)
	{
		nop();
		PHY_SetTxPower(0X00);	//恢复发射功率
		return TRUE;		
	}
		
	PHY_SetTxPower(0X00);		//恢复发射功率
	return FALSE;	
}
