#include "device.h"
#include "ldsw20.h"
#include "sio2host.h"
#include "stdlib.h"
#include "des.h"


swNOdeConfig WriterConfig;
sLDSW20deviceMap pointerOfLDSW20deviceMap[16];
sLDSW20Frame    sPointerOfLDSW20Frame[MAXchannelNumb]={0};


/*获取控制域各种参数*/
unsigned char FunctionGetAttrOfDestDev(unsigned char cmmdChanel)
{
	return GetAttrOfDestDev(cmmdChanel);
}
unsigned char FunctionGetAttrOfsourceDev(unsigned char cmmdChanel)
{
	return GetAttrOfsourceDev(cmmdChanel);
}
unsigned char FunctionGetAttrDataDirect(unsigned char cmmdChanel)
{
	return GetAttrDataDirect(cmmdChanel);
}
unsigned char FunctionGetAttrDataDataCompare(unsigned char cmmdChanel)
{
	return GetAttrDataDataCompare(cmmdChanel);
}
unsigned char FunctionGetAttrBROADCAST(unsigned char cmmdChanel)
{
	return GetAttrBROADCAST(cmmdChanel);
}
unsigned char FunctionGetAttrGROUP(unsigned char cmmdChanel)
{
	return GetAttrGROUP(cmmdChanel);
}
unsigned char FunctionGetAttrFRAME(unsigned char cmmdChanel)
{
	return GetAttrFRAME(cmmdChanel);
}
unsigned char FunctionGetAttrDESTADRESSVALID(unsigned char cmmdChanel)
{
	return GetAttrDESTADRESSVALID(cmmdChanel);
}
unsigned char FunctionGetAttrDESTGROUPVALID(unsigned char cmmdChanel)
{
	return GetAttrDESTGROUPVALID(cmmdChanel);
}
unsigned char FunctionGetAttrSOURCEADRESSVALID(unsigned char cmmdChanel)
{
	return GetAttrSOURCEADRESSVALID(cmmdChanel);
}
unsigned char FunctionGetAttrSOURCEGROUPVALID(unsigned char cmmdChanel)
{
	return GetAttrSOURCEGROUPVALID(cmmdChanel);
}
unsigned char FunctionGetAttrGROUPSORT(unsigned char cmmdChanel)
{
	return GetAttrGROUPSORT(cmmdChanel);
}

unsigned char FunctionGetAttrDATARETURNSTATUS(unsigned char cmmdChanel)
{
	return GetAttrDATARETURNSTATUS(cmmdChanel);
}
unsigned char FunctionGetAttrPASSWORDSEC(unsigned char cmmdChanel)
{
	return GetAttrPASSWORDSEC(cmmdChanel);
}
unsigned char FunctionGetAttrDATAENCODEStatus(unsigned char cmmdChanel)
{
	return GetAttrDATAENCODEStatus(cmmdChanel);
}
unsigned char FunctionGetAttrDATAENCODEsec(unsigned char cmmdChanel)
{
	return GetAttrDATAENCODEsec(cmmdChanel);
}
unsigned char FunctionGetAttrDeviceOfBroadcast(unsigned char cmmdChanel)
{
	return GetAttrDeviceOfBroadcast(cmmdChanel);
}
unsigned char FunctionGetAttrAUXMODELENABLE(unsigned char cmmdChanel)
{
	return GetAttrAUXMODELENABLE(cmmdChanel);
}
unsigned char FunctionGetAttrDEVBeCTRL(unsigned char cmmdChanel)
{
	return GetAttrDEVBeCTRL(cmmdChanel);
}
/**********************************************************/
/*操作控制域各种参数*/

unsigned char FunctionChangeAttrOfDestDev(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrOfDestDev(cmmdChanel,x);
}
unsigned char FunctionChangeAttrOfsourceDev(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrOfsourceDev(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDataDirect(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDataDirect(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDataDataCompare(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDataDataCompare(cmmdChanel,x);
}
unsigned char FunctionChangeAttrBROADCAST(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrBROADCAST(cmmdChanel,x);
}
unsigned char FunctionChangeAttrGROUP(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrGROUP(cmmdChanel,x);
}
unsigned char FunctionChangeAttrFRAME(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrFRAME(cmmdChanel,x);
}

unsigned char FunctionChangeAttrDESTADRESSVALID(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDESTADRESSVALID(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDESTGROUPVALID(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDESTGROUPVALID(cmmdChanel,x);
}
unsigned char FunctionChangeAttrSOURCEADRESSVALID(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrSOURCEADRESSVALID(cmmdChanel,x);
}
unsigned char FunctionChangeAttrSOURCEGROUPVALID(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrSOURCEGROUPVALID(cmmdChanel,x);
}
unsigned char FunctionChangeAttrGROUPSORT(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrGROUPSORT(cmmdChanel,x);  
}
unsigned char FunctionChangeAttrDATARETURNSTATUS(unsigned char cmmdChanel,unsigned char x)
{
    return ChangeAttrDATARETURNSTATUS(cmmdChanel,x);
}
unsigned char FunctionChangeAttrPASSWORDSEC(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrPASSWORDSEC(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDATAENCODEStatus(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDATAENCODEStatus(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDATAENCODEsec(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDATAENCODEsec(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDeviceOfBroadcast(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDeviceOfBroadcast(cmmdChanel,x);
}
unsigned char FunctionChangeAttrAUXMODELENABLE(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrAUXMODELENABLE(cmmdChanel,x);
}
unsigned char FunctionChangeAttrDEVBeCTRL(unsigned char cmmdChanel,unsigned char x)
{
	return ChangeAttrDEVBeCTRL(cmmdChanel,x);
}


void GetSourceTOSetChannel(uint8_t cmmdChanel)
{
	if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[2]&0x0f)==devOfDwritor)
	{
		nop();
		WriterConfig.DeviceChannel.channel_temp =1;
	}
	if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[2]&0x0f)==devOfBaseStation)
	{
		nop();
		WriterConfig.DeviceChannel.channel_temp =2;
	}
}


unsigned char GetPointerOfCmd(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	switch(FunctionGetAttrFRAME(cmmdChanel))	//获取帧的类型
	{
		case  FRAMEOFCTL :
		case  FRAMEOFDATA :
		case  FRAMEOFLOCA:
		case  FRAMEOFRESP:
		case  FRAMEOFKILL:
		case  FRAMEOFINVENT:
		case  FRAMEOFALARM:
		case  FRAMEOFHEARTBEAT:
		case  FRAMEOFBOOTUP:
		case  FRAMEOFJOIN:
		case  FRAMEOFCALL:
		sPointerOfLDSW20Frame[cmmdChanel].pAreaofFramePswd= (pLdsw20FramePswd)((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl+5);
		if(FunctionGetAttrPASSWORDSEC(cmmdChanel)!=0x00)
		{
			sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup   =(unsigned long *)((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFramePswd+8);
		}
		else
		{
			sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup   =(unsigned long *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFramePswd;
		}
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress  =sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup+FunctionGetAttrDESTGROUPVALID(cmmdChanel);
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup =sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress+FunctionGetAttrDESTADRESSVALID(cmmdChanel);
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress=sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup+FunctionGetAttrSOURCEGROUPVALID(cmmdChanel);
		sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain =(pLdsw20FrameChain)((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup+\
		(FunctionGetAttrDESTGROUPVALID(cmmdChanel)+FunctionGetAttrDESTADRESSVALID(cmmdChanel)+FunctionGetAttrSOURCEGROUPVALID(cmmdChanel)+\
		FunctionGetAttrSOURCEADRESSVALID( cmmdChanel))*4);
		sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd =(pLdsw20FrameCmd)(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4)*4+1+(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain);
		
		sPointerOfLDSW20Frame[cmmdChanel].offsetOfAdress=(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress-(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl;
		sPointerOfLDSW20Frame[cmmdChanel].offsetOfFrameChain=(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain-(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl;
		sPointerOfLDSW20Frame[cmmdChanel].offsetOfFrameCmd=(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd-(unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl;
		break;
		case  FRAMEOFTEST:	//测试帧
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup  =(unsigned long *)((unsigned char *)(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl)+2);
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress  =sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup+FunctionGetAttrDESTGROUPVALID(cmmdChanel);
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup =sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress+FunctionGetAttrDESTADRESSVALID(cmmdChanel);
		sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress=sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup+FunctionGetAttrSOURCEGROUPVALID(cmmdChanel);
		break;
		case  FRAMEOFACK :
		break;
		
		default:
		return FALSE;
	}
	return TRUE;
	
}
/*******************************************************************************
*
*函 CheckPassward( )
*功 能：本函数用于对比口令
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即数据是从哪个通道进入的，通道取值0-5)
*输 出：3无需检查口令，TRUE：对应检查正确,FALSE：口令检查错误
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char CheckPassward(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char i,temp,ptemp;
    
	if(FunctionGetAttrOfDestDev(cmmdChanel)!=FunctionGetAttrDEVBeCTRL(cmmdChanel))
        return 2;//传输未到终点
   
	temp=FunctionGetAttrPASSWORDSEC(cmmdChanel);//返回0不需要口令
	
	if(temp!=0x00)
	{
        ptemp=WRConfig->Password.passwordVoildByte[temp-1];
		for(i=0;i<8;i++)
		{
			if((ptemp&0x01)==0x01)
			{
				if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFramePswd->parmofCmd[i]!=WRConfig->Password.PassWard0[temp-1][i])
				return FALSE;
			}
			ptemp=ptemp>>1;
		}
		return TRUE;
	}
	else
	{
		return 3;//无需判断口令密码
	}
}


/*******************************************************************************
*
*函 数：checkLdsw20( )
*功 能：检测设备的帧类型并返回
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：对应的帧类型,FALSE：检查错误
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char checkLdsw20(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl=(pLdsw20FrameCtl)(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3]);

	if(GetPointerOfCmd(WRConfig, cmmdChanel)==FALSE)		//获取指令序列中控制域，地址域，链路域，指令域，口令区指针 
		return FALSE;
	if((FunctionGetAttrOfDestDev(cmmdChanel)!=deviceOfTYPE)&&(FunctionGetAttrOfDestDev(cmmdChanel)!=devOfDwritor))	//仅接收指令接收设备为指定设备的指令。不同的设备这里必须不同
		return FALSE;
	if(CheckPassward(WRConfig,cmmdChanel)==FALSE)			//检查口令
		return FALSE;
	
	switch(FunctionGetAttrFRAME(cmmdChanel))				//判断信息帧属性
	{
		case  FRAMEOFCTL:
		case  FRAMEOFDATA:
		case  FRAMEOFLOCA:
		case  FRAMEOFRESP:
		case  FRAMEOFKILL:
		case  FRAMEOFINVENT:
		case  FRAMEOFALARM:
		case  FRAMEOFHEARTBEAT:
		case  FRAMEOFBOOTUP:
		case  FRAMEOFJOIN:
			
		if(FunctionGetAttrBROADCAST(cmmdChanel)!=BROADCAST)	//判断是否为广播模式
		{
			//判断目标地址是否有效及设备目标地址与本身ID地址是否相等
			if((FunctionGetAttrDESTADRESSVALID(cmmdChanel)==TRUE)&&(Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress)!=WRConfig->AttrOfDevice.DeviceID))
			return FALSE;
			//判断设备群地址是否有效及设备目标地址与本身ID地址是否相等
			if((FunctionGetAttrDESTGROUPVALID(cmmdChanel)==TRUE)&&(Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup)!=WRConfig->AttrOfDevice.GroupId))
			return FALSE;
		}
		GetLDSW20MapNews(WRConfig);	//获取各类数据区的指针和长度(大小)。
		return 1;
		
		case  FRAMEOFCALL:			//唤醒
		return 2;
		
		case  FRAMEOFACK :			//ACK帧
		return 3;
		
		case FRAMEOFTEST:			//测试帧
		return 4;
		
		default:
		return FALSE;
	}
}

/************************************
获取各类数据区的指针和长度。
设备信道参数区  0
设备告警数据区  1
设备定位数据区  2
设备口令数据区  3
设备属性数据区  4
设备用户数据区  5
设备数传数据区  6
设备备用链路区  7
设备绑定数据区  8
传感器数据区    9
读设备固件版本区13
*************************************/
unsigned char GetLDSW20MapNews(pwNodeCondig WRConfig)
{
	pointerOfLDSW20deviceMap[0].mapPointer=(unsigned char *)&WRConfig->UserTransArea;
	pointerOfLDSW20deviceMap[0].mapLenth  =sizeof(WRConfig->UserTransArea);
	pointerOfLDSW20deviceMap[1].mapPointer=(unsigned char *)&WRConfig->MaprecordOfAlarm;
	pointerOfLDSW20deviceMap[1].mapLenth  =sizeof(WRConfig->MaprecordOfAlarm);
	pointerOfLDSW20deviceMap[2].mapPointer=(unsigned char *)&WRConfig->LocationDataArea;
	pointerOfLDSW20deviceMap[2].mapLenth  =sizeof(WRConfig->LocationDataArea);
	pointerOfLDSW20deviceMap[3].mapPointer=(unsigned char *)&WRConfig->Password;
	pointerOfLDSW20deviceMap[3].mapLenth  =sizeof(WRConfig->Password);
	pointerOfLDSW20deviceMap[4].mapPointer=(unsigned char *)&WRConfig->AttrOfDevice;
	pointerOfLDSW20deviceMap[4].mapLenth  =sizeof(WRConfig->AttrOfDevice);
	pointerOfLDSW20deviceMap[5].mapPointer=(unsigned char *)&WRConfig->UserDataArea;
	pointerOfLDSW20deviceMap[5].mapLenth  =sizeof(WRConfig->UserDataArea);
	pointerOfLDSW20deviceMap[6].mapPointer=(unsigned char *)&WRConfig->DeviceChannel;//
	pointerOfLDSW20deviceMap[6].mapLenth  =sizeof(WRConfig->DeviceChannel);
	pointerOfLDSW20deviceMap[7].mapPointer=(unsigned char *)&WRConfig->InventorArea;
	pointerOfLDSW20deviceMap[7].mapLenth  =sizeof(WRConfig->InventorArea);
	//pointerOfLDSW20deviceMap[8].mapPointer=(unsigned char *)&WRConfig->rfBingDevArea;
	//pointerOfLDSW20deviceMap[8].mapLenth  =sizeof(WRConfig->rfBingDevArea);
	//pointerOfLDSW20deviceMap[9].mapPointer=(unsigned char *)&WRConfig->sensorInfoArea;
	//pointerOfLDSW20deviceMap[9].mapLenth  =sizeof(WRConfig->sensorInfoArea);
	//pointerOfLDSW20deviceMap[10].mapPointer=(unsigned char *)&WRConfig->CacheArea;
	//pointerOfLDSW20deviceMap[10].mapLenth  =sizeof(WRConfig->CacheArea);
	pointerOfLDSW20deviceMap[13].mapPointer=(unsigned char *)&WRConfig->FirmwareVerID;
	pointerOfLDSW20deviceMap[13].mapLenth  =sizeof(RW_FIRMWARE_VERSION_ID);
	
	return TRUE;
}

/*******************************************************************************
*
*函 数：checkMemeryOfRAM( )
*功 能：
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从
*       哪个通道进入的，通道取值0-5)
*输 出：告警区域数组中可存储的节点
*作 者：WGS
*时 间：2018.12.07
*备 注：NONE
*
********************************************************************************/
//unsigned short checkMemeryOfRAM(pwNodeCondig WRConfig,unsigned char cmmdChanel)
//{
  //unsigned short i;
  //
  //for( i=0;i<32;i++)
  //{
    //if(WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Flag==0x00)
      //return (i);
    //if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[0] == WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Tag)//去除再次接收数据时ID重复的问题
      //return (i);
  //}
  //return (i-1);
//}

/*******************************************************************************
*
*函 数：SaveDealdeDataOfInventoryToMemeryOfRAM( )
*功 能：数据存储在RAM中
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从
*       哪个通道进入的，通道取值0-5)
*输 出：NONE
*作 者：WGS
*时 间：2018.12.07
*备 注：NONE
*
********************************************************************************/

void SaveDealdeDataOfInventoryToMemeryOfRAM(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned short i,j;
  //LongType *longdtat;
  //LongType *shortData;
  
  if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[0]==0x00)
    return;
  i=checkMemeryOfRAM( WRConfig, cmmdChanel);
  
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Tag =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[0];
  //shortData = (LongType *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0];
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].CmdByte=shortData->long_;
  //longdtat =(LongType *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[2];
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].AlarmValid=(longdtat)->long_;
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].AlarmStatus=(longdtat+1)->long_;
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Rssi=WRConfig->uartParameter[cmmdChanel].IssiStrength;
  //WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Power=sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[11];
  /*从指令域的参数区拷贝12个字节 采集终端ID 采集终端告警有效位 采集终端告警状态位*/
  mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],(unsigned char *)&WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Tag,12);
  WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Rssi=WRConfig->uartParameter[cmmdChanel].IssiStrength;		//拷贝本身的信号强度
  j=(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x001ff)-12;
  mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[12],&WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].text[0],j);
  if(WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Flag != 0xee)
  {
    WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Flag=0xee;
    WRConfig->MaprecordOfAlarm.QuantityOfRecords= WRConfig->MaprecordOfAlarm.QuantityOfRecords+1;
    if(WRConfig->MaprecordOfAlarm.QuantityOfRecords>512)
    {
      WRConfig->MaprecordOfAlarm.QuantityOfRecords=512;
    }
  }
}


/*******************************************************************************
*
*函 数：DealdeDataOfInventory( )
*功 能：数据存储处理
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从
*       哪个通道进入的，通道取值0-5)
*输 出：
*作 者：WGS
*时 间：2018.12.07
*备 注：NONE
*
********************************************************************************/
unsigned char DealdeDataOfInventory(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  //获取信息帧属性
  switch((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[0]&0x0f0)>>4)
  {
    case FRAMEOFALARM://告警帧
    case FRAMEOFRESP: //应答帧
      if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[1]&0x01)!=0x01)     //数据是否上行
        return 0x0e;
      if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[4]&0x0e)>>5)!=0x00)//数据是否来自标签
        return 0x0e;
      //数据转发方式
      switch((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[3]&0x03))
      {
        case 0x01: //存储本地，写铁电(下行命令返回数据需要存储在FRAM)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
          //saveToEEprom(WRConfig,cmmdChanel);
          return 1;
        case 0x02: //存储转发，缓存在RAM中 (下行命令返回数据需要存储在RAM中等待上层应用读取)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
        case 0x00: //转发(下行命令返回数据需要及时回传) 
          return 2;
        case 0x03: //无需返回(下行命令无需返回任何数据)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
          return 3; 
      }
    case FRAMEOFHEARTBEAT://心跳帧
      if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[1]&0x01)!=0x00 &&\
        (((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[4]&0x0e)>>5) == 0x00))
        return 0x04;
      break;
    default:
      break;
  }
  return 0x0a;
}

unsigned char MakeTransFrameOfWRiterUniversal(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],RxdDataPointor[2]+3);
	//WRConfig->AttrOfDevice.PCId=*sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress;
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.PCId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	temp = *SendDataPointor;
	if(((temp&0x0f0)>>4)==0x00)
	return FALSE;
	(*SendDataPointor)--;
	temp--;
	nop();
	if(((temp&0x0f0)>>4)<(temp&0x0f))
	return FALSE;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	nop();
	nop();
	switch((temp&0x0f))
	{
		case 0x00:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfPC;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);//源设备属性变化，目标设备属性变为源设备属性
		Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
		memset0(&WRConfig->uartParameter[1].uartTxdBuffer[0], 0, 255);
		mov_data(SendDataPointor,&WRConfig->uartParameter[1].uartTxdBuffer[0],(SendDataPointor[2]+5));
		USART1_TxBuf(&WRConfig->uartParameter[1].uartTxdBuffer[0], (WRConfig->uartParameter[1].uartTxdBuffer[2]+5));
		break;
		case 0x01:
		break;
		case 0x02:
		break;
		default:
		break;
	}
	return TRUE;
}

unsigned char MakeTransFrameOf1Universal(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|((RxdDataPointor[7]&0xe0)>>5);//目标设备属性变化，终端设备属性变为目标设备属性
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
	
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f)],SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	(*SendDataPointor)++;
	// sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb++;
	if((((*SendDataPointor)&0x0f0)>>4)>8)
	return FALSE;
	nop();
	if((((*SendDataPointor)&0x0f0)>>4)\
	<((*SendDataPointor)&0x0f))
	return FALSE;
	// WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
	nop();
	return TRUE;
}

unsigned char MakeTransFrameOf2Universal(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|((RxdDataPointor[7]&0xe0)>>5);//目标设备属性变化，终端设备属性变为目标设备属性
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
	
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f)],SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	(*SendDataPointor)++;
	// sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb++;
	if((((*SendDataPointor)&0x0f0)>>4)>8)
	return FALSE;
	nop();
	if((((*SendDataPointor)&0x0f0)>>4)\
	<((*SendDataPointor)&0x0f))
	return FALSE;
	// WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
	nop();
	return TRUE;
	
}

unsigned char MakeTransFrameOfReturnNiversal(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	
	//  WRConfig->AttrOfDevice.PCId=*sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress;
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.PCId,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	temp=*SendDataPointor;
	if(((temp&0x0f0)>>4)==0x00)
	return FALSE;
	(*SendDataPointor)--;
	temp--;
	nop();
	if(((temp&0x0f0)>>4)<(temp&0x0f))
	return FALSE;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	nop();
	nop();
	switch((temp&0x0f))
	{
		case 0x00:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfPC;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);//源设备属性变化，目标设备属性变为源设备属性
		Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
		mov_data(SendDataPointor,&WRConfig->uartParameter[1].uartTxdBuffer[0],(SendDataPointor[2]+5));
		break;
		case 0x01:
		break;
		case 0x02:
		break;
		default:
		break;
		
	}
	nop();
	nop();
	
	return TRUE;
	
}

unsigned char MakeTransFrameOfmultiUniversalForBaseStation(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned char chainIndex)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	
	switch(chainIndex)
	{
		case 18:
		break;
		case 19:
		break;
		case 20:
		break;
		case 21:
		break;
		case 22:
		break;
		case 23:
		break;
		case 24:
		break;
		case 25:
		break;
		case 26:
		break;
		case 27:
		break;
		case 28:
		break;
		case 29:
		break;
		case 30:
		break;
		case 31:
		break;
		case 32:
		break;
		case 33:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfDwritor;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 34:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfDwritor;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 35:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 36:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 37:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 38:
		case 39:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		case 255:
		return FALSE;
		default:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//目标设备属性变化，终端设备属性变为目标设备属性
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//源设备属性变化，目标设备属性变为源设备属性
		break;
		
	}
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f)],SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	(*SendDataPointor)++;
	// sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb++;
	if((((*SendDataPointor)&0x0f0)>>4)>8)
	return FALSE;
	nop();
	if((((*SendDataPointor)&0x0f0)>>4)\
	<((*SendDataPointor)&0x0f))
	return FALSE;
	// WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
	nop();
	return TRUE;
	
}

unsigned char MakeCallFrameToSmartNode(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,lens;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	
	mov_data(&RxdDataPointor[3],&SendDataPointor[3],2);
	SendDataPointor+=5;
	mov_data(&WRConfig->InventorArea.InventorInfo.CmdIndex,SendDataPointor,1);
	SendDataPointor++;
	mov_data(&WRConfig->InventorArea.InventorInfo.param,SendDataPointor,1);
	SendDataPointor++;
	mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
	SendDataPointor+=4;
	mov_data((unsigned char *)&WRConfig->InventorArea.InventorInfo.timerOfAwake[0],SendDataPointor,4);
	SendDataPointor+=4;
	mov_data((unsigned char *)&WRConfig->InventorArea.InventorInfo.timerOfAwake[1],SendDataPointor,4);
	SendDataPointor+=4;
	lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3] =((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3]&0xf0)|SMARTNODE);
	switch(WRConfig->InventorArea.InventorInfo.CmdIndex )
	{
		case 0x00:
		WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[4] = (WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[4]&0xf3) | (BROADCAST<<2);
		break;
		case 0x01:
		break;
		case 0x21:
		break;
		case 0x22:
		WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[4] = (WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[4]&0xf3) | (BROADCAST<<2);
		break;
		default:
		break;
	}
	return TRUE;
}


unsigned long Quoting(unsigned long *addr)
{
	uint8_t *tmp;
	
	tmp = (uint8_t *)addr;
	return (*tmp | *(tmp+1)<<8 | *(tmp+2)<<16 | *(tmp+3)<<24);
}

