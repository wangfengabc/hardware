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

#define uartBufferSize           127   //通讯口缓存初始255
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

#define RF_TX_RETRY_MAX 1           //重发次数

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

/*wFrameCtrlArea*************帧控制域结构体*******************/
/**************************************************************
*发送时低字节在前;
*BIT0-3   目标设备属性                BIT4-7   源设备属性
*BIT8-9   数据方向定义                BIT9-11  广播，点对点属性定义
*BIT12-15 信息帧属性                  BIT16-19 地址信息控制位
*BIT20-23 分组信息                    BIT24-25 预留
*BIT26-28 口令行选择                  BIT29    加密选择
*BIT30-31 加密方式                    BIT32-35 发射广播命令的设备属性
*BIT36   辅助模块使用选项             BIT37-39 智能节点属性
***************************************************************/
typedef __packed union wFrameCtrlArea
{
	unsigned char FrameCtrlByte[5];   //帧控制域一共5个字节
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
}rfTxStatu;   //定义枚举型rfTxStatu

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

/*wCMMDarea***********定位标签文件格式**********************/
typedef __packed struct  wCMMDarea
{
	unsigned short  ATTofCMMD;//长度
	unsigned long   offsetOfArea;//偏移
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

/*wNodeUartPara*********串口节点参数*******************/
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

/*sDeviceChannel*********设备信道结构体*******************/
typedef __packed union  wTimeOfRandW//标签收发包的计数器
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
	unsigned char     wakeUpCmmdIndex;			/*0: 盘点帧; 其他值为特殊盘点帧*/
	unsigned long     AsleepConst;
	sTimeOfRandW   TimeOfRandWofTag;
	unsigned char  ChannelCode_temp;
	//sBackupChain      cmmdCache;
} *pDeviceChannel,sDeviceChannel;

typedef __packed struct rfBackupChains
{
	unsigned char valid;			  //链表有效位
	unsigned char chainAttr;		  //链路属性，如：告警链路
	unsigned char rfChannel;		  //链路射频通道 0-96
	unsigned char chainLenth;		  //链路长度
	unsigned char chainPL[40];		  //链路内容，至少包括读写器 基站
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
	unsigned long RWID;            //读写器ID号
	unsigned long Readtotal_offset;//帧偏移（为0）
	unsigned int  Tagtemptotal;    //读写器读取时标签总数；
	unsigned char bankTotal;       //需要读取的次数
	unsigned char readCnt;         //当前读的次数
	unsigned char index;           //当前要读取的bank数
	unsigned char flag;            //读取标志
	unsigned char Bank[8];       //读取的bank总数
}*pLocationfirstframe,sLocationfirstframe;

typedef __packed struct  wMapNodeRecordOfAlarme//移动标签的记录
{
	unsigned long      Tag;           //采集终端ID
	unsigned long      AlarmValid;    //采集终端告警有效位
	unsigned long      AlarmStatus;   //采集终端告警状态位
	unsigned char      Rssi;          //读写器检测到的采集终端信号强度
	unsigned char      Power;         //采集终端信的发射功率强度
	unsigned short     CmdByte;       //命令字
	unsigned long      OffsetOfAddr;  //偏移地址
	unsigned char      text[32];      //数据
	unsigned char      Flag;          //存储标志
} * pMapNodeRecordOfAlarm,sMapNodeRecordOfAlarm;


typedef __packed struct  wMaprecordOfAlarm//移动标签的记录  警告映射记录
{
	volatile unsigned long QuantityOfRecords;
	unsigned char          Reserve[60];
	sMapNodeRecordOfAlarm  RecorderOfNoteAlarm[TAG_BUFF_SIZE];
	//sBackupChain           cmmdCache;
} *pMaprecordOfAlarm,sMaprecordOfAlarm;


/*wPosiFixNodeRecord*************信标终端信息***********************************/
typedef __packed struct wPosiFixNodeRecord//信标终端信息
{
	unsigned char    FrameIndex;          //帧类型
	unsigned long    FixNodeId;           //信标终端ID
	unsigned char    Power;               //移动采集终端发射功率
	unsigned char    Rssi;                //信标终端接收信号强度
} *pPosiFixNodeRecord,sPosiFixNodeRecord;

typedef __packed struct lbsScanLog
{
	unsigned long FixPoseNo;
	unsigned char readDone;
	unsigned short tagCount;
}*plbsScanLog,slbsScanLog;

typedef __packed struct wTagNoderecord	 //移动采集终端的记录  //
{
	unsigned long      MovingNodeID;   	       //移动采集终端ID
	unsigned char      Rssi; 		       //定位器收到数据的信号强度
	unsigned char      Power; 		       //移动标签的发射功率
	unsigned char      voltage;                  //电池电压
	unsigned char      reserved;                 //存储正确的标签信息后置1
} *pTagNoderecord,sTagNoderecord;

/*wPosNoderecord**********移动采集终端的记录***********************************/
typedef __packed struct wPosNoderecord
{
	unsigned char       dataValid;
	unsigned char       FixNodeNub;      //记录中信标终端的ID有效个数
	unsigned long       MovingNodeID;    //移动采集终端ID
	sPosiFixNodeRecord    FixNodeRcd[4];   //信标标签信息，最大定位包数8
} *pPosNoderecord,sPosNoderecord;

/*wPosiNodeBuff***********定位标签文件格式**************************************/
typedef __packed struct  wPosiNodeBuff
{
	unsigned long     QuantityOfTag;
	unsigned short    bank_total;
	unsigned char     reserve[42];
	unsigned char     FilesDisrip[32];
	sTagNoderecord     MovingNodeMap[50];	//移动标签的记录	bank=13
} *pPosiNodeBuff,sPosiNodeBuff;

/*wPasswordNodeBuff************设备口令结构体*******************************/
typedef __packed struct  sPasswordNodeBuff
{
	unsigned char passwordVoildByte[8] ;
	unsigned char PassWard0[7][8];
	//sBackupChain  cmmdCache;
} *pwPassword,swPassword;

/*IoConfig**************IO配置结构体***************************************/
typedef __packed struct  IoConfig
{
	unsigned short  IOVaild;        // IO有效标志
	unsigned short  IOInOut;        // IO输出/输入方向控制
	unsigned short  IOOutCtrl;      // IO输出状态控制
	unsigned short  IOStatus;       // IO输入状态下端口状态
	unsigned short  IOTeamValid;    // IO分组
	unsigned short  IOTeam;         // IO组号
} *pIoConfig,sIoConfig;

typedef __packed struct  IoPwmConfig
{
	unsigned short  IOVaild;      //IO有效标志
	unsigned char   IOOutCtrl[16]; //PWM占空比
	unsigned short  IOTeamValid;  //IO分组
	unsigned short  IOTeam;       //IO组号
} *pIoPwmConfig,sIoPwmConfig;

/*Alarmadc******************告警*******************************************/
typedef __packed struct Alarmadc
{
	unsigned char  AlarmAdcFlag;      //告警状态
	unsigned long  Alarm_modulus;     //Adc报警校正系数
	unsigned long  Alarm_Bottom;	     //Adc报警校正本底
	unsigned long  Alarm_Value;       //Adc采样值
	unsigned long  Alarm_Threshold;   //告警域值
}*PAlarmadc,SAlarmadc;

/*AlarmParam***************警告参数结构体**********************************/
typedef __packed struct AlarmParam
{
	unsigned int  sensor_Valid;
	unsigned int  sensor_Status;
	SAlarmadc  AlarmAdc[8];
	SAlarmadc  AlarmSensor[8];
} *PAlarmParam,SAlarmParam;

/*CommunicateRate**********传达率结构体********************************/
typedef __packed struct CommunicateRate
{
	unsigned char  CommVaild;    //端口选择
	unsigned char  CommEn;       //端口使能
	unsigned char  CommStatus;   //端口状态
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
	unsigned long backGround;     //背景噪声值
}*pRfJudgeParaOfRatio,sRfJudgeParaOfRatio;

/*DMemParam************设备用户数据区结构体*********************************/
typedef __packed struct  DMemParam
{
	unsigned long BankTotal;       //用户数据分区数量
	unsigned char BankLenth;       //用户数据分区长度
	unsigned long eXBankTotal;     //数传分区数量
	unsigned char eXBankLenth;     //数传分区长度
} *pMemParam,sMemParam;

//定位器扫描表
#define  MAX_TAGCOUNT  10//最大定位器个数
typedef  __packed struct FixPoseIDNo
{
	unsigned long FixPoseNo;
	unsigned char IdValid;
}*pFixPoseIDNo,sFixPoseIDNo;

typedef __packed struct FixPoseIDMap//固定标签ID表
{
	unsigned short Sendcount;                     //发送次数
	unsigned short send_flag;                     //发送标志位
	unsigned short check_IDFlag;                  //轮询标签ID标志位
	unsigned char  datMapFlag;
	unsigned char  channelBuff;                   //临时通道缓存
	unsigned char  channelOrigital;               //原始通道
	unsigned short ID_Total;                      //定位器ID号总数
	unsigned char  TexT_ReserveSpace[5];          //预留空白区
	sFixPoseIDNo   fixPoseIDno[MAX_TAGCOUNT];      //固定标签ID
} *pFixPoseIDMap,sFixPoseIDMap;

typedef __packed struct TagIDRecord  //标签属性
{
	unsigned long TagNodeID;   //标签ID
	unsigned char Index;       //标签序号
	unsigned char Flag;
}*pTagIDRecord, sTagIDRecord;

typedef __packed struct   TagIDMap  //标签比对表
{
	unsigned char  Reserve[16];
	sTagIDRecord     Tag[10];
}*pTagIDMap,sTagIDMap;

/*DataOfDeviceAttr*********设备属性数据区结构体*****************************/

typedef __packed struct DataOfDeviceAttr //设备属性数据区
{
	unsigned long     	GroupId;          //设备群ID
	unsigned long     	PCId;             //PC ID
	unsigned long     	DeviceID;         //设备ID
	unsigned long     	BroadcastTime;    //广播持续时间
	unsigned long     	HeartBeatenTime;  //心跳时间
	unsigned short   	RspTime;          //应答等待时间
	unsigned long    	AlarmValid;       //告警有效位
	unsigned long    	AlarmStatus;      //告警状态位
	unsigned char 	tagRssiThreshold; //标签RSSI比对门限
	unsigned char 	devFirmwareVer[FIRMWARE_VERSION_ID_LEN]; //固件版本号
	sCommunicateRate      ComRateConfig;    //通讯速度选择
	sIoConfig             IoConfig;         //IO电平操作区
	sIoPwmConfig          IoPwmConfig;      //IO pwm操作区
	sbackupRFchains       BackupRFchains;   //备用链路区
	sRfJudgeParaOfRatio   TimerOfRatio[4];  //rf radio设置参数
	SAlarmParam           SensorDeal;       //ADC以及传感器处理区
	sMemParam        	MemParam;         //存储空间参数
	sFixPoseIDMap         PoserTable;       //定位器扫描表
	sTagIDMap             TagCompTable;     //标签比对表
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

/*UserDataMap**********设备数据传输区结构体*************************************/
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

/*AttrOfRalerNode************中继器节点结构体****************************/
typedef __packed struct RfFrameAckCtrls
{
	unsigned char TimerEn;       //定时器使能
	unsigned long TimerCnt;      //定时器计数
	unsigned char TimeOutFlg;    //超时标志
	unsigned char sendRetryCnt;  //重发计数
	unsigned char sendFlg;
	unsigned char senddatatransFlg;
	unsigned char DataTransFlg;
}*pRfFrameCtrls,sRfFrameCtrls;

typedef __packed struct Timer//定时器函数参数
{
	unsigned long timerTick;
	unsigned char timerEN;
	unsigned long timeCount;      //unsigned long 4个字节65536
	unsigned char timeOfRecover;  //恢复通道标志
}sTimerCtrl;

typedef __packed struct FirmwareVerArea    //搜索回应内容
{
	unsigned long        verL;
	unsigned long        verH;      //版本号
	unsigned char        charge;    //电量
	unsigned char        type;      //类型 0-读写器，1-基站，2-中继，3-标签，4-定位器
	unsigned char        Rssi;
}*psFirmwareVerArea,sFirmwareVerArea;

typedef __packed struct rfBingDevice
{
	unsigned char valid;			//绑定有效位
	unsigned char devAttr;		//绑定设备属性(可以是读写器，定位器，标签,中继，pc)
	unsigned char rfChannel;		//绑定设备的工作频道
	unsigned char chainPL[4];		//绑定设备ID
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
	unsigned long Type;						/*分类*/
	unsigned char parameter[6];					/*参数*/
	unsigned char manufactory[6];				/*制造商*/
}*psDesc_t,sDesc_t;

typedef __packed struct UsensorInfo
{
	sDesc_t		sDesc;
	unsigned char senInfoUserDef[48];
}*pUsensorInfo,sUsensorInfo;

typedef __packed struct sensorInfoDesc
{
	unsigned char valid;						/*数据有效位*/
	unsigned long TagID;						/*标签id号*/
	sUsensorInfo  UsensorInfo;					/*数据*/
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

/********************盘点区********************/
typedef __packed  struct  wTagNodeInfo
{
	unsigned long      TagId;           //采集终端ID
	unsigned char      Rssi;          //读写器检测到的采集终端信号强度
	unsigned char      Power;         //采集终端信的发射功率强度
	unsigned char      text[36];      //数据
	unsigned char      Flag;          //存储标志
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
	sTagNodeInfo       MovingNodeMap[1];	//移动标签的记录	bank=13
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

typedef __packed struct ParamsOfTag   //设备存储区定义
{
	unsigned char        flag;           //对应存储位置 flash 0 ,铁电 1
	unsigned char        channel;        //RF 通道
	unsigned char        type;           //类型 0-读写器，1-基站，2-中继，3-标签，4-定位器
	unsigned char        power;          //发射功率
	unsigned char        pn;             //pn码
	unsigned char        mode;           //工作模式 （ 0-主动，1-被动，2-升级）
	unsigned char        reserved[2];
	unsigned long        paramAddr;      //设备存储区地址
	unsigned long        jumpAddr;       //app区地址
	unsigned long        groupId;        //组ID
	unsigned long        deviceId;       //设备ID
	unsigned long        ver;            //版本号
	unsigned long        updateGroupId;  //对应升级手持机的
	unsigned long        updateId;       //对应升级手持机的
}*pParamsOfTag,sParamsOfTag;


#endif