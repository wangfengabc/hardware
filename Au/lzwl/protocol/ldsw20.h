#ifndef LDSW20_H_
#define LDSW20_H_

#include "auxdevice.h"

#define  MAXchannelNumb    2
#define  devOfSmartModel          0
#define  devOfAuxiliary           1
#define  devOfLocator             2
#define  devOfSwritor             3
#define  devOfDwritor             4
#define  devOfRepeater            5
#define  devOfBaseStation         6
#define  devOfHander              7
#define  devOfPC                  15

#define  deviceOfTYPE     devOfAuxiliary		//设备类型


/************************************************************************/
/*                         
		支持long或short指针数据（注：编译器不支持变量单字节对齐时使用）                                 
*/
/************************************************************************/
typedef  union test_
{
	//unsigned char Char_[4];
	//unsigned short Short_[2];
	unsigned long  long_;
}LongType;


/*控制域**************************************************/
typedef enum
{
	deviceOfSMARTNODE,
	deviceOfAUXMODEL,
	deviceOfLOCATOR,
	deviceOfSWRITER,
	deviceOfDWRITER,
	deviceOfRELAYER,
	deviceOfBASESTATION,
	deviceOfHANDLE,
	deviceOfRESERVE0,
	deviceOfRESERVE1,
	deviceOfRESERVE2,
	deviceOfRESERVE3,
	deviceOfRESERVE4,
	deviceOfRESERVE5,
	deviceOfRESERVE6,
	deviceOfPCdevice,
}DFDeviceType;

typedef enum
{
	mUserTransArea,
	mMaprecordOfAlarm,
	mLocationDataArea,
	mPassword,
	mAttrOfDevice,
	mUserDataArea,
	mDeviceChannel,
	mrfBackupchainsArea,
	mrfBingDevArea,
	msensorInfoArea,
	mCacheArea,
	mReserve0,
	mReserve1,
	mfirmwareArea,
	mReserve2,
	mReserve3
}MapOfDevice;

typedef __packed struct LDSW20FrameCtrl            //帧控制域
{
	unsigned char     FrameCtrl[5];
}*pLdsw20FrameCtl;

typedef __packed struct LDSW20FrameAdress
{
	unsigned long     *DestGroup;			//帧地址域目标地址
	unsigned long     *DestAdress;			//帧地址域目标地址
	unsigned long     *SourceGroup;			//帧地址域源地址
	unsigned long     *SourceAdress;			//帧地址域目标地址
}*pLdsw20FrameAdress,sLdsw20FrameAdress;

typedef __packed struct LDSW20FrameChain
{
	//unsigned char      chainTotal;			//链路设备总数
	//unsigned char      chainCount;			//当前链路指针，用于标明当前该接收的链路设备id
	unsigned char      chainNumb;
	unsigned long      chainID[];                         //链路id列表，链路排列从以高层设备开始，由近及远排列。
}*pLdsw20FrameChain;

typedef __packed struct LDSW20FrameCMD
{
	unsigned  short     CmdOfATTR;			//指令属性
	unsigned  long      OffsetofAddress;			//参数地址偏移量
	unsigned  char      parmofCmd[];                      //指令参数。
}*pLdsw20FrameCmd;

typedef __packed struct LDSW20FramePSWD
{
	unsigned  char   parmofCmd[8];                      //指令参数。
}*pLdsw20FramePswd;


typedef __packed struct LDSW20Frame
{
	pLdsw20FrameCtl       pAreaofFrameCtrl;
	sLdsw20FrameAdress    sAreaofFrameAdress;
	pLdsw20FrameChain 	pAreaofFrameChain;
	pLdsw20FrameCmd       pAreaofFrameCmd;
	pLdsw20FramePswd      pAreaofFramePswd;
	unsigned long        offsetOfAdress;
	unsigned long        offsetOfFrameChain;
	unsigned long        offsetOfFrameCmd;
}*pLDSW20Frame,sLDSW20Frame;

typedef __packed struct deviceMap
{
	unsigned char *mapPointer;
	unsigned long  mapLenth;
}sLDSW20deviceMap;


/*************************************读取控制域操作相关宏定义*********************************************************/

//#define Tmp0       (Tmp0->)

#define GetAttrOfDestDev(tmp0)           (sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[0]&0x0f)
#define GetAttrFRAME(tmp0)               ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[0]&0x0f0)>>4)

#define GetAttrDataDirect(tmp0)           (sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x01)
#define GetAttrDataDataCompare(tmp0)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x02)>>1)
#define GetAttrBROADCAST(tmp0)            ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x04)>>2)
#define GetAttrGROUP(tmp0)                ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x08)>>3)
#define GetAttrDESTADRESSVALID(tmp0)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x10)>>4)
#define GetAttrDESTGROUPVALID(tmp0)       ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x20)>>5)
#define GetAttrSOURCEADRESSVALID(tmp0)    ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x40)>>6)
#define GetAttrSOURCEGROUPVALID(tmp0)     ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x80)>>7)

#define GetAttrOfsourceDev(tmp0)           (sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[2]&0x0f)
#define GetAttrGROUPSORT(tmp0)            ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[2]&0x0f0)>>4)

#define GetAttrDATARETURNSTATUS(tmp0)       (sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x03)
#define GetAttrPASSWORDSEC(tmp0)           ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x01C)>>2)	//验证口令
#define GetAttrDATAENCODEStatus(tmp0)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x020)>>5)
#define GetAttrDATAENCODEsec(tmp0)         ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x0C0)>>6)	//加密算法版本

#define GetAttrDeviceOfBroadcast(tmp0)     (sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x0F)
#define GetAttrAUXMODELENABLE(tmp0)        ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x010)>>4)
#define GetAttrDEVBeCTRL(tmp0)             ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x0E0)>>5)

/**************************************操作控制域相关变量******************************************************/

/*改变目标设备属性*/
#define ChangeAttrOfDestDev(tmp0,x)         ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[0]&0x0f0)|x)

/*改变设备帧属性*/
#define ChangeAttrFRAME(tmp0,x)            ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[0]&0x0f)|((x&0x0f)<<4))

/*改变数据方向*/
#define ChangeAttrDataDirect(tmp0,x)           ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0fe)|x)

/*改变对比属性*/
#define ChangeAttrDataDataCompare(tmp0,x)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0fd)|(x<<1))

/*改变广播属性*/
#define ChangeAttrBROADCAST(tmp0,x)            ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0fb)|(x<<2))

#define ChangeAttrGROUP(tmp0,x)                ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0f7)|(x<<3))
/*改变目标地址有效位*/
#define ChangeAttrDESTADRESSVALID(tmp0,x)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0ef)|(x<<4))

/*改变目标群地址有效位*/
#define ChangeAttrDESTGROUPVALID(tmp0,x)       ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0df)|(x<<5))

/*改变源设备地址有效位*/
#define ChangeAttrSOURCEADRESSVALID(tmp0,x)    ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x0bf)|(x<<6))

/*改变源设备地址群有效位*/
#define ChangeAttrSOURCEGROUPVALID(tmp0,x)     ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[1]&0x077)|(x<<7))

/*改变源设备属性*/
#define ChangeAttrOfsourceDev(tmp0,x)          ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[2]&0x0f0)|x)

/*改变分组信息*/
#define ChangeAttrGROUPSORT(tmp0,x)            ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[2]&0x0f)|((x&0x0f)<<4))

/*改变数据存储方式*/
#define ChangeAttrDATARETURNSTATUS(tmp0,x)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x0fc)|x)

/*改变口令验证*/
#define ChangeAttrPASSWORDSEC(tmp0,x)           ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x0e3)|(x<<2))

/*改变加密*/
#define ChangeAttrDATAENCODEStatus(tmp0,x)      ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x0df)|(x<<5))
#define ChangeAttrDATAENCODEsec(tmp0,x)         ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[3]&0x03f)|(x<<6))

/*改变广播指令目标属性*/
#define ChangeAttrDeviceOfBroadcast(tmp0,x)     ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x0f0)|x)

/*改变辅助模块使用选项*/
#define ChangeAttrAUXMODELENABLE(tmp0,x)        ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x0ef)|(x<<4))

/*改变采集终端*/
#define ChangeAttrDEVBeCTRL(tmp0,x)             ((sPointerOfLDSW20Frame[tmp0].pAreaofFrameCtrl->FrameCtrl[4]&0x01f)|(x<<5))

/*****************************************链路操作***********************************************/
#define TmpChain                               (*(tmp0->pAreaofFrameChain))
/*获取传输链路中的链路总数*/
#define GetNumbOfChainToal(TmpChain)           (TmpChain.chainNumb&0x0f)

/*获取传输链路中的当前链路*/
#define GetNumbOfChainNow(TmpChain)            ((TmpChain.chainNumb&0x0f0)>>4)

/*获取传输链路中的链路地址（ID）*/
#define GetIDOfChain(TmpChain,xNumb)           (TmpChain.chainID[xNumb])

#define ChangeNumbOfChainToal(TmpChain,x)      ((TmpChain.chainNumb&0x0f0)|x)
#define ChangeNumbOfChainNow(TmpChain,x)       ((TmpChain.chainNumb&0x0f)|(x<<4))
#define ChangeIDOfChain(TmpChain,xNumb,xID)    (TmpChain.chainID[xNumb]=xID)

/**************************************指令域操作************************************************/
#define TmpCmd                                 (*(tmp0->pAreaofFrameCmd))

/*获取指令控制区中的参数数据长度*/
#define GetCmdOfLengthOfATTR(TmpCmd)           (TmpCmd.CmdOfATTR&0x1ff)

/*获取指令控制区中的读写属性*/
#define GetATTROfCmd(TmpCmd)                   ((TmpCmd.CmdOfATTR&0x0e00)>>9)

/*获取指令控制区中的数据区属性*/
#define GetDeviceOfCmd(TmpCmd)                 ((TmpCmd.CmdOfATTR&0x0f000)>>12)

/*改变指令控制区中的参数数据长度*/
#define ChangeCmdOfLengthOfATTR(TmpChain,x)    ((TmpCmd.CmdOfATTR&0x0f0)|（x&0x1f）)

/*改变指令控制区中的读写属性*/
#define ChangeATTROfCmd(TmpChain,x)            ((TmpCmd.CmdOfATTR&0x0f1ff)|(（x&0x07)<<9))

/*改变指令控制区中的数据区属性*/
#define ChangeDeviceOfCmd(TmpChain,x)          ((TmpCmd.CmdOfATTR&0x0fff)|(（x&0x0f)<<12))

/*****设备属性  AreaCtL[0]    */

#define   SMARTNODE                             0x00//'0000'
#define   AUXMODEL                              0x01//'0001'
#define   LOCATOR                               0x02//'0010'
#define   SWRITER                               0x03//'0011'
#define   DWRITER                               0x04//'0100'
#define   RELAYER                               0x05//'0101'
#define   BASESTATION                           0x06//'0110'
#define   HANDLE                                0x07//'0111'

#define   PCdevice                              0x0f//'1111'

/***AreaCtL[1]                                      */
#define   DataDirectUp                           1
#define   DataDirectDown                         0

#define   DataCompare                            1
#define   DataNoCompare                          0

#define   BROADCAST                              0
#define   NOBROADCAST                            1

#define   GROUP                                  1
#define   NOGROUP                                0

#define   FRAMEOFCTL                              0x00
#define   FRAMEOFDATA                             0x01
#define   FRAMEOFLOCA                             0x02
#define   FRAMEOFRESP                             0x03
#define   FRAMEOFACK                              0x04
#define   FRAMEOFCALL                             0x05
#define   FRAMEOFKILL                             0x06
#define   FRAMEOFINVENT                           0x07		//盘点帧
#define   FRAMEOFALARM                            0x08
#define   FRAMEOFHEARTBEAT                        0x09
#define   FRAMEOFTEST                             0x0a
#define   FRAMEOFBOOTUP                           0x0d

#define   FRAMEOFJOIN                             0x0f

/***AreaCtL[2]                                      */

#define   DESTADRESSVALID                          1
#define   DESTADRESSINVALID                        0
#define   DESTGROUPVALID                           1
#define   DESTGROUPINVALID                         0

#define   SOURCEADRESSVALID                        1
#define   SOURCEADRESSINVALID                      0
#define   SOURCEGROUPVALID                         1
#define   SOURCEGROUPINVALID                       0

#define   GROUPSORT                                0X00

/***AreaCtL[3]                                   */

#define  DATARETURNIMMEDIATE                     0x00//'00'
#define  DATARETURNSAVFRAM                       0x01//'01'
#define  DATARETURNSAVRAM                        0x02//'10'
#define  DATANORETURN                            0x03//'11'

#define  NOPASSWORD                              0x00//'000'
#define  PASSWORDZERO                            0x01//'001'
#define  PASSWORDONE                             0x02//'010'
#define  PASSWORDTWO                             0x03//'011'
#define  PASSWORDTHREE                           0x04//'100'
#define  PASSWORDFOUR                            0x05//'101'
#define  PASSWORDFIVE                            0x06//'110'
#define  PASSWORDSIX                             0x07//'111'

#define  DATAENCODE                               1
#define  DATANOCODE                               0

#define  DATACODEOPTIONONE                        0x00
#define  DATACODEOPTIONTWO                        0x01
#define  DATACODEOPTIONTHREE                      0x02
#define  DATACODEOPTIONTFOUR                      0x03

/***AreaCtL[4]                                   */
#define   BSMARTNODE                             0x00//'0000'
#define   BBAUXMODEL                             0x01//'0001'
#define   BLOCATOR                               0x02//'0010'
#define   BSWRITER                               0x03//'0011'
#define   BDWRITER                               0x04//'0100'
#define   BRELAYER                               0x05//'0101'
#define   BBASESTATION                           0x06//'0110'
#define   BHANDLE                                0x07//'0111'

#define   AUXMODELENABLE                           1
#define   AUXMODELDISENABLE                        0

#define   CTRLTERMINATE                    0x00// '000'
#define   CTRLRESEVER                      0x01// '001'
#define   CTRLLOCATOR                      0x02// '010'
#define   CTRLSWRITER                      0x03// '011'
#define   CTRLWRITER                       0x04// '100'
#define   CTRLRELAYER                      0x05// '101'
#define   CTRLBASESTATION                  0x06//'110'
#define   CTRLHANDLE                       0x07//'111'

/*指令控制区定义*/
#define   CmdAttrOfRD                      0
#define   CmdAttrOfWD                      1
#define   CmdAttrOfCLRbuffer               2
#define   CmdAttrOfRDRbuffer               3
#define   CmdAttrOfRStart                  4
#define   CmdAttrOfREnd                    5



extern swNOdeConfig WriterConfig;
extern sLDSW20Frame sPointerOfLDSW20Frame[MAXchannelNumb];
extern sLDSW20deviceMap pointerOfLDSW20deviceMap[16];

unsigned char checkDeviceAttr(unsigned char *Framebuffer,unsigned char channel);

unsigned char FunctionGetAttrOfDestDev(unsigned char cmmdChanel);
unsigned char FunctionGetAttrOfsourceDev(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDataDirect(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDataDataCompare(unsigned char cmmdChanel);
unsigned char FunctionGetAttrBROADCAST(unsigned char cmmdChanel);
unsigned char FunctionGetAttrGROUP(unsigned char cmmdChanel);
unsigned char FunctionGetAttrFRAME(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDESTADRESSVALID(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDESTGROUPVALID(unsigned char cmmdChanel);
unsigned char FunctionGetAttrSOURCEADRESSVALID(unsigned char cmmdChanel);
unsigned char FunctionGetAttrSOURCEGROUPVALID(unsigned char cmmdChanel);
unsigned char FunctionGetAttrGROUPSORT(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDATARETURNSTATUS(unsigned char cmmdChanel);
unsigned char FunctionGetAttrPASSWORDSEC(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDATAENCODEStatus(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDATAENCODEsec(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDeviceOfBroadcast(unsigned char cmmdChanel);
unsigned char FunctionGetAttrAUXMODELENABLE(unsigned char cmmdChanel);
unsigned char FunctionGetAttrDEVBeCTRL(unsigned char cmmdChanel);
unsigned short checkMemeryOfRAM(pwNodeCondig WRConfig,unsigned char cmmdChanel);

unsigned char FunctionChangeAttrOfDestDev(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrOfsourceDev(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDataDirect(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDataDataCompare(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrBROADCAST(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrGROUP(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrFRAME(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDESTADRESSVALID(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDESTGROUPVALID(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrSOURCEADRESSVALID(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrSOURCEGROUPVALID(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrGROUPSORT(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDATARETURNSTATUS(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrPASSWORDSEC(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDATAENCODEStatus(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDATAENCODEsec(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDeviceOfBroadcast(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrAUXMODELENABLE(unsigned char cmmdChanel,unsigned char x);
unsigned char FunctionChangeAttrDEVBeCTRL(unsigned char cmmdChanel,unsigned char x);

/*****************************************************************************************/
unsigned char checkLdsw20(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char CheckPassward(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char GetLDSW20MapNews(pwNodeCondig WRConfig);
unsigned char MakeTransFrameOf1Universal(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeTransFrameOfmultiUniversalForBaseStation(pwNodeCondig WRConfig,unsigned char cmmdChanel,unsigned char chainIndex);
unsigned char  GetPointerOfCmd(pwNodeCondig WRConfig,unsigned char cmmdChanel);
unsigned char MakeTransFrameOfWRiterUniversal(pwNodeCondig WRConfig,unsigned char cmmdChanel);

extern void clrMemeryOfAlarm(pwNodeCondig WRConfig);
extern unsigned char Ldsw20RfpackSend(pwNodeCondig WRConfig,unsigned char cmmdChanel);
extern unsigned char SendRfpackOption(pwNodeCondig WRConfig,unsigned char *sData,unsigned char cmmdChanel,unsigned char retry,unsigned short timedelay);
extern void mov_data(unsigned char *source,unsigned char *dist,unsigned char lenth);
extern void Calculate_Crc16(unsigned char * aData, unsigned char aSize );
unsigned char DealdeDataOfInventory(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void SaveDealdeDataOfInventoryToMemeryOfRAM(pwNodeCondig WRConfig,unsigned char cmmdChanel);
void GetSourceTOSetChannel(uint8_t cmmdChanel);
unsigned long Quoting(unsigned long *addr);
#endif