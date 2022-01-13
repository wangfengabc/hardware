#include <at86rf233.h>
#include <string.h>
#include "asf.h"
#include "trx_access.h"
#include "ldsw20rf.h"
#include "ldsw20.h"
#include "io_define.h"
#include "device.h"
#include "phy.h"
#include "wdt.h"


#define LS_CHANNEL_OFFSET           0x00

extern struct tcc_module tcc_instance;

pwtimer TimerSerial,TimerMaxSerial,TimerSerialTemp;
unsigned long TimerSerialData;

void RxdRF6936(unsigned char cmmdChanel)
{
	phyWriteRegister(IRQ_MASK_REG,(1 << TRX_END));
	phyTrxSetState(TRX_CMD_RX_ON);
}

void RxModuleOfACK(unsigned char cmmdChanel)
{
	phyWriteRegister(IRQ_MASK_REG,0);
	phyTrxSetState(TRX_CMD_RX_ON);
}

void SelectChanel(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	switch(WRConfig->DeviceChannel.channel_temp)
	{
		case 0x01:                                            //设置1通道
		if((WRConfig->DeviceChannel.T_vaild & WRConfig->DeviceChannel.T_En & 0x0001)==0x01)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T0+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0002)==0x02)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T1+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0004)==0x04)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0008)==0x08)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F1+LS_CHANNEL_OFFSET;
		}
		break;

		case 0x02:
		//WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F2+LS_CHANNEL_OFFSET;
		if((WRConfig->DeviceChannel.T_vaild & WRConfig->DeviceChannel.T_En & 0x0001)==0x01)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T0+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0002)==0x02)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T1+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0004)==0x04)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0008)==0x08)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F2+LS_CHANNEL_OFFSET;
		}		
		break;

		case 0x03:
		WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F3+LS_CHANNEL_OFFSET;
		break;

		case 0x04:
		WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F4+LS_CHANNEL_OFFSET;
		break;

		case 0x05:
		WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F5+LS_CHANNEL_OFFSET;
		break;

		case 0x06:
		WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F6+LS_CHANNEL_OFFSET;
		break;

		case 0x07:
		if((WRConfig->DeviceChannel.T_vaild & WRConfig->DeviceChannel.T_En & 0x0001)==0x01)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T0+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0002)==0x02)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T1+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0004)==0x04)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0008)==0x08)
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.T3+LS_CHANNEL_OFFSET;
		}
		else
		{
			WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F7+LS_CHANNEL_OFFSET;
		}
		break;

		default:
		WRConfig->DeviceChannel.ChannelCode_temp= WRConfig->DeviceChannel.F0+LS_CHANNEL_OFFSET;
		break;
	}
	PHY_SetChannel(WRConfig->DeviceChannel.ChannelCode_temp);
}



unsigned char SendRfpackOption(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay)
{
    unsigned char txcount = 0;
    do{
        if(Ldsw20RfpackSend(WRConfig,cmmdChanel)==TRUE)
        {
            if(((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[5]&0x80)>>7))
            {
                return TRUE;
            }
            if(Ldsw20ACKPackReci(WRConfig,cmmdChanel,0) == TRUE)
            {
                //if(isValidAckForMe(WRConfig,cmmdChanel) == TRUE)
                //{
                    return TRUE;
                //}
            }
        }
        txcount++;
       delay_ms(20);
    }while(txcount<retry);
    return FALSE;
}


void SetbTimerOfRatio(pwNodeCondig WRConfig,unsigned char Rfchannel)
{
    switch(WRConfig->DeviceChannel.DataRat[Rfchannel])
    {
    case 0x00: //1M bps
    case 0x01: //250kbps    32-chip 8DR
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =100;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=130;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =200;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =0;    
        break;
    case 0x05: //125kbps     64-chip 8DR
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =100;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=260;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =200;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =0; 
        break;
    case 0x02: //62.5kbps    32-chip DDR
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =560;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=520;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =400;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =2;      
        break;
    case 0x06://31.25kbps    64-chip DDR
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =1120;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=1040;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =800; 
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =4;
        break;
    case 0x07://15.625kbps   64-chip SDR
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =2240;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=2080;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =1600;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =8;
        break;
    default:
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempComp =280;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].GetAckDls=260;
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempOver =200; 
        WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].tempWait =2;       //10ms 
        break;
    }
    WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].backGround =16;//???????????
    WRConfig->AttrOfDevice.TimerOfRatio[Rfchannel].sampleTimes =12;
}

void Getchannel_timer(pwNodeCondig WRConfig)
{
    SetbTimerOfRatio(WRConfig,0);
    SetbTimerOfRatio(WRConfig,1);
}

//unsigned char isValidAckForMe(pwNodeCondig WRConfig,unsigned char cmmdChanel)
//{
    //unsigned long *ID;
    //unsigned char *RxdDataPointor;
    //RxdDataPointor=&WRConfig->uartParameter[cmmdChanel].uartRxdtemp[0];
    //ID = (unsigned long *)&RxdDataPointor[4];
    //if((*ID == WRConfig->AttrOfDevice.DeviceID )&& ((WRConfig->uartParameter[cmmdChanel].uartRxdtemp[3]&0xf0)>>4)==FRAMEOFACK)
    //{
        //mov_data((unsigned char*)&RxdDataPointor[8],(unsigned char*)&WRConfig->AttrOfDevice.RspTime,4);
        ////WRConfig->IrqCng.timeMargin = ((RxdDataPointor[8]&0xf0)>>4)*2000;
        //WRConfig->IrqCng.waitMessageForCount=0;
        //WRConfig->IrqCng.waitSleepTime=((unsigned long)(RxdDataPointor[8]&0x0f))*500;
        //WRConfig->IrqCng.SleepDelayFlg =1;
        //WRConfig->IrqCng.timerOfCollison = WRConfig->DeviceChannel.AsleepConst;
        //return TRUE;
    //}
    //return FALSE;
//}

/*******************************************************************************
*
*函 数：IssiAverage( )
*功 能：对碰撞中的信号强度计算平均值
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：对应的帧类型,FALSE：检查错误
*作 者：
*时 间：2018.12.20
*备 注：被judge_collision调用
*
********************************************************************************/
unsigned char IssiAverage(unsigned char *s,unsigned char lens)
{
    unsigned char i;
    unsigned int Sum;
    Sum =0;
    for(i =0;i<lens;i++)
    {
        Sum = Sum + *s++;
    }
    i = Sum/lens;
    return i;
}
/*******************************************************************************
*
*函 数：JudegeWorkCh( )
*功 能：判断并设置工作通道
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：没有碰撞
*作 者：
*时 间：2018.12.20
*备 注：根据设备属性选择射频通道channel_temp
*
********************************************************************************/
unsigned char JudegeWorkCh(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    switch((WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[3]&0x0f))
    {
    case SMARTNODE:
        WRConfig->DeviceChannel.channel_temp = 0;
        break;
    case SWRITER:
        WRConfig->DeviceChannel.channel_temp = 1;
        break;
    case LOCATOR:
        WRConfig->DeviceChannel.channel_temp = 4;
        break;
    case DWRITER:
        WRConfig->DeviceChannel.channel_temp = 1;
        break;
    case RELAYER://????
        WRConfig->DeviceChannel.channel_temp = 2;
        break;
    case BASESTATION://???
        WRConfig->DeviceChannel.channel_temp = 2;
        break;
    case HANDLE://??????
      WRConfig->DeviceChannel.channel_temp = 1;
      break;
    default:
        WRConfig->DeviceChannel.channel_temp = 1;
        //return FALSE;
    }
    return TRUE;
}

/*******************************************************************************
*
*函 数：judge_collision( )
*功 能：判断碰撞
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：没有碰撞,FALSE：有碰撞
*作 者：
*时 间：2018.12.20
*备 注：周围的信号强度
*
********************************************************************************/
unsigned char judge_collision(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned int  i,j,temp=0;
    unsigned char  TestBuff[4],pointer;
	
	phyTrxSetState(TRX_CMD_RX_ON);
    delay_us(120);
    for(i =0;i<4;i++)
    {
        if(pointer>3)
          pointer =0;
        delay_us(50);
        TestBuff[pointer++] = ((phyReadRegister(PHY_RSSI_REG) >> RSSI) & 0x1F);
    }

    for(j=0;j<WRConfig->AttrOfDevice.TimerOfRatio[cmmdChanel].sampleTimes;j++)
    {
		phyTrxSetState(TRX_CMD_RX_ON);
        delay_us(10);
        if(pointer>3)
            pointer =0;
        TestBuff[pointer++] = ((phyReadRegister(PHY_RSSI_REG) >> RSSI) & 0x1F);
        if(IssiAverage(TestBuff, 4)<WRConfig->AttrOfDevice.TimerOfRatio[cmmdChanel].backGround)
        {
            return TRUE;
        }
    }
	
    if(j==WRConfig->AttrOfDevice.TimerOfRatio[cmmdChanel].sampleTimes)
    {
        temp=TestBuff[0]*10;
        delay_us(temp);
    }
    //WRConfig->IrqCng.RssiOfcollisonStrenth=(TestBuff[3]*10);
    return FALSE;
}

/*******************************************************************************
*
*函 数：Ldsw20ACkPackage( )
*功 能：ACK帧组包
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.26
*备 注：
*
********************************************************************************/
void Ldsw20ACkPackage(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned char AddrTemp;
	unsigned short *tSdat;
	
    WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[0] =0x55;
    WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[1] =0xaa;
    WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[2] =0x07;
    WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[3] =(FRAMEOFACK<<4)|WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[5]&0x0f;
    AddrTemp=((WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[4]&0xf0)>>4);
    switch(AddrTemp)
    {
        case 0x05:
            memblockCopy(&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[4],&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[12],4);
            WRConfig->uartParameter[cmmdChanel].uartTxdPointer=16;
            break;
        case 0x07:
            memblockCopy(&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[4],&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[16],4);
            WRConfig->uartParameter[cmmdChanel].uartTxdPointer=20;
            break;
        case 0x0f:
            memblockCopy(&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[4],&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[20],4);
            break;
        default:
            break;
    }
	tSdat=(unsigned short *)&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[8];
	*tSdat=WRConfig->AttrOfDevice.RspTime;	
    //mov_data((unsigned char*)sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd,&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[8],2);
    mov_data(&WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],\
    WRConfig->uartParameter[cmmdChanel].ackInfo.ackToken[2]+3);
}

/******************???**************************
Function:     timerDlesOfsend
Description:  ??????
Input:        pwNodeCondig WRConfig        ????????
unsigned char cmmdChanel     ????????
Output:   
Others:      1.2007,6,5 ????
author:      ?????
*************************************************/
//void timerDlesOfsend(pwNodeCondig WRConfig,unsigned char cmmdChanel)
//{
  //if(WriterConfig.RfFrameDatCtrls.TimerEn==1)
  //{
	  //WriterConfig.RfFrameDatCtrls.TimerCnt++;
	  //if(WriterConfig.RfFrameDatCtrls.TimerCnt > 15)
	  //{
		  //WriterConfig.RfFrameDatCtrls.TimerCnt = 0;
		  //WriterConfig.RfFrameDatCtrls.TimerEn = 0;
		  //WriterConfig.RfFrameDatCtrls.sendFlg = 1;
	  //}
  //}
  //if(1 == WriterConfig.RfFrameDatCtrls.sendFlg)
  //{
	  //WriterConfig.RfFrameDatCtrls.sendFlg = 0;
	  //SendRfpackOption(WRConfig,WRConfig->uartParameter[cmmdChanel].uartTxdBuffer,cmmdChanel,3,2000);
//
	  //WRConfig->DeviceChannel.channel_temp=2;//射频通道及6936复位
	  //radio_ini(WRConfig,cmmdChanel);
	  //RxdRF6936(cmmdChanel);
	  //__enable_irq();
  //}
//}

/*******************************************************************************
*
*函 数：CRCis_Valid( )
*功 能：RF射频芯片硬件CRC判断
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：硬件接收正确,FALSE：接受数据失败
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char CRCis_Valid(void)
{
	unsigned char TRstatus;
	
	TRstatus =  phyReadRegister(PHY_RSSI_REG);
	if (TRstatus&(1 << RX_CRC_VALID))
	{
		return TRUE;
	}
	
	return false;
}

/*******************************************************************************
*
*函 数：Ldsw20RfPackReci( )
*功 能：中断接收数据函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：接收成功,FALSE：接受失败
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/

unsigned char Ldsw20RfPackReci(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned char *adata;
    unsigned short nAccum;
    unsigned char regStatus;
    unsigned char reciLength;
	
	regStatus = phyReadRegister(IRQ_STATUS_REG);
	if((regStatus & (1 << TRX_END)) != 0)  
	{
		if(CRCis_Valid()==false)
		{
			return false;
		} 
		
		trx_frame_read(&reciLength, 1);
		if((reciLength > 127) || (reciLength < 8))
		{
			WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;
			radio_ini(WRConfig,cmmdChanel);        
 			RxdRF6936(cmmdChanel);
			return FALSE;
		}
			
		WRConfig->uartParameter[cmmdChanel].IssiStrength = (int8_t)(phyReadRegister(PHY_ED_LEVEL_REG)) ;
		adata = &WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2];
		trx_frame_read(adata, reciLength-1);
		WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2] = reciLength-4;
		   
	}
	else
	{
		WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;
		radio_ini(WRConfig,cmmdChanel);
		RxdRF6936(cmmdChanel);
		return FALSE;
	}
	

	 
    nAccum = CRC_16(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],(reciLength-2));
    if(nAccum!=0x00)
    {
	    WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;                      
	    radio_ini(WRConfig,cmmdChanel);                              
	    RxdRF6936(cmmdChanel);
	    return FALSE;
    }
    sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl=(pLdsw20FrameCtl)(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3]);
    if((GetPointerOfCmd(WRConfig, cmmdChanel)==FALSE)||(FunctionGetAttrOfDestDev(cmmdChanel)!=devOfDwritor)||(CheckPassward(WRConfig,cmmdChanel)==FALSE))
    {
  	    WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;//?????????936????
  	    radio_ini(WRConfig,cmmdChanel);
  	    RxdRF6936(cmmdChanel);
  	    return FALSE;
    }   
	
    if(FunctionGetAttrBROADCAST(cmmdChanel)!=BROADCAST)		//判断是否是广播
    {
	    if((FunctionGetAttrDESTADRESSVALID(cmmdChanel)==TRUE) && (Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress)==WRConfig->AttrOfDevice.DeviceID))
	    {
		    if((FunctionGetAttrDESTGROUPVALID(cmmdChanel)==TRUE))
		    {
			    if((Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup))!=WRConfig->AttrOfDevice.GroupId)
			    {
				    WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;                      
				    radio_ini(WRConfig,cmmdChanel);                   
				    RxdRF6936(cmmdChanel);
				    return FALSE;
			    }
		    }
            
			Ldsw20ACKPackSend(WRConfig,cmmdChanel,2000);			/*中断收到数据发送ACK*/
			WRConfig->uartParameter[cmmdChanel].uartStatus= 4;
								
			//switch(DealdeDataOfInventory(WRConfig,cmmdChanel))   
			//{
				//case  0x01://保存铁电无返回
				//case  0x03://保存无返回
				//case  0x0e://错误
					//break;
				//case  0x02://返回
				//case  0x0a:
					//WRConfig->uartParameter[cmmdChanel].uartStatus= 4;
				//#if deviceOfTYPE==deviceOfDwritor
				////WRConfig->RfFrameDatCtrls.TimerEn=1;
				//#endif
					//break;
				//default: 
					//break;
			//}	  
		    //WriterConfig.RfFrameDatCtrls.TimerCnt = 0;
		    //WriterConfig.RfFrameDatCtrls.TimerEn = 1;
		    ////Ldsw20ACKPackSend(WRConfig,cmmdChanel,2000);
		    //timerCnt=0;
		    //WRConfig->uartParameter[cmmdChanel].uartStatus= 4;
            
			WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;
			radio_ini(WRConfig,cmmdChanel);
			RxdRF6936(cmmdChanel);
		    return TRUE;
	    }
    }
    else
    {
	    if(FunctionGetAttrFRAME(cmmdChanel)==FRAMEOFLOCA)
	    {

	    }
    }
    WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;
    radio_ini(WRConfig,cmmdChanel);
    RxdRF6936(cmmdChanel);
    return FALSE;
}
/*******************************************************************************
*
*函 数：Ldsw20ACKPackReci( )
*功 能：接收ack
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：接收成功,FALSE：接受失败
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
unsigned char Ldsw20ACKPackReci(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay)
{
    unsigned char *aData;
    unsigned char status;
    unsigned char reciLength=0;
	unsigned long disptemp;
	
    WRConfig->DeviceChannel.channel_temp = 5;
    SelectChanel(WRConfig,cmmdChanel);
    RxModuleOfACK(cmmdChanel);
    disptemp = (2+(WRConfig->AttrOfDevice.TimerOfRatio[cmmdChanel].tempWait));
	delay_ms(disptemp);
    status = phyReadRegister(IRQ_STATUS_REG);
    if((status&(1<<TRX_END)) == 0x00)
    {
        nop();
        return FALSE;
    }
    trx_frame_read(&reciLength, 1);
    if((reciLength>17)||(reciLength<5))
    {
        WRConfig->DeviceChannel.channel_temp = 0;
        radio_ini(WRConfig,cmmdChanel);
        RxdRF6936(cmmdChanel);
        return FALSE;
    }
    aData = &WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2];	
	trx_frame_read(aData,reciLength-1);		//去掉第一次SPI读的一个字节的长度
	WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2]=(reciLength-2);//去掉RF233发送数据自动加上的CRC
	//mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2],&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3],WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]);
    if(((WRConfig->uartParameter[cmmdChanel].uartRxdtemp[3]&0xf0)>>4)!= FRAMEOFACK)//判断收到的数据是否是ACK帧
    {
		WRConfig->DeviceChannel.channel_temp = 0;
		radio_ini(WRConfig,cmmdChanel);
		RxdRF6936(cmmdChanel);
		return FALSE;
    }
	
    return TRUE;
}
/*******************************************************************************
*
*函 数：Ldsw20ACKPackSend( )
*功 能：发送ACK数据
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：TRUE：发送成功,FALSE：发送失败
*作 者：
*时 间：2018.12.11
*备 注：ACK返回专用channel通道为5
*
********************************************************************************/
unsigned char Ldsw20ACKPackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned short timedelay)
{
    unsigned char length;
    unsigned char status;
	
    Ldsw20ACkPackage(WRConfig,cmmdChanel);
    WRConfig->DeviceChannel.channel_temp=5;
	
    SelectChanel(WRConfig,cmmdChanel);
	length=WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]+2;

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
*函 数：Ldsw20RfpackSend( )
*功 能：发送数据
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：判断通道和碰撞
*
********************************************************************************/
unsigned char Ldsw20RfpackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
    unsigned char status,length;
	
    if(JudegeWorkCh(WRConfig,cmmdChanel)==FALSE)
    {
        return  FALSE;
    }
    radio_ini(WRConfig,cmmdChanel);
	
    if(judge_collision(WRConfig,cmmdChanel)== TRUE)
    {	
		length=WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[2]+2;
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
    return FALSE;
}


void setRfPowerOfDevice(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0001)==0x01)    //T0
	{
		PHY_SetTxPower(WRConfig->DeviceChannel.Pow[0]);
		PHY_SetRxSensitivity(WRConfig->DeviceChannel.Reci[0]);
		PHY_SetDataRate(WRConfig->DeviceChannel.DataRat[0]);
		PHY_SetSFD_Value(WRConfig->DeviceChannel.SFD_Value[0]);
	}
	else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0002)==0x02)//T1
	{
		PHY_SetTxPower(WRConfig->DeviceChannel.Pow[1]);
		PHY_SetRxSensitivity(WRConfig->DeviceChannel.Reci[1]);
		PHY_SetDataRate(WRConfig->DeviceChannel.DataRat[1]);
		PHY_SetSFD_Value(WRConfig->DeviceChannel.SFD_Value[1]);
	}
	else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0004)==0x04)//T2
	{
		PHY_SetTxPower(WRConfig->DeviceChannel.Pow[2]);
		PHY_SetRxSensitivity(WRConfig->DeviceChannel.Reci[2]);
		PHY_SetDataRate(WRConfig->DeviceChannel.DataRat[2]);
		PHY_SetSFD_Value(WRConfig->DeviceChannel.SFD_Value[2]);
	}
	else if((WRConfig->DeviceChannel.T_vaild&WRConfig->DeviceChannel.T_En&0x0008)==0x08)//T3
	{
		PHY_SetTxPower(WRConfig->DeviceChannel.Pow[3]);
		PHY_SetRxSensitivity(WRConfig->DeviceChannel.Reci[3]);
		PHY_SetDataRate(WRConfig->DeviceChannel.DataRat[3]);
		PHY_SetSFD_Value(WRConfig->DeviceChannel.SFD_Value[3]);
	}
	else     //不分组
	{
		PHY_SetTxPower(WRConfig->DeviceChannel.Pow[0]);
		PHY_SetRxSensitivity(WRConfig->DeviceChannel.Reci[0]);
		PHY_SetDataRate(WRConfig->DeviceChannel.DataRat[0]);
		PHY_SetSFD_Value(WRConfig->DeviceChannel.SFD_Value[0]);
	}
}


/*******************************************************************************
*
*函 数：SendCallOf20Bytes( )
*功 能：发送唤醒帧
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：发送20字节的唤醒帧
*
********************************************************************************/
unsigned char SendCallOf20Bytes(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
//	struct tcc_module *const module_inst;
//	uint32_t int_flags = module_inst->hw->INTFLAG.reg;
//	unsigned long i,j,k;
//	unsigned long timerCntOfInventor;
//	unsigned char lens;
//	unsigned long timercnt;
//
//	
//	__disable_irq();
//	switch((WRConfig->uartParameter[0].uartTxdBuffer[3]&0x0f0)>>4)
//	{
//		case FRAMEOFCALL:
//		WRConfig->DeviceChannel.channel_temp=0;
//		radio_ini(WRConfig,0);
//		//LETIMER_setup();
//		configure_tcc0(65535);
//		lens = WRConfig->uartParameter[0].uartTxdBuffer[2];
//		TimerSerialTemp=(pwtimer)&TimerSerialData;
//		TimerSerial =(pwtimer)&timercnt;//WRConfig->uartParameter[0].uartTxdBuffer[11];
//		TimerMaxSerial=(pwtimer)&WRConfig->uartParameter[0].uartTxdBuffer[15];
//		TimerSerialTemp->Dwtimer=(TimerSerial->Dwtimer*32768)/1000;
//		
//		TimerSerial->Dwtimer=0;
//		do{
//			
//			if (int_flags & TCC_INTFLAG_OVF)
//			{
//				//LETIMER0->IFC=LETIMER_IF_UF;
//				TimerSerialTemp->Dtimer[1]++;
//			}		
//				
//			//if((LETIMER0->IF&LETIMER_IF_UF)== LETIMER_IF_UF)
//			//{
//				//LETIMER0->IFC=LETIMER_IF_UF;
//				//TimerSerialTemp->Dtimer[1]++;
//			//}
//			TimerSerialTemp->Dtimer[0] =0xffff-(tcc_get_count_value(&tcc_instance)&0xffff);
//			TimerSerial->Dwtimer=(TimerSerialTemp->Dwtimer*1000/32768);
//						
//			PHY_DataReq(&WRConfig->uartParameter[0].uartTxdBuffer[3],lens);
//		
//		}	while(TimerSerial->Dwtimer < TimerMaxSerial->Dwtimer);
//	}
  return false;
}

/*******************************************************************************
*
*函 数：sendawakepackageDone( )
*功 能：检测发送唤醒帧
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：发送唤醒帧走射频0通道
*
********************************************************************************/
void sendawakepackageDone(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	uint32_t int_flags;
    unsigned int i;
	//uint32_t int_clr = 0;
	//unsigned long timerCntOfInventor;
	//unsigned char *s;
	unsigned char lens;
	unsigned long timercnt;
	unsigned char status;

	switch((WRConfig->uartParameter[0].uartTxdBuffer[3]&0x0f0)>>4)//判断信息帧属性
	{
		case FRAMEOFCALL:							//如果是唤醒帧		
		WRConfig->DeviceChannel.channel_temp=0;		//唤醒帧走射频0通道
		radio_ini(WRConfig,0);
		configure_tcc0(65535);						//初始化定时器0	
		tcc_disable_callback(&tcc_instance, TCC_CALLBACK_OVERFLOW);//取消回调函数
		
		lens = WRConfig->uartParameter[0].uartTxdBuffer[2];
		
		TimerSerialTemp=(pwtimer)&TimerSerialData;
		TimerSerial =(pwtimer)&timercnt;
		TimerMaxSerial=(pwtimer)&WRConfig->uartParameter[0].uartTxdBuffer[15];	//赋值最大睡眠时间
		TimerSerialTemp->Dwtimer= 0;				//时间计算初始清0
		TimerSerial->Dwtimer=0;						//时间计算初始清0
		
		int_flags = tcc_instance.hw->INTFLAG.reg;
		if (int_flags & TCC_INTFLAG_OVF)					//判断定时器是否溢出，溢出则计数高位加1
		{
			int_flags |= TCC_INTFLAG_OVF;
			tcc_instance.hw->INTFLAG.reg = int_flags;		//清溢出标志位
		}
		tcc_set_count_value(&tcc_instance,0);
		WDT_Stop();			
		delay_ms(100);
		do{
			int_flags = tcc_instance.hw->INTFLAG.reg;
			if (int_flags & TCC_INTFLAG_OVF)				//判断定时器是否溢出，溢出则计数高位加1
			{
				int_flags |= TCC_INTFLAG_OVF;
				tcc_instance.hw->INTFLAG.reg = int_flags;	//清溢出标志位
				TimerSerialTemp->Dtimer[1]++;				//计数高位
			}
			tcc_instance.hw->CTRLBSET.bit.CMD= TCC_CTRLBSET_CMD_READSYNC_Val;
			delay_us(10);
			TimerSerialTemp->Dtimer[0]=tcc_instance.hw->COUNT.reg;
			//TimerSerialTemp->Dtimer[0] =(tcc_get_count_value(&tcc_instance));		//获取定时器计数值
			TimerSerial->Dwtimer=(((TimerSerialTemp->Dwtimer)*2000)/32768);			//定时器计数值单位计算
			PHY_DataReq(&WRConfig->uartParameter[0].uartTxdBuffer[0],lens);			//射频发送数据
			for(i = 0;i<WRConfig->AttrOfDevice.TimerOfRatio[0].tempOver;i++)	//循环次数读取状态200次
			{
				status = phyReadRegister(IRQ_STATUS_REG);		//读取RF233寄存器中断状态
				if((status&(1 << TRX_END)) != 0)				//判断发送是否完成
				{
					//LED2_TOGGLE();
					break;
				}
			}
		}while(TimerSerial->Dwtimer<TimerMaxSerial->Dwtimer);	//发送时间为	TimerMaxSerial
		configure_wdt();	//独立看门狗初始化
		wdt_reset_count();  //喂狗
	}
}

/*******************************************************************************
*
*函 数：memset0( )
*功 能：格式化数据区
*输 入：ptr：源格式数据区,ch：要格式的数据区，length：格式长度
*输 出：
*作 者：
*时 间：2018.12.21
*备 注：功能类似于标准库函数memset()
*
********************************************************************************/
void memset0(unsigned char *ptr,unsigned char ch,unsigned long length)
{
	unsigned long i;
	for(i=0;i<length;i++)
	{
		*ptr++=ch;
	}
}

/*******************************************************************************
*
*函 数：mov_data( )
*功 能：检测设备
*输 入：source：源拷贝数据区,dist：要拷贝的数据区，lenth：拷贝长度
*输 出：
*作 者：
*时 间：2018.12.21
*备 注：功能类似于标准库函数memcpy()
*
********************************************************************************/
void mov_data(unsigned char *source,unsigned char *dist,unsigned char lenth)
{
	unsigned char i;
	for(i = 0; i< lenth;i++)
	{
		*dist++  = *source++;
	}
}

void memblockCopy(unsigned char *sdestAddr,unsigned char *dSourAddr,unsigned char length)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		*sdestAddr++=*dSourAddr++;
	}
}
