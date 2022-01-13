#include "ldsw20.h"
#include "ldsw20rf.h"
#include "ldsw20ofaux.h"
#include "string.h"
#include "delay.h"
#define  e222 <io_define.h>
#include e222


uint8_t Savr_Source_DEV=0XFF;

/*******************************************************************************
*
*数组：ChainJTable[]
*功 能：链路查询
*时 间：2018.12.20
*备 注：<<4,1<<8,2<<8，分别代表连接总数
*
********************************************************************************/
const unsigned short ChainJTable[64] = { 
/*	目标设备属性          终端设备设备属性			总链路级数		*/	
	(devOfSwritor		|(devOfSwritor			<<4)),			//0
	(devOfDwritor		|(devOfDwritor			<<4)),			//1
	(devOfBaseStation	|(devOfBaseStation		<<4)),			//2
	(devOfSmartModel	|(devOfSmartModel<<4)	|(1<<8)),		//3
	(devOfSmartModel	|(devOfLocator<<4)		|(1<<8)),		//4
	(devOfLocator		|(devOfLocator<<4)		|(1<<8)),		//5
	(devOfSmartModel	|(devOfSwritor<<4)		|(1<<8)),		//6
	(devOfLocator		|(devOfSwritor<<4)		|(1<<8)),		//7
	(devOfSwritor		|(devOfSwritor<<4)		|(1<<8)),		//8
	(devOfSmartModel	|(devOfDwritor<<4)		|(1<<8)),		//9
	(devOfLocator		|(devOfDwritor<<4)		|(1<<8)),		//10
	(devOfDwritor		|(devOfDwritor<<4)		|(1<<8)),		//11
	(devOfRepeater		|(devOfRepeater<<4)		|(1<<8)),		//12
	(devOfSwritor		|(devOfBaseStation<<4)	|(1<<8)),		//13
	(devOfDwritor		|(devOfBaseStation<<4)	|(1<<8)),		//14
	(devOfRepeater		|(devOfBaseStation<<4)	|(1<<8)),		//15
	(devOfHander		|(devOfBaseStation<<4)	|(1<<8)),		//16
	(devOfSmartModel	|(devOfHander<<4)		|(1<<8)),		//17
	(devOfLocator		|(devOfHander<<4)		|(1<<8)),		//18
	(devOfSwritor		|(devOfHander<<4)		|(1<<8)),		//19
	(devOfDwritor		|(devOfHander<<4)		|(1<<8)),		//20
	(devOfRepeater		|(devOfHander<<4)		|(1<<8)),		//21
	(devOfBaseStation	|(devOfHander<<4)		|(1<<8)),		//22
	(devOfSmartModel	|(devOfSmartModel<<4)	|(2<<8)),		//23
	(devOfSmartModel	|(devOfLocator<<4)		|(2<<8)),		//24
	(devOfLocator		|(devOfLocator<<4)		|(2<<8)),		//25
	(devOfSmartModel	|(devOfSwritor<<4)		|(2<<8)),		//26
	(devOfLocator		|(devOfSwritor<<4)		|(2<<8)),		//27
	(devOfSwritor		|(devOfSwritor<<4)		|(2<<8)),		//28
	(devOfSmartModel	|(devOfDwritor<<4)		|(2<<8)),		//29
	(devOfLocator		|(devOfDwritor<<4)		|(2<<8)),		//30
	(devOfDwritor		|(devOfDwritor<<4)		|(2<<8)),		//31
	(devOfRepeater		|(devOfRepeater<<4)		|(2<<8)),		//32
	(devOfSmartModel	|(devOfBaseStation<<4)	|(2<<8)),		//33
	(devOfLocator		|(devOfBaseStation<<4)	|(2<<8)),		//34
	(devOfSwritor		|(devOfBaseStation<<4)	|(2<<8)),		//35
	(devOfDwritor		|(devOfBaseStation<<4)	|(2<<8)),		//36
	(devOfRepeater		|(devOfBaseStation<<4)	|(2<<8)),		//37
	(devOfHander		|(devOfBaseStation<<4)	|(2<<8)),		//38
	(devOfHander		|(devOfHander<<4)		|(2<<8)),		//39
	(devOfAuxiliary		|(devOfAuxiliary<<4)	|(1<<8)),		//40
};


unsigned char MakeDataTransFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  //mov_data(WRConfig->uartParameter[0].uartRxdBuffer,WRConfig->uartParameter[cmmdChanel].uartRxdtemp,(WRConfig->uartParameter[0].uartRxdBuffer[2]+5));
  unsigned char *SendDataPointor,*RxdDataPointor,temp;
  unsigned short lens;
  lens=ChainJTable[0];
  SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
  RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  SendDataPointor[0]=0x55;
  SendDataPointor[1]=0xaa;
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0x0c0)>>2)|((RxdDataPointor[4]&0x030)<<2);//目标，源设备属性地址有效位交换
  SendDataPointor[4] |= DataDirectUp;
  SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFDATA<<4);
  SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|(RxdDataPointor[5]&0x0f);
  SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);
  temp =SendDataPointor[4];
  SendDataPointor=SendDataPointor+8;
  if((temp&0x20)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
    SendDataPointor=SendDataPointor+4;
  }
  if((temp&0x10)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
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
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));
  SendDataPointor=SendDataPointor+temp*4+1;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);
  *SendDataPointor = (WRConfig->uartParameter[1].uartRxdBuffer[1]+2);
  SendDataPointor=SendDataPointor+6;
  
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12;
  lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;
  nop();
  nop();
  mov_data(WRConfig->uartParameter[1].uartRxdBuffer,SendDataPointor,(WRConfig->uartParameter[1].uartRxdBuffer[1]+2));
  SendDataPointor=SendDataPointor+WRConfig->uartParameter[1].uartRxdPointer;
  nop();
  nop();
  lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
  WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
  nop();
  Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );
  return TRUE;
  
}

/*******************************************************************************
*
*函 数：MakeUniversalFrame( )
*功 能：串口组包函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：组包成功,FALSE：组包错误
*作 者：
*时 间：2018.12.20
*备 注：用于发送给上位机的组包
*
********************************************************************************/
unsigned char MakeUniversalFrame(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned char *SendDataPointor,*RxdDataPointor,temp;
  unsigned short lens;
  
  lens=ChainJTable[0];

  SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
  RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  
  SendDataPointor[0]=0x55;
  SendDataPointor[1]=0xaa;
  
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0xc0)>>2)|((RxdDataPointor[4]&0x30)<<2);//目标，源设备属性地址有效位交换
  SendDataPointor[4] |= DataDirectUp;
  SendDataPointor[4] |= (NOBROADCAST<<2);
  SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFDATA<<4);
  SendDataPointor[3]=(SendDataPointor[3]&0xf0)|(RxdDataPointor[5]&0x0f);
  SendDataPointor[5]=(SendDataPointor[5]&0xf0)|(RxdDataPointor[3]&0x0f);
  temp =SendDataPointor[4];

  SendDataPointor=SendDataPointor+8;
  
  if((temp&0x20)!=0)	//判断源设备群地址有效位是否有效
  {
	  mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
	  SendDataPointor=SendDataPointor+4;
  }
  if((temp&0x10)!=0)	//判断源设备地址有效位是否有效
  {
	  mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
	  SendDataPointor=SendDataPointor+4;
  }
  if((temp&0x80)!=0)	//判断目标设备群地址有效位是否有效
  {
	  mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);
	  SendDataPointor=SendDataPointor+4;
  }
  if((temp&0x40)!=0)	//判断目标设备地址有效位是否有效
  {
	  if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12)==mfirmwareArea){
		  mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
		  SendDataPointor=SendDataPointor+4;
		  }else{
		  mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		  SendDataPointor=SendDataPointor+4;
	  }
  }
  
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0xf0)>>4;	//传输链路
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));	//地址偏移
  SendDataPointor=SendDataPointor+temp*4+1;
  
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);	//指令长度6位
  SendDataPointor=SendDataPointor+6;
  
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0xf000)>>12;//获取参数数据区属性 
  lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;//获取参数数据区长度
  
  if(pointerOfLDSW20deviceMap[temp].mapLenth>=(temp+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress))
  {
	if(temp!=mfirmwareArea)		//判断是不是告警数据区
	{
		mov_data((unsigned char *)(pointerOfLDSW20deviceMap[temp].mapPointer+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress),SendDataPointor,lens);//获取参数数据区数据
		SendDataPointor=SendDataPointor+lens;
	}
	else
	{
		mov_data(RW_FIRMWARE_VERSION_ID,SendDataPointor,FIRMWARE_VERSION_ID_LEN);
		SendDataPointor=SendDataPointor+FIRMWARE_VERSION_ID_LEN;
	}
  }
  else
  {
	  return FALSE;
  }

  lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
  WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
  Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );
  
  return TRUE;
}
/*******************************************************************************
*
*函 数：sendBackForRddataNews( )
*功 能：串口组包上传给上位机
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
void sendBackForRddataNews(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  MakeUniversalFrame(WRConfig,cmmdChanel);
  if(cmmdChanel == 1)
  {
	  USART1_TxBuf(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0], (WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]+5));
  }
}

/************************************
*************************************/
unsigned char WritedataToMap(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned char *SendDataPointor,*RxdDataPointor,temp;
  unsigned short lens;
  

  
  SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
  RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  SendDataPointor[0]=0x55;
  SendDataPointor[1]=0xaa;
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0x0c0)>>2)|((RxdDataPointor[4]&0x030)<<2);//目标，源设备属性地址有效位交换
  SendDataPointor[4] |= DataDirectUp;
  SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFRESP<<4);
  SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|(RxdDataPointor[5]&0x0f);
  SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);
  temp =SendDataPointor[4];
  SendDataPointor=SendDataPointor+8;
  
  if((temp&0x20)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
    SendDataPointor=SendDataPointor+4;
  } 
  if((temp&0x10)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
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
  
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));
  SendDataPointor=SendDataPointor+temp*4+1;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);
  SendDataPointor=SendDataPointor+6;
  
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12;
  lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;
 
  *SendDataPointor++=0x01;

  lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
  WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
  
  Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );
  
  if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0xf000)>>12)!=mUserTransArea)
  {
    if(cmmdChanel == 0)
    {
      SendRfpackOption(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
    }else
    {
		/*返回应答帧	参数为01代表写入成功*/
		USART1_TxBuf(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0], (WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]+5));
    }
  }
  if(pointerOfLDSW20deviceMap[temp].mapLenth>=(temp+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress))
  {
	WriterConfig.AttrOfDevice.GroupId=Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup);  
	WriterConfig.AttrOfDevice.DeviceID=Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress);  
	GetSourceTOSetChannel(cmmdChanel);	
	/* parmofCmd[0] 为指令控制中的参数数据起始头 */
    mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],(unsigned char *)(pointerOfLDSW20deviceMap[temp].mapPointer+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress),\
      (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff));		//写入PC下发的数据
  }
  else
  {
    mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],WRConfig->uartParameter[cmmdChanel].uartTxdtemp,\
      (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff));
    WRConfig->RfFrameDatCtrls.TimerEn = 0;
    WRConfig->RfFrameDatCtrls.senddatatransFlg = 1;
  }
  return TRUE;
}

/************************************
*************************************/
void  SendWritedataToMap(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{ 
  WritedataToMap(WRConfig,cmmdChanel);
}

/************************************
*************************************/
unsigned char checkDevChain(unsigned short Attr)
{
  unsigned char i;
  for(i=0;i<41;i++)
  {
    if(Attr==ChainJTable[i])
    {
      return i;
    }
  }
  for(i=23;i<41;i++)
  {
    if((Attr&0xff)==(ChainJTable[i]&0xff))
    {
      return (i);
    }
  }
  return 255;
}

unsigned char MakeDataTransFrameForGPS(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	unsigned short lens;
	lens=ChainJTable[0];
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0x0c0)>>2)|((RxdDataPointor[4]&0x030)<<2);//目标，源设备属性地址有效位交换
	SendDataPointor[4] |= DataDirectUp;
	SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFDATA<<4);
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|(RxdDataPointor[5]&0x0f);
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
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
	temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4;
	mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));
	SendDataPointor=SendDataPointor+temp*4+1;
	mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);
	*SendDataPointor = (WRConfig->uartParameter[1].uartReci_length)+1;
	SendDataPointor=SendDataPointor+6;
	temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12;
	lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;
	nop();
	nop();
	mov_data(&WRConfig->uartParameter[cmmdChanel].IssiStrength,SendDataPointor,1);
	SendDataPointor++;
	mov_data(WRConfig->uartParameter[1].uartRxdBuffer,SendDataPointor,(WRConfig->uartParameter[1].uartReci_length));
	SendDataPointor=SendDataPointor+WRConfig->uartParameter[1].uartReci_length+1;
	nop();
	nop();
	lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
	nop();
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );
	return TRUE;
	
}

/*********************************************************
                 for  test
**********************************************************/
unsigned char MakeUniversalFrameForTEST(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned char *SendDataPointor,*RxdDataPointor,temp;
  unsigned short lens;
  lens=ChainJTable[0];
  SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
  RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  SendDataPointor[0]=0x55;
  SendDataPointor[1]=0xaa;
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0x0c0)>>2)|((RxdDataPointor[4]&0x030)<<2);//目标，源设备属性地址有效位交换
  SendDataPointor[4] |= DataDirectUp;
  SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFDATA<<4);
  SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|(RxdDataPointor[5]&0x0f);
  SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);
  temp =SendDataPointor[4];
  SendDataPointor=SendDataPointor+8;
  if((temp&0x20)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
    SendDataPointor=SendDataPointor+4;
  }
  if((temp&0x10)!=0)
  {
    mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
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
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));
  SendDataPointor=SendDataPointor+temp*4+1;
  mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);
  *SendDataPointor = (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff)+1;
  SendDataPointor=SendDataPointor+6;
  *SendDataPointor = WRConfig->uartParameter[cmmdChanel].IssiStrength;
  SendDataPointor++;
  temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12;
  lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;
  nop();
  nop();
  if(pointerOfLDSW20deviceMap[temp].mapLenth>=(temp+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress))
  {
    mov_data((unsigned char *)(pointerOfLDSW20deviceMap[temp].mapPointer+sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress),SendDataPointor,lens);
    SendDataPointor=SendDataPointor+lens;
  }
  else
  {
    if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress)==0xffffffff)
    {   
      mov_data(&WRConfig->uartParameter[cmmdChanel].uartTimer_count,(unsigned char *)&WRConfig->UserTransArea.dataPayload,1);
      mov_data((unsigned char *)(pointerOfLDSW20deviceMap[temp].mapPointer+32),SendDataPointor,lens);
      SendDataPointor=SendDataPointor+lens;
    }else
    {
      return FALSE;
    }
  }
  nop();
  nop();
  lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
  WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;
  nop();
  Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );
  return TRUE;
}

/*******************************************************************************
*
*函 数：MakeWriteRsp( )
*功 能：使用扩展模块发送唤醒帧组包函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：true ，flase
*作 者：
*时 间：2018.12.21
*备 注：
*
********************************************************************************/
void MakeWriteRsp(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	unsigned short lens;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	SendDataPointor[4] =(SendDataPointor[4]&0x0f)|((RxdDataPointor[4]&0x0c0)>>2)|((RxdDataPointor[4]&0x030)<<2);//目标、源设备属性地址有效位交换
	SendDataPointor[4] |= DataDirectUp; //改变数据传输方向
	SendDataPointor[3]=(SendDataPointor[3]&0x0f)|(FRAMEOFRESP<<4);
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|(RxdDataPointor[5]&0x0f);
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//判断帧属性
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);//拷贝源设备群地址（4字节）
		SendDataPointor=SendDataPointor+4;//指针向后移动4位
	}
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);//拷贝源设备地址
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x80)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup,SendDataPointor,4);//拷贝群目标地址
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);//拷贝目标地址
		SendDataPointor=SendDataPointor+4;
	}
	nop();
	temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f0)>>4;//1
	mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb,SendDataPointor,(temp*4+1));
	SendDataPointor=SendDataPointor+temp*4+1;
	mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR,SendDataPointor,6);
	SendDataPointor=SendDataPointor+6;
	
	temp =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12;//0x07
	lens =sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x01ff;//0x0010

	*SendDataPointor++=0x01;
	
	lens =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;//末地址—首地址=长度
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =lens;//赋值长度
	
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], lens );//加上2个字节的CRC校检

	USART1_TxBuf(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0], (WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]+5));//串口数据上传
}

/*******************************************************************************
*
*函 数：SendCallToNoExtendboard( )
*功 能：使用扩展模块发送唤醒帧
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.21
*备 注：
*
********************************************************************************/
void SendCallToNoExtendboard(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	//if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[4]&0x010)!=0x00) //判断辅助模块使用选项是否从辅助模块发送
	//{
		//return;
	//}
	//mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
	//clrMemeryOfAlarm( WRConfig);		//清除告警记录
	//DoCallPackage(WRConfig,cmmdChanel);
	
  MakeWriteRsp(WRConfig,cmmdChanel);		//通过串口上传给读写器
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  clrMemeryOfAlarm( WRConfig);  //清楚标签盘点记录
  DoCallPackage(WRConfig,cmmdChanel);
}

/*******************************************************************************
*
*函 数：DoCallPackage( )
*功 能：唤醒包操作函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
void DoCallPackage(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned short lens;
	
	lens= (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0ff);
	mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],lens);
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]=lens;
	
	switch((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[5]&0x1f))		//判断唤醒帧指令域格式中的指令字
	{
		case 0x11:				//清点标签ID
		case 0x13:				//智能终端工作模式切换
			if(lens!=0x04)
			return;
		break;
		case 0x00:				//盘点
		case 0x01:				//通用唤醒
		case 0x10:
		case 0x12:				//单模基站清点标签ID
			if((lens>=0x10)&&(lens<=0x25))		//如果指令长度不为16位
			{
				mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[11],(unsigned char *)&WRConfig->DeviceChannel.timerOfAwake[0],4);	//拷贝唤醒时间
				mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[15],(unsigned char *)&WRConfig->DeviceChannel.timerOfAwake[1],4);
			
				if(cmmdChanel == 1)
				{
					mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],&WRConfig->uartParameter[0].uartTxdBuffer[3],lens);
					WRConfig->uartParameter[0].uartTxdBuffer[2] = lens;
				}
				sendawakepackageDone(WRConfig,0);				
			}
		break;
		
		case 0x14:		//点对点唤醒操作标签
			if(lens!=0x14)
			return;

			mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[11],(unsigned char *)&WRConfig->DeviceChannel.timerOfAwake[0],4);
			mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[15],(unsigned char *)&WRConfig->DeviceChannel.timerOfAwake[1],4);
			if(cmmdChanel == 1)
			{
				mov_data(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],&WRConfig->uartParameter[0].uartTxdBuffer[3],lens);
				WRConfig->uartParameter[0].uartTxdBuffer[2] = lens;
			}
			
			sendawakepackageDone(WRConfig,0);

		break;
		case 0x15:				//绑定基站地址
		break;
		case 0x16:				//改心跳
		break;
		default:
		break;
	}
}
/************************************
*************************************/
void clrMemeryOfAlarm(pwNodeCondig WRConfig)
{
	unsigned long i;
	unsigned char *sdata;
	sdata =(unsigned char *)&WRConfig->MaprecordOfAlarm;
	//tsty=sizeof(WRConfig->MaprecordOfAlarm);
	for(i=0;i<sizeof(WRConfig->MaprecordOfAlarm);i++)
	{
		sdata[i]=0;
	}
}
/************************************
*************************************/

unsigned char MakeTransFrameOf1UniversalforTEST(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],2);
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|((RxdDataPointor[7]&0xe0)>>5);
	SendDataPointor[3]=((SendDataPointor[3]&0x0f)| (FRAMEOFTEST<<4));
	SendDataPointor[4]=((SendDataPointor[4]&0x0f)|(0x05<<4));
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+5;
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f)],SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff)<16)
	{
		mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[1],SendDataPointor,2);
		SendDataPointor+=2;
		*SendDataPointor =0x00;
		SendDataPointor++;
		*SendDataPointor =0x00;
		SendDataPointor++;
	}else
	{
		mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[5],SendDataPointor,2);
		SendDataPointor+=2;
		*SendDataPointor =0x00;
		SendDataPointor++;
		*SendDataPointor =(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff);
		SendDataPointor++;
		mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],SendDataPointor,\
		((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff)));
		SendDataPointor+=((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff));
	}
	WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] =SendDataPointor-&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0]-3;
	
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);
	
	return TRUE;
}



unsigned char SendRfpackOptionFortag(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay)
{
	unsigned char txCount=0;
	
	mov_data(sData,&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],(sData[2]+5));
	do{		
		if(Ldsw20RfpackSend(WRConfig,cmmdChanel)==TRUE)
		{
			//if(((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3]&0xf0)>>4)!=FRAMEOFTEST)
			//{
				if(((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[5]&0x80)>>7)!=0)//判断是否需要返回ACK
				{
					return TRUE;
				}
			//}
			
			//if(((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[5]&0x80)>>7))
			//{
				//return TRUE;
			//}
			if((Ldsw20ACKPackReci(WRConfig,cmmdChanel,timedelay) == TRUE))
			{
				nop();
				return TRUE;
			}
		}
		delay_ms(10);
		//R_delayCnt=Randowdata();
		//nop();
		//timer_delay(((R_delayCnt+100)*5));
		txCount++;
	}while(txCount<retry);
	return FALSE;
}

/*******************************************************************************
*
*函 数：sendDownToNextDevice( )
*功 能：发送下行数据到设备
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从
*       哪个通道进入的，通道取值0-5)
*输 出：TRUE,帧获取成功,FALSE,帧错误
*作 者：WGS
*时 间：2018.12.11
*备 注：
*
********************************************************************************/
unsigned char LDSW_BoardcastFrameTest(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,*RxdDataPointor,temp;
  
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  
	SendDataPointor[0]=0x55;
	SendDataPointor[1]=0xaa;
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2],WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+1);
	SendDataPointor[3] &= 0xF0;
	SendDataPointor[5] =(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);     //源设备属性变化，目标设备属性变为源设备属性
	SendDataPointor[4] &= ~(0x0C);		//获取地址信息有效位
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;	
	if((temp&0x20)!=0)//目标群地址变化
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceGroup,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
  
	if((temp&0x10)!=0)
	{
		memset(SendDataPointor,0,4);
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
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]);

	if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress == 0xfffffff1)
	{
		// MakeTransFrameOf1UniversalforTEST(WRConfig,cmmdChanel);
	}
	
	if((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3]&0x0f)!= SMARTNODE)//如果目标地址不是智能终端
	{
		if(SendRfpackOption(WRConfig,&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],0,3,100) == TRUE)
		{
			nop();
		}
	}
	else
	{
		//while(1)
		//{
			//
			if(SendRfpackOptionFortag(WRConfig,&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],0,3,100) == TRUE)
			{
				nop();
			}
		//	 delay_ms(300);
		 //}
	}
	cpu_irq_enable();
	//WRConfig->DeviceChannel.channel_temp=1;
	//radio_ini(WRConfig,0);
	//RxdRF6936(cmmdChanel);
	
	return TRUE;
}

/*******************************************************************************
*
*函 数：sendDownToNextDevice( )
*功 能：读数据发送下行函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：对应的帧类型,FALSE：检查错误
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char sendDownToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned char *RxdDataPointor,temp=0;
      
    unsigned short ChecktableTemp=0;
    
    
    RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
    mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
    //lens =ChainJTable[temp];
    ChecktableTemp= ((RxdDataPointor[3]&0x0f)<<4)|((RxdDataPointor[7]&0xe0)>>5);//由目标设备属性和采集终端设备属性
    ChecktableTemp=((((unsigned short)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb)&0x0f0)<<4)|ChecktableTemp;
    temp=checkDevChain(ChecktableTemp);
    
    switch(temp)
    {
        case 0x00://单模读写器
        case 0x01://双模模读写器
        case 0x02://基站
        case 0x03:
        case 0x05:
        case 12:
        case 23:
        case 25:
        case 28:
        case 31:
        case 32:
          /*判断如果是盘点帧*/
          if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0F000)>>12)==FRAMEOFINVENT)
          {
            WRConfig->RfFrameDatCtrls.TimerEn = 0;
            SendCallToNoExtendboard(WRConfig,cmmdChanel);
            return TRUE;
          }
          if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->OffsetofAddress == 0xfffffff1)
            LDSW_BoardcastFrameTest( WRConfig,  cmmdChanel);
          else
            sendBackForRddataNews(WRConfig,cmmdChanel);//指令已到最后一级		
        break;
        case 0x04:
        break;
        case 0x06:
        break;
        case 0x07:
        break;
        case 0x08:
        break;
        case 0x09:
            if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12)==FRAMEOFINVENT)
            {
              WRConfig->RfFrameDatCtrls.TimerEn = 0;
              SendCallToNoExtendboard(WRConfig,cmmdChanel);
              return TRUE;
            }
        break;
        case 10:
          nop();
          MakeTransFrameOf1Universal(WRConfig,cmmdChanel);
          nop();
        break;
        case 11:
          if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0xf000)>>12)==mUserTransArea)
          {
            mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],WRConfig->uartParameter[cmmdChanel].uartTxdtemp,\
              (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x1ff));
            nop();
            WRConfig->RfFrameDatCtrls.TimerEn = 0;
            WRConfig->RfFrameDatCtrls.senddatatransFlg = 1;
          }else{
            MakeUniversalFrame(WRConfig,cmmdChanel);
          }
          break;
        case 13:
          break;
        case 14:
          break;
        case 15:
          break;
        case 16:
          break;
        case 17:
          break;
        case 18:
          break;
        case 19:
          break;
        case 20:
          break;
        case 21:
        case 22:
        case 24:
        case 26:
          break;
        case 27:
          break;
        case 29:
        case 40:
          if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0f000)>>12)==FRAMEOFINVENT)
          {
            WRConfig->RfFrameDatCtrls.TimerEn = 0;
            SendCallToNoExtendboard(WRConfig,cmmdChanel);
            return TRUE;
          }
          break;
        case 30:
          break;
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
          nop();
          nop();
          MakeTransFrameOfmultiUniversalForBaseStation(WRConfig,cmmdChanel,temp);//用于基站集中管理
          nop();
          nop();
          break;
        case  255:
          break;
        default:
          break;
        }
    return TRUE;
}

/*******************************************************************************
*
*函 数：sendWdDownToNextDevice( )
*功 能：写数据发送下行函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：发送成功,FALSE：发送失败
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char sendWdDownToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned char *RxdDataPointor,temp=0;
  
    unsigned short ChecktableTemp=0;
  
  
    RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0]; 
    mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
    ChecktableTemp= ((RxdDataPointor[3]&0x0f)<<4)|((RxdDataPointor[7]&0xe0)>>5);
    ChecktableTemp=((((unsigned short)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb)&0x0f0)<<4)|ChecktableTemp;
    temp=checkDevChain(ChecktableTemp);
  
    switch(temp)
    {
        case 0x00://单模读写器
        case 0x01://双模模读写器
        case 0x02://基站
        case   40:
        case   11:
            SendWritedataToMap(WRConfig,cmmdChanel);;
        break;  
        case 0x03:
        break;    
        case 0x04:
        break;     
        case 0x05:
        break;     
        case 0x06:
        break;     
        case 0x07:
        break;    
        case 0x08:
        case 0x09:
        case 0x0a:  
            //MakeTransFrameOf1Universal(WRConfig,cmmdChanel);
        nop();
        break;  
        case   12:
        break;   
        case   13:  
        case   14:
        case   15: 
        case   16://一级链路，基站操作
    
        MakeTransFrameOf1Universal(WRConfig,cmmdChanel);
    
        break;     
        case   17:
        break;    
        case   18:
        break;    
        case   19:
        break;  
        case   20:
        break;  
        case   21:
        case   22:
        case   23:
        case   24:
        case   25:
        case   26:
        break; 
        case   27:
        case   28:
        case   29:
        case   30:
        case   31:
        case   32: 
          if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0xf0)>>4)!=\
            (sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb&0x0f)){
              MakeTransFrameOf1Universal(WRConfig,cmmdChanel);
            }else
            {
              SendWritedataToMap(WRConfig,cmmdChanel);
            }
        break; 
        case  33:
        case  34:
        case  35:
        case  36:  
        case  37: 
        case  38: 
        case  39:  
            MakeTransFrameOfmultiUniversalForBaseStation(WRConfig,cmmdChanel,temp); //用于基站集中管理 
        break;
        case  255:
        break;
        default:
        break;        
    }
    return TRUE;
}



unsigned char MakeDataReturnFrameForTest(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char *SendDataPointor,temp;
	SendDataPointor =&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0];
	
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],\
	WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+5);
	SendDataPointor[3] = ((SendDataPointor[3]&0xf0)|BASESTATION);
	SendDataPointor[4] = ((SendDataPointor[4]&0xfe)|DataDirectUp);
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+5;
	if((temp&0x10)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.SourceAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	if((temp&0x40)!=0)
	{
		mov_data((unsigned char *)sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress,SendDataPointor,4);
		SendDataPointor=SendDataPointor+4;
	}
	SendDataPointor+=2;
	*SendDataPointor = WRConfig->uartParameter[cmmdChanel].IssiStrength;
	SendDataPointor++;
	if(WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] == 0x0e){
		nop();
	}else
	{
		SendDataPointor++;
		mov_data((unsigned char *)&WRConfig->AttrOfDevice.DeviceID,SendDataPointor,4);
	}
	Calculate_Crc16(&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3], WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2] );
	nop();
	return TRUE;
}

/*******************************************************************************
*
*函 数：sendUpToNextDevice( )
*功 能：数据发送上行函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：对应的帧类型,FALSE：检查错误
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char sendUpToNextDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  unsigned char *RxdDataPointor,temp=0;

  unsigned short ChecktableTemp=0;
  
  RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0];
  mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3],5);
  ChecktableTemp= ((RxdDataPointor[3]&0x0f)<<4)|((RxdDataPointor[7]&0xe0)>>5);
  ChecktableTemp=((((unsigned short)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainNumb)&0x0f0)<<4)|ChecktableTemp;
  temp=checkDevChain(ChecktableTemp);
  
  switch(temp)
  {
  case 0x00:	//单模读写器
  case 0x01:	//双模模读写器
  case 0x02:	//基站
    sendBackForRddataNews(WRConfig,cmmdChanel);
    break;  
  case 0x03:
    break;    
  case 0x04:
    break;     
  case 0x05:
    break;     
  case 0x06:
    break;     
  case 0x07:
    break;    
  case 0x08:
  case 0x09:
  case   10:	
	WRConfig->uartParameter[0].uartTxdBuffer[0]=0X55;
	WRConfig->uartParameter[0].uartTxdBuffer[1]=0XAA;
	Calculate_Crc16(&WRConfig->uartParameter[0].uartTxdBuffer[3], WRConfig->uartParameter[0].uartTxdBuffer[2]);
	USART1_TxBuf(&WRConfig->uartParameter[0].uartTxdBuffer[0], (WRConfig->uartParameter[0].uartTxdBuffer[2]+5));

    //MakeTransFrameOfWRiterUniversal(WRConfig,cmmdChanel);
    nop();
    break;  
  case   11:
    break;   
  case   12:
    break;   
  case   13:   
  case   14:
  case   15:  
  case   16://一级链路，基站操作
    MakeTransFrameOfReturnNiversal(WRConfig,cmmdChanel);
    USART1_TxBuf(&WRConfig->uartParameter[1].uartTxdBuffer[0], (WRConfig->uartParameter[1].uartTxdBuffer[2]+5));
    nop();
    break;     
  case   17:
    break;    
  case   18:
    break;    
  case   19:
    break;  
  case  20:
    break;  
  case   21:
  case   22:
  case   23:
  case   24:
  case   25:
  case   26:  
    break; 
  case   27:
  case   28:
  case   29:
  case   30:
  case   31:
  case   32:
    MakeTransFrameOfReturnNiversal(WRConfig,cmmdChanel);
    break; 
  case   33:  
  case   34:
  case   35:
  case   36:   
  case   37: 
  case   38: 
  case   39: 
    nop();
    nop();
    MakeTransFrameOfmultiUniversalForBaseStation(WRConfig,cmmdChanel,temp);//用于基站集中管理
    nop();
    nop();
  case  255:
    break;
  default:
    break;     
  }
  return TRUE; 
}

/*******************************************
*Name:jump_bootload
*Description:跳转到bootload启动区
*Input:设备参数、通道号
*Output:NULL
*Author:CODER_XINGUANG
*Date:2017/02/21
********************************************/
void jump_bootload(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  //uint32_t SpInitVal;
  //uint32_t JumpAddr; 
  //void(*pFun)(void);
  //pParamsOfTag addr;
  //MSC_Init();                                                 //初始化MSC，并使能AUXHFRCO
  //sBootFlashData.channel=96;                                  //在线升级通道96
  //sBootFlashData.deviceId=WriterConfig.AttrOfDevice.DeviceID; //当前期间ID
  //sBootFlashData.flag=1;                                      //标志0
  //sBootFlashData.groupId=WriterConfig.AttrOfDevice.GroupId;   //组ID
  //sBootFlashData.jumpAddr=G210_APP_ADDR;                      //APP起始地址
  //sBootFlashData.mode= 2;                                     //升级模式
  //sBootFlashData.paramAddr=G210_PARAMS_FLASH_ADDR;            //存储信息在Flash中的应用
  //sBootFlashData.pn=WriterConfig.DeviceChannel.PN[0];         //PN码
  //sBootFlashData.power=WriterConfig.DeviceChannel.Pow[0];     //功率值
  //sBootFlashData.type= 0x04;                                  //定位器
  //sBootFlashData.updateGroupId = 100;//*((unsigned long *)&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[16]);//源组
  //sBootFlashData.updateId=*((unsigned long *)&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[20]);       //源ID
  //sBootFlashData.ver = 0x02;                                                                               //版本号
  ////关闭总中断
  //__disable_irq();
  //addr=&sBootFlashData;
  //if(MSC_ErasePage((uint32_t *)G210_PARAMS_FLASH_ADDR) == mscReturnOk)
  //{
    //MSC_WriteWord((uint32_t *)G210_PARAMS_FLASH_ADDR,addr,sizeof(sBootFlashData));
  //}
  //MSC_Deinit();
  //__enable_irq();
  //BOOT_app();
}


/*******************************************************************************
*
*函 数：excuteLDSW20( )
*功 能：协议执行
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：执行成功,FALSE：检查错误
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char excuteLDSW20(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{		
	mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],(WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+3));
	
    switch(checkLdsw20(WRConfig,cmmdChanel))
	{
      case 0x01:
        switch(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->CmdOfATTR&0x0e00)>>9))		//判断指令属性
        {
            case CmdAttrOfRD:	//读命令
            if((WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[4]&0x01)==DataDirectDown)	//判断数据方向
            {
                sendDownToNextDevice(WRConfig,cmmdChanel);		//读数据发送下行
            }
            else
            {
                sendUpToNextDevice(WRConfig,cmmdChanel);		//读数据发送上行
            }
            break;
            
            case CmdAttrOfWD:	//写命令
            if((WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[4]&0x01)==DataDirectDown)
            {	
                sendWdDownToNextDevice(WRConfig,cmmdChanel);	//写数据发送下行
            }
            else
            {
                sendUpToNextDevice(WRConfig,cmmdChanel);		//写数据发送上行
            }
            break;             
        
            case CmdAttrOfCLRbuffer:								//清缓存
            break;             
            
            case CmdAttrOfRDRbuffer:								//读缓存
            break;              
            
            case CmdAttrOfRStart:
                WRConfig->RfFrameDatCtrls.TimerEn = 0;
                jump_bootload(WRConfig,cmmdChanel);					//跳转到升级程序
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
			//MakeDataReturnFrameForTest(WRConfig,cmmdChanel);
		break;
		
		default:
		return FALSE;
	}
    return TRUE;
}
