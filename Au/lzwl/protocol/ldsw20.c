#include "device.h"
#include "ldsw20.h"
#include "sio2host.h"
#include "stdlib.h"
#include "des.h"


swNOdeConfig WriterConfig;
sLDSW20deviceMap pointerOfLDSW20deviceMap[16];
sLDSW20Frame    sPointerOfLDSW20Frame[MAXchannelNumb]={0};


/*��ȡ��������ֲ���*/
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
/*������������ֲ���*/

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
	switch(FunctionGetAttrFRAME(cmmdChanel))	//��ȡ֡������
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
		case  FRAMEOFTEST:	//����֡
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
*�� CheckPassward( )
*�� �ܣ����������ڶԱȿ���
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(�������Ǵ��ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� ����3��������TRUE����Ӧ�����ȷ,FALSE�����������
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��
*
********************************************************************************/
unsigned char CheckPassward(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	unsigned char i,temp,ptemp;
    
	if(FunctionGetAttrOfDestDev(cmmdChanel)!=FunctionGetAttrDEVBeCTRL(cmmdChanel))
        return 2;//����δ���յ�
   
	temp=FunctionGetAttrPASSWORDSEC(cmmdChanel);//����0����Ҫ����
	
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
		return 3;//�����жϿ�������
	}
}


/*******************************************************************************
*
*�� ����checkLdsw20( )
*�� �ܣ�����豸��֡���Ͳ�����
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(��Э�������Ǵ��ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� ����TRUE����Ӧ��֡����,FALSE��������
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��
*
********************************************************************************/
unsigned char checkLdsw20(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl=(pLdsw20FrameCtl)(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[3]);

	if(GetPointerOfCmd(WRConfig, cmmdChanel)==FALSE)		//��ȡָ�������п����򣬵�ַ����·��ָ���򣬿�����ָ�� 
		return FALSE;
	if((FunctionGetAttrOfDestDev(cmmdChanel)!=deviceOfTYPE)&&(FunctionGetAttrOfDestDev(cmmdChanel)!=devOfDwritor))	//������ָ������豸Ϊָ���豸��ָ���ͬ���豸������벻ͬ
		return FALSE;
	if(CheckPassward(WRConfig,cmmdChanel)==FALSE)			//������
		return FALSE;
	
	switch(FunctionGetAttrFRAME(cmmdChanel))				//�ж���Ϣ֡����
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
			
		if(FunctionGetAttrBROADCAST(cmmdChanel)!=BROADCAST)	//�ж��Ƿ�Ϊ�㲥ģʽ
		{
			//�ж�Ŀ���ַ�Ƿ���Ч���豸Ŀ���ַ�뱾��ID��ַ�Ƿ����
			if((FunctionGetAttrDESTADRESSVALID(cmmdChanel)==TRUE)&&(Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestAdress)!=WRConfig->AttrOfDevice.DeviceID))
			return FALSE;
			//�ж��豸Ⱥ��ַ�Ƿ���Ч���豸Ŀ���ַ�뱾��ID��ַ�Ƿ����
			if((FunctionGetAttrDESTGROUPVALID(cmmdChanel)==TRUE)&&(Quoting(sPointerOfLDSW20Frame[cmmdChanel].sAreaofFrameAdress.DestGroup)!=WRConfig->AttrOfDevice.GroupId))
			return FALSE;
		}
		GetLDSW20MapNews(WRConfig);	//��ȡ������������ָ��ͳ���(��С)��
		return 1;
		
		case  FRAMEOFCALL:			//����
		return 2;
		
		case  FRAMEOFACK :			//ACK֡
		return 3;
		
		case FRAMEOFTEST:			//����֡
		return 4;
		
		default:
		return FALSE;
	}
}

/************************************
��ȡ������������ָ��ͳ��ȡ�
�豸�ŵ�������  0
�豸�澯������  1
�豸��λ������  2
�豸����������  3
�豸����������  4
�豸�û�������  5
�豸����������  6
�豸������·��  7
�豸��������  8
������������    9
���豸�̼��汾��13
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
*�� ����checkMemeryOfRAM( )
*�� �ܣ�
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(��Э�������Ǵ�
*       �ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� �����澯���������пɴ洢�Ľڵ�
*�� �ߣ�WGS
*ʱ �䣺2018.12.07
*�� ע��NONE
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
    //if(sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameChain->chainID[0] == WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Tag)//ȥ���ٴν�������ʱID�ظ�������
      //return (i);
  //}
  //return (i-1);
//}

/*******************************************************************************
*
*�� ����SaveDealdeDataOfInventoryToMemeryOfRAM( )
*�� �ܣ����ݴ洢��RAM��
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(��Э�������Ǵ�
*       �ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� ����NONE
*�� �ߣ�WGS
*ʱ �䣺2018.12.07
*�� ע��NONE
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
  /*��ָ����Ĳ���������12���ֽ� �ɼ��ն�ID �ɼ��ն˸澯��Чλ �ɼ��ն˸澯״̬λ*/
  mov_data(&sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCmd->parmofCmd[0],(unsigned char *)&WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Tag,12);
  WRConfig->MaprecordOfAlarm.RecorderOfNoteAlarm[i].Rssi=WRConfig->uartParameter[cmmdChanel].IssiStrength;		//����������ź�ǿ��
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
*�� ����DealdeDataOfInventory( )
*�� �ܣ����ݴ洢����
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(��Э�������Ǵ�
*       �ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� ����
*�� �ߣ�WGS
*ʱ �䣺2018.12.07
*�� ע��NONE
*
********************************************************************************/
unsigned char DealdeDataOfInventory(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
  //��ȡ��Ϣ֡����
  switch((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[0]&0x0f0)>>4)
  {
    case FRAMEOFALARM://�澯֡
    case FRAMEOFRESP: //Ӧ��֡
      if((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[1]&0x01)!=0x01)     //�����Ƿ�����
        return 0x0e;
      if(((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[4]&0x0e)>>5)!=0x00)//�����Ƿ����Ա�ǩ
        return 0x0e;
      //����ת����ʽ
      switch((sPointerOfLDSW20Frame[cmmdChanel].pAreaofFrameCtrl->FrameCtrl[3]&0x03))
      {
        case 0x01: //�洢���أ�д����(���������������Ҫ�洢��FRAM)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
          //saveToEEprom(WRConfig,cmmdChanel);
          return 1;
        case 0x02: //�洢ת����������RAM�� (���������������Ҫ�洢��RAM�еȴ��ϲ�Ӧ�ö�ȡ)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
        case 0x00: //ת��(���������������Ҫ��ʱ�ش�) 
          return 2;
        case 0x03: //���践��(�����������践���κ�����)
          SaveDealdeDataOfInventoryToMemeryOfRAM(WRConfig,cmmdChanel);
          return 3; 
      }
    case FRAMEOFHEARTBEAT://����֡
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
	if((temp&0x20)!=0)//Ⱥ��ַ�仯
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
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfPC;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
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
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|((RxdDataPointor[7]&0xe0)>>5);//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
	
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//Ⱥ��ַ�仯
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
	SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|((RxdDataPointor[7]&0xe0)>>5);//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
	SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
	
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//Ⱥ��ַ�仯
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
	if((temp&0x20)!=0)//Ⱥ��ַ�仯
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
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfPC;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
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
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfDwritor;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 34:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfDwritor;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 35:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 36:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 37:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 38:
		case 39:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		case 255:
		return FALSE;
		default:
		SendDataPointor[3]=(SendDataPointor[3]&0x0f0)|devOfRepeater;//Ŀ���豸���Ա仯���ն��豸���Ա�ΪĿ���豸����
		SendDataPointor[5]=(SendDataPointor[5]&0x0f0)|(RxdDataPointor[3]&0x0f);;//Դ�豸���Ա仯��Ŀ���豸���Ա�ΪԴ�豸����
		break;
		
	}
	temp =SendDataPointor[4];
	SendDataPointor=SendDataPointor+8;
	if((temp&0x20)!=0)//Ⱥ��ַ�仯
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

