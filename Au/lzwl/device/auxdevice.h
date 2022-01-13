#ifndef AUXDEVICE_H_
#define AUXDEVICE_H_


#include "device.h"

#define RFOfTag				0
#define RFOfAUX				7
#define RFOfstation			2

#if 0//(deviceOfTYPE == deviceOfBaseStation)
#define RFchanelOfDevice   RFOfstation
#else
#define RFchanelOfDevice   RFOfAUX
#endif

#define uartBufferSize           127   //ͨѶ�ڻ����ʼ255
#define FIRMWARE_VERSION_ID_LEN  32
#define RF_BACKUP_CHAIN_MAX      1
#define CMMD_MAX_SIZE            2

#define TAG_BUFF_SIZE   	16
#define TAG_LOOP_CNT_OFFSET	(TAG_BUFF_SIZE-1)

#define SENSOR_INFO_BANK_MAX     16

#define CHANNEL_RECOVER_TIME_CNT 500 //350    //350=700ms  500=1s
#define RF_TX_CCA_REQ            1
#define RF_TX_FORCED             2

#define RF_TX_ACK_REQ 1
#define RF_TX_ACK_NONE 2

#define RF_TX_RETRY_MAX 1           //�ط�����

#define NET_ADDR_SIZE 4

#define NET_RE_COUNT_MAX 9

/////////////rf tx status define /////////////
#define TX_STATUS_IDLE           0
#define TX_STATUS_SEND           1
#define TX_STATUS_ACK_RESEND     2
#define TX_STATUS_DAT_RESEND     3
#define TX_STATUS_DONE           4
#define TX_STATUS_WATI_DATA      5
#define TX_STATUS_WAIT_RETRY     6
#define TX_STATUS_NA             7

/*wFrameCtrlArea*************֡������ṹ��*******************/
/**************************************************************
*����ʱ���ֽ���ǰ;
*BIT0-3   Ŀ���豸����                BIT4-7   Դ�豸����
*BIT8-9   ���ݷ�����                BIT9-11  �㲥����Ե����Զ���
*BIT12-15 ��Ϣ֡����                  BIT16-19 ��ַ��Ϣ����λ
*BIT20-23 ������Ϣ                    BIT24-25 Ԥ��
*BIT26-28 ������ѡ��                  BIT29    ����ѡ��
*BIT30-31 ���ܷ�ʽ                    BIT32-35 ����㲥������豸����
*BIT36   ����ģ��ʹ��ѡ��             BIT37-39 ���ܽڵ�����
***************************************************************/
typedef __packed union wFrameCtrlArea
{
	unsigned char FrameCtrlByte[5];   //֡������һ��5���ֽ�
}*pwFrameCtrlArea,swFrameCtrlArea;

typedef enum rfTxStatus_u
{
	RF_TX_NA,         //0
	RF_TX_FAILED,     //1
	RF_TX_CCA_FAILED,
	RF_TX_TIME_OUT,
	RF_TX_DONE,
	RF_TX_ACK_NDATA,
	RF_TX_DONE_WITH_ACK,
	RT_TX_DONE_ACK_CRC_ERR,
	RF_TX_DONE_ACK_TIMEOUT,
	RF_TX_RADIO_BUSY,
	RF_TX_RADIO_ERR,
	RF_TX_BAD_PARAMENTER,
	RF_TX_NO_ACK,
	RT_TX_BUSY,
}rfTxStatu;   //����ö����rfTxStatu

typedef enum ldswtTestMode_u
{
	TEST_MODE_RF_LOOP,
	TEST_MODE_RF_POWER,
}ldswTestMode;

typedef enum ldswtTestStatu_u
{
	TEST_STATU_HALT,
	TEST_STATU_START,
}ldswTestStatu;

typedef __packed union
{
	unsigned char addr[NET_ADDR_SIZE];
	unsigned long longAddr;
}*paddrUnion,addrUnion;

/*wCMMDarea***********��λ��ǩ�ļ���ʽ**********************/
typedef __packed struct  wCMMDarea
{
	unsigned short  ATTofCMMD;//����
	unsigned long   offsetOfArea;//ƫ��
} *pCMMDarea,sCMMDarea;

typedef __packed struct rfChain
{
	unsigned char    usage;
	unsigned char    frameLenth;
	unsigned char    rspChannel;
	unsigned char    payload[16];
	unsigned char    payloadOffset;
	unsigned char    broadType;
	unsigned char    frameType;
	unsigned char    cmmd;
	unsigned char    cmmdLenth;
	unsigned char    rspFrameType;
	unsigned char    *cmmdAddrPtr;
	unsigned char    tagACKValid;
	unsigned long    destTagAddr;
	sCMMDarea        AttrOfCmmd;
	sCMMDarea        origAttrOfCmmd;
}*pBackupChain,sBackupChain;

typedef __packed struct  rfFrameAddrPtr
{
	unsigned char * dstGroupAddrPtr;
	unsigned char * dstAddrPtr;
	unsigned char * srcGroupAddrPtr;
	unsigned char * srcAddrPtr;

	unsigned char * nextREaddrPtr;
	unsigned char * dstRWaddrPtr;
	unsigned char * dstSMEDptr;
	unsigned char * dstREaddrPtr;
	unsigned char * dstLocatorPtr;
	unsigned char * BSaddrPtr;
	unsigned char * rfChainCfgPtr;

	unsigned char  rfFrameAckLoc;
	unsigned char  rfFrameOffCnt;
	unsigned char  rfChainValid;

	unsigned char reCount;
	unsigned char reIndex;
	unsigned char frameDriect;

	unsigned char frameToAux;
	unsigned char framToAuxType;

	unsigned char frameType;
	unsigned char broadType;
	unsigned char TagCountFilterEn;
	unsigned char rfReturnType;
	
	unsigned char operAreaIndex;
	unsigned char destDevType;
	unsigned char TagFilterEn;
	unsigned char cmd;
	unsigned char OpArea;
	unsigned char cmdLen;
	unsigned long offset;
	
}*pRfFrameAddrPtr,sRfFrameAddrPtr;

typedef __packed struct commTimer
{
	unsigned char timerUsage;
	unsigned char timerEN;
	unsigned long timerCnt;
	unsigned char timeOutFlg;
	unsigned long loopCnt;
	unsigned short loopOffset;
	unsigned char frameIndex;
	unsigned char copyLenth;
	unsigned char payloadOffset;
	volatile unsigned short curSoltIndex;
}*pCommTimer,sCommTimer;

typedef __packed struct appAckInfo
{
	unsigned char ackFlag;
	unsigned long dstAddr;
	unsigned char ackToken[10];
	//sCMMDarea	cmmd;
}*pAckInfo,sAckInfo;

/*wNodeUartPara*********���ڽڵ����*******************/
typedef __packed struct wNodeUartPara
{
	unsigned char   rebootFlg;
	unsigned char   IssiStrength;
	volatile unsigned char uartStatus;
	unsigned char   uartRxdPointer;
	unsigned char   uartTxdPointer;
	unsigned char   uartTimer_count;
	unsigned char uartcovery_count;
	unsigned char   RfTimer_count;
	unsigned char   UartRawDataLen;
	unsigned char   uartReci_length;
	unsigned char   uartSend_length;
	unsigned char   srandV;
	unsigned char   seed;
	sRfFrameAddrPtr  RfFrameAddrPtr;
	sAckInfo	   ackInfo;
	unsigned char   uartRxdtemp[uartBufferSize];
	unsigned char   uartRxdBuffer[uartBufferSize];
	unsigned char   uartTxdtemp[uartBufferSize];
	unsigned char   uartTxdBuffer[uartBufferSize];
	//unsigned char   ReSendBuffer[127];
}*pNodeUartPara,sNodeUartPara;

/*sDeviceChannel*********�豸�ŵ��ṹ��*******************/
typedef __packed union  wTimeOfRandW//��ǩ�շ����ļ�����
{
	unsigned  short TimeOfRandW;
	unsigned  char RandW[2]; //
} sTimeOfRandW,*pTimeOfRandW;

typedef __packed struct  wDeviceChannel
{
	unsigned char     F0;				//WAKEUP
	unsigned char     F1;				//TAG,LOC,RW
	unsigned char     F2;				//RE,RW,BS
	unsigned char     F3;				//LOC
	unsigned char     F4;
	unsigned char     F5;				//ACK
	unsigned char     F6;
	unsigned char     F7;
	unsigned char     T0;
	unsigned char     T1;
	unsigned char     T2;
	unsigned char     T3;
	unsigned short    T_vaild;
	unsigned short    T_En;
	unsigned char     SFD_Value[4];
	unsigned char     F_sec;
	unsigned char     Precod[3];
	unsigned char     Dat_pn [16];
	unsigned char     Sop_pn[8];
	unsigned char     Pow[4];
	unsigned char     Reci[4];
	unsigned char     DataRat[4];
	unsigned char     channel_temp;
	unsigned char     PNcode_temp;
	unsigned long     timerOfAwake[2];
	unsigned char     WaitTimeForTag;
	unsigned char     wakeUpCmmdIndex;			/*0: �̵�֡; ����ֵΪ�����̵�֡*/
	unsigned long     AsleepConst;
	sTimeOfRandW   TimeOfRandWofTag;
	unsigned char  ChannelCode_temp;
	//sBackupChain      cmmdCache;
} *pDeviceChannel,sDeviceChannel;

typedef __packed struct rfBackupChains
{
	unsigned char valid;			  //������Чλ
	unsigned char chainAttr;		  //��·���ԣ��磺�澯��·
	unsigned char rfChannel;		  //��·��Ƶͨ�� 0-96
	unsigned char chainLenth;		  //��·����
	unsigned char chainPL[40];		  //��·���ݣ����ٰ�����д�� ��վ
}*pRFchains,sRFchains;

typedef __packed struct backupRFchainArea
{
	unsigned char chainTotal;
	unsigned char Reserve[32];
	sRFchains      chains[RF_BACKUP_CHAIN_MAX];
	//sBackupChain    cmmdCache;
}*pbackupRFchains,sbackupRFchains;

typedef __packed struct Locationfirstframe
{
	unsigned long RWID;            //��д��ID��
	unsigned long Readtotal_offset;//֡ƫ�ƣ�Ϊ0��
	unsigned int  Tagtemptotal;    //��д����ȡʱ��ǩ������
	unsigned char bankTotal;       //��Ҫ��ȡ�Ĵ���
	unsigned char readCnt;         //��ǰ���Ĵ���
	unsigned char index;           //��ǰҪ��ȡ��bank��
	unsigned char flag;            //��ȡ��־
	unsigned char Bank[8];       //��ȡ��bank����
}*pLocationfirstframe,sLocationfirstframe;

typedef __packed struct  wMapNodeRecordOfAlarme//�ƶ���ǩ�ļ�¼
{
	unsigned long      Tag;           //�ɼ��ն�ID
	unsigned long      AlarmValid;    //�ɼ��ն˸澯��Чλ
	unsigned long      AlarmStatus;   //�ɼ��ն˸澯״̬λ
	unsigned char      Rssi;          //��д����⵽�Ĳɼ��ն��ź�ǿ��
	unsigned char      Power;         //�ɼ��ն��ŵķ��书��ǿ��
	unsigned short     CmdByte;       //������
	unsigned long      OffsetOfAddr;  //ƫ�Ƶ�ַ
	unsigned char      text[32];      //����
	unsigned char      Flag;          //�洢��־
} * pMapNodeRecordOfAlarm,sMapNodeRecordOfAlarm;


typedef __packed struct  wMaprecordOfAlarm//�ƶ���ǩ�ļ�¼  ����ӳ���¼
{
	volatile unsigned long QuantityOfRecords;
	unsigned char          Reserve[60];
	sMapNodeRecordOfAlarm  RecorderOfNoteAlarm[TAG_BUFF_SIZE];
	//sBackupChain           cmmdCache;
} *pMaprecordOfAlarm,sMaprecordOfAlarm;


/*wPosiFixNodeRecord*************�ű��ն���Ϣ***********************************/
typedef __packed struct wPosiFixNodeRecord//�ű��ն���Ϣ
{
	unsigned char    FrameIndex;          //֡����
	unsigned long    FixNodeId;           //�ű��ն�ID
	unsigned char    Power;               //�ƶ��ɼ��ն˷��书��
	unsigned char    Rssi;                //�ű��ն˽����ź�ǿ��
} *pPosiFixNodeRecord,sPosiFixNodeRecord;

typedef __packed struct lbsScanLog
{
	unsigned long FixPoseNo;
	unsigned char readDone;
	unsigned short tagCount;
}*plbsScanLog,slbsScanLog;

typedef __packed struct wTagNoderecord	 //�ƶ��ɼ��ն˵ļ�¼  //
{
	unsigned long      MovingNodeID;   	       //�ƶ��ɼ��ն�ID
	unsigned char      Rssi; 		       //��λ���յ����ݵ��ź�ǿ��
	unsigned char      Power; 		       //�ƶ���ǩ�ķ��书��
	unsigned char      voltage;                  //��ص�ѹ
	unsigned char      reserved;                 //�洢��ȷ�ı�ǩ��Ϣ����1
} *pTagNoderecord,sTagNoderecord;

/*wPosNoderecord**********�ƶ��ɼ��ն˵ļ�¼***********************************/
typedef __packed struct wPosNoderecord
{
	unsigned char       dataValid;
	unsigned char       FixNodeNub;      //��¼���ű��ն˵�ID��Ч����
	unsigned long       MovingNodeID;    //�ƶ��ɼ��ն�ID
	sPosiFixNodeRecord    FixNodeRcd[4];   //�ű��ǩ��Ϣ�����λ����8
} *pPosNoderecord,sPosNoderecord;

/*wPosiNodeBuff***********��λ��ǩ�ļ���ʽ**************************************/
typedef __packed struct  wPosiNodeBuff
{
	unsigned long     QuantityOfTag;
	unsigned short    bank_total;
	unsigned char     reserve[42];
	unsigned char     FilesDisrip[32];
	sTagNoderecord     MovingNodeMap[50];	//�ƶ���ǩ�ļ�¼	bank=13
} *pPosiNodeBuff,sPosiNodeBuff;

/*wPasswordNodeBuff************�豸����ṹ��*******************************/
typedef __packed struct  sPasswordNodeBuff
{
	unsigned char passwordVoildByte[8] ;
	unsigned char PassWard0[7][8];
	//sBackupChain  cmmdCache;
} *pwPassword,swPassword;

/*IoConfig**************IO���ýṹ��***************************************/
typedef __packed struct  IoConfig
{
	unsigned short  IOVaild;        // IO��Ч��־
	unsigned short  IOInOut;        // IO���/���뷽�����
	unsigned short  IOOutCtrl;      // IO���״̬����
	unsigned short  IOStatus;       // IO����״̬�¶˿�״̬
	unsigned short  IOTeamValid;    // IO����
	unsigned short  IOTeam;         // IO���
} *pIoConfig,sIoConfig;

typedef __packed struct  IoPwmConfig
{
	unsigned short  IOVaild;      //IO��Ч��־
	unsigned char   IOOutCtrl[16]; //PWMռ�ձ�
	unsigned short  IOTeamValid;  //IO����
	unsigned short  IOTeam;       //IO���
} *pIoPwmConfig,sIoPwmConfig;

/*Alarmadc******************�澯*******************************************/
typedef __packed struct Alarmadc
{
	unsigned char  AlarmAdcFlag;      //�澯״̬
	unsigned long  Alarm_modulus;     //Adc����У��ϵ��
	unsigned long  Alarm_Bottom;	     //Adc����У������
	unsigned long  Alarm_Value;       //Adc����ֵ
	unsigned long  Alarm_Threshold;   //�澯��ֵ
}*PAlarmadc,SAlarmadc;

/*AlarmParam***************��������ṹ��**********************************/
typedef __packed struct AlarmParam
{
	unsigned int  sensor_Valid;
	unsigned int  sensor_Status;
	SAlarmadc  AlarmAdc[8];
	SAlarmadc  AlarmSensor[8];
} *PAlarmParam,SAlarmParam;

/*CommunicateRate**********�����ʽṹ��********************************/
typedef __packed struct CommunicateRate
{
	unsigned char  CommVaild;    //�˿�ѡ��
	unsigned char  CommEn;       //�˿�ʹ��
	unsigned char  CommStatus;   //�˿�״̬
	unsigned char  uart[4];
	unsigned char  RF[4];
} *pCommunicateRate, sCommunicateRate;

/*RFJudgeParaOfRatio**********************************************************/
typedef __packed struct  RfJudgeParaOfRatio
{
	unsigned long tempComp;
	unsigned long GetAckDls;
	unsigned long tempOver;
	unsigned long tempWait;
	unsigned long sampleTimes;
	unsigned long backGround;     //��������ֵ
}*pRfJudgeParaOfRatio,sRfJudgeParaOfRatio;

/*DMemParam************�豸�û��������ṹ��*********************************/
typedef __packed struct  DMemParam
{
	unsigned long BankTotal;       //�û����ݷ�������
	unsigned char BankLenth;       //�û����ݷ�������
	unsigned long eXBankTotal;     //������������
	unsigned char eXBankLenth;     //������������
} *pMemParam,sMemParam;

//��λ��ɨ���
#define  MAX_TAGCOUNT  10//���λ������
typedef  __packed struct FixPoseIDNo
{
	unsigned long FixPoseNo;
	unsigned char IdValid;
}*pFixPoseIDNo,sFixPoseIDNo;

typedef __packed struct FixPoseIDMap//�̶���ǩID��
{
	unsigned short Sendcount;                     //���ʹ���
	unsigned short send_flag;                     //���ͱ�־λ
	unsigned short check_IDFlag;                  //��ѯ��ǩID��־λ
	unsigned char  datMapFlag;
	unsigned char  channelBuff;                   //��ʱͨ������
	unsigned char  channelOrigital;               //ԭʼͨ��
	unsigned short ID_Total;                      //��λ��ID������
	unsigned char  TexT_ReserveSpace[5];          //Ԥ���հ���
	sFixPoseIDNo   fixPoseIDno[MAX_TAGCOUNT];      //�̶���ǩID
} *pFixPoseIDMap,sFixPoseIDMap;

typedef __packed struct TagIDRecord  //��ǩ����
{
	unsigned long TagNodeID;   //��ǩID
	unsigned char Index;       //��ǩ���
	unsigned char Flag;
}*pTagIDRecord, sTagIDRecord;

typedef __packed struct   TagIDMap  //��ǩ�ȶԱ�
{
	unsigned char  Reserve[16];
	sTagIDRecord     Tag[10];
}*pTagIDMap,sTagIDMap;

/*DataOfDeviceAttr*********�豸�����������ṹ��*****************************/

typedef __packed struct DataOfDeviceAttr //�豸����������
{
	unsigned long     	GroupId;          //�豸ȺID
	unsigned long     	PCId;             //PC ID
	unsigned long     	DeviceID;         //�豸ID
	unsigned long     	BroadcastTime;    //�㲥����ʱ��
	unsigned long     	HeartBeatenTime;  //����ʱ��
	unsigned short   	RspTime;          //Ӧ��ȴ�ʱ��
	unsigned long    	AlarmValid;       //�澯��Чλ
	unsigned long    	AlarmStatus;      //�澯״̬λ
	unsigned char 	tagRssiThreshold; //��ǩRSSI�ȶ�����
	unsigned char 	devFirmwareVer[FIRMWARE_VERSION_ID_LEN]; //�̼��汾��
	sCommunicateRate      ComRateConfig;    //ͨѶ�ٶ�ѡ��
	sIoConfig             IoConfig;         //IO��ƽ������
	sIoPwmConfig          IoPwmConfig;      //IO pwm������
	sbackupRFchains       BackupRFchains;   //������·��
	sRfJudgeParaOfRatio   TimerOfRatio[4];  //rf radio���ò���
	SAlarmParam           SensorDeal;       //ADC�Լ�������������
	sMemParam        	MemParam;         //�洢�ռ����
	sFixPoseIDMap         PoserTable;       //��λ��ɨ���
	sTagIDMap             TagCompTable;     //��ǩ�ȶԱ�
	//sBackupChain        cmmdCache;        //
}*pDataOfDeviceAtt,sDataOfDeviceAttr;

typedef __packed struct usrTrasDataInfo
{
	unsigned char flag;
	unsigned char recRssi;
	long deviceID;
	unsigned char plLen;
	unsigned char verID;
	unsigned char dataPayload[36];		//
}*pUsrDataInfo,sUsrDataInfo;			//all 54 bytes

/*UserDataMap**********�豸���ݴ������ṹ��*************************************/
typedef __packed struct UserDataMap
{
	unsigned long BankTotal;
	unsigned char BankLenth;
	unsigned char Reserve[27];
	unsigned char dataPayload[150];
	//sUsrDataInfo  userdata[5];			//5*50
	unsigned char curSlotIndex;
	unsigned char QuantityOfRecords;
	unsigned char BankIndex;
	//sBackupChain  cmmdCache;
}*pUserDataMap,sUserDataMap;

/*AttrOfRalerNode************�м����ڵ�ṹ��****************************/
typedef __packed struct RfFrameAckCtrls
{
	unsigned char TimerEn;       //��ʱ��ʹ��
	unsigned long TimerCnt;      //��ʱ������
	unsigned char TimeOutFlg;    //��ʱ��־
	unsigned char sendRetryCnt;  //�ط�����
	unsigned char sendFlg;
	unsigned char senddatatransFlg;
	unsigned char DataTransFlg;
}*pRfFrameCtrls,sRfFrameCtrls;

typedef __packed struct Timer//��ʱ����������
{
	unsigned long timerTick;
	unsigned char timerEN;
	unsigned long timeCount;      //unsigned long 4���ֽ�65536
	unsigned char timeOfRecover;  //�ָ�ͨ����־
}sTimerCtrl;

typedef __packed struct FirmwareVerArea    //������Ӧ����
{
	unsigned long        verL;
	unsigned long        verH;      //�汾��
	unsigned char        charge;    //����
	unsigned char        type;      //���� 0-��д����1-��վ��2-�м̣�3-��ǩ��4-��λ��
	unsigned char        Rssi;
}*psFirmwareVerArea,sFirmwareVerArea;

typedef __packed struct rfBingDevice
{
	unsigned char valid;			//����Чλ
	unsigned char devAttr;		//���豸����(�����Ƕ�д������λ������ǩ,�м̣�pc)
	unsigned char rfChannel;		//���豸�Ĺ���Ƶ��
	unsigned char chainPL[4];		//���豸ID
}*prfBingDevAttr, srfBingDevAttr;

typedef __packed struct rfBingDevArea
{
	unsigned char    bingDevTotal;
	unsigned char    Reserve[32];
	srfBingDevAttr    rfBingDev[2];
	//sBackupChain     cmmdCache;
}*prfBingDevArea,srfBingDevArea;

typedef __packed struct sDescInfo
{
	unsigned long Type;						/*����*/
	unsigned char parameter[6];					/*����*/
	unsigned char manufactory[6];				/*������*/
}*psDesc_t,sDesc_t;

typedef __packed struct UsensorInfo
{
	sDesc_t		sDesc;
	unsigned char senInfoUserDef[48];
}*pUsensorInfo,sUsensorInfo;

typedef __packed struct sensorInfoDesc
{
	unsigned char valid;						/*������Чλ*/
	unsigned long TagID;						/*��ǩid��*/
	sUsensorInfo  UsensorInfo;					/*����*/
}*prwContextList,rwContextList;

typedef __packed struct sensInfoRamMap
{
	unsigned char sensorInfoCnt;
	unsigned char reserved[32];
	rwContextList context[SENSOR_INFO_BANK_MAX];
	//sBackupChain      cmmdCache;
}*psensorInfoRamMap,sensorInfoRamMap;

typedef __packed struct ldswManuTest_t
{
	ldswTestMode  testMode;
	ldswTestStatu testStatu;
	unsigned char txFlag;
	unsigned char testDeviceAttr;
	unsigned char rfLoopRxCnt;
	unsigned char rfLoopTxCnt;
	unsigned long txTimerCnt;
	unsigned char rfLoopTestCnt;
	unsigned char rfTxInverVal;
	unsigned char hwTestResultMsk;
	unsigned char testResult[3];
}*pLdswManuTest,sLdswManuTest;

typedef __packed struct userKey_t
{
	unsigned char keyNum;
	unsigned char keyScanFlag;
	unsigned char keyStatue;
}*pUserKey,sUserKey;

typedef __packed struct sysPromisCtrls
{
	unsigned short FramRWlength;
	volatile unsigned char rf0TxTestSendFlg;
	unsigned char sysLedStatus[3];
	unsigned char xorKeyInit;
	unsigned char xorKeyIndex;
	unsigned char desDecKey[8];
	unsigned char desEncKey[8];
}*psysPromisCtrl,sSysPromisCtrl;

/********************�̵���********************/
typedef __packed  struct  wTagNodeInfo
{
	unsigned long      TagId;           //�ɼ��ն�ID
	unsigned char      Rssi;          //��д����⵽�Ĳɼ��ն��ź�ǿ��
	unsigned char      Power;         //�ɼ��ն��ŵķ��书��ǿ��
	unsigned char      text[36];      //����
	unsigned char      Flag;          //�洢��־
} *pTagNodeInfo,sTagNodeInfo;


typedef __packed union wtimer
{
	unsigned long  Dwtimer;
	unsigned short Dtimer[2];
}*pwtimer,swtimer;


typedef __packed  struct  wInventorInfo
{
	unsigned char CmdIndex;
	unsigned char param;
	unsigned long sourceId;
	unsigned long timerOfAwake[2];
	volatile unsigned short curSoltIndex;
} *pInventorInfo,sInventorInfo;

typedef __packed  struct  wInventorMap
{
	unsigned long     QuantityOfTag;
	unsigned short    bank_total;
	unsigned char     reserve[42];
	sInventorInfo      InventorInfo;
	sTagNodeInfo       MovingNodeMap[1];	//�ƶ���ǩ�ļ�¼	bank=13
} *pInventorMap,sInventorMap;
/****************************************/

typedef __packed struct wNodeConfig
{
	unsigned char		ini_flag[3];
	sDataOfDeviceAttr   AttrOfDevice;
	sDeviceChannel      DeviceChannel;
	swPassword          Password;
	sMaprecordOfAlarm   MaprecordOfAlarm;
	sPosiNodeBuff       LocationDataArea;
	sUserDataMap        UserDataArea;
	sUserDataMap        UserTransArea;
	sInventorMap        InventorArea;
	sNodeUartPara       uartParameter[CMMD_MAX_SIZE];
	sRfFrameCtrls       RfFrameDatCtrls;
	sFirmwareVerArea    FirmwareVerID;

	//unsigned char      RssiStrenth;
	//unsigned char     HeartBeatflg;
	//unsigned char      keepAliveSendFlg;
	//unsigned long      keepAliveCnt;
	//unsigned char      reciDoneFlg;
	#ifdef TAGINVENTORY_DEBUG
	unsigned char       recNewTagInventoryRspInfo;
	#endif
	unsigned long      spiDataLength;
}*pwNodeCondig,swNOdeConfig;


typedef __packed struct AttrOfRelayChain
{
	unsigned char chainAttr;
	unsigned long DeviceId[10];
}*pRelayChain,sRelayChain;

typedef __packed struct TxParaOfpointer
{
	unsigned char *DestinAdrpointer;
	unsigned char  DestinAttr;
	unsigned char *SourceAdrpointer;
	unsigned char  SourceAttr;
	unsigned char *chainAddrPointer;
}*pTxParaOfpointer,sTxParaOfpointer;

typedef __packed struct ParamsOfTag   //�豸�洢������
{
	unsigned char        flag;           //��Ӧ�洢λ�� flash 0 ,���� 1
	unsigned char        channel;        //RF ͨ��
	unsigned char        type;           //���� 0-��д����1-��վ��2-�м̣�3-��ǩ��4-��λ��
	unsigned char        power;          //���书��
	unsigned char        pn;             //pn��
	unsigned char        mode;           //����ģʽ �� 0-������1-������2-������
	unsigned char        reserved[2];
	unsigned long        paramAddr;      //�豸�洢����ַ
	unsigned long        jumpAddr;       //app����ַ
	unsigned long        groupId;        //��ID
	unsigned long        deviceId;       //�豸ID
	unsigned long        ver;            //�汾��
	unsigned long        updateGroupId;  //��Ӧ�����ֳֻ���
	unsigned long        updateId;       //��Ӧ�����ֳֻ���
}*pParamsOfTag,sParamsOfTag;


#endif