#include <stdio.h>

#include "main.h"
#include "device.h"
#include "config.h"
#include "sys.h"
#include "system.h"
#include "sysTimer.h"
#include "sio2host.h"
#include "asf.h"
#include "trx_access.h"
#include "tcc.h"
#include "io_define.h"
#include "wdt.h"


/*******************************************************************************
*
*函 数：InitSystem( )
*功 能：系统外设初始化函数
*输 入：none
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：none
*
********************************************************************************/
void InitSystem(void)
{
  sio2host_init();    //串口初始化   PA08 09
  configure_tcc2();	//定时器初始化
  configure_wdt();	//独立看门狗初始化
  wdt_reset_count();  //喂狗 8s溢出
}

/*******************************************************************************
*
*函 数：Runing_Status( )
*功 能：运行指示灯函数
*输 入：none
*输 出：
*作 者：
*时 间：2019.1.8
*备 注：none
*
********************************************************************************/
void Runing_Status(void)
{
  static uint16_t cnt_led=0;
  
  cnt_led++;
  
  if(cnt_led>500)   
  {
    LED1_TOGGLE();
    cnt_led=0;
  }
}

/*******************************************************************************
*
*函 数：do_UARTcmd( )
*功 能：串口数据处理函数
*输 入：WRConfig，节点串口接收信息存储区,cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：none
*.
********************************************************************************/
void do_UARTcmd(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{	 
  /*是否需要解析，只有标志为4才进行数据解析*/
  if(WRConfig->uartParameter[cmmdChanel].uartStatus != 4)	
  {
    return;
  }
  
  cpu_irq_disable();  //关中断
  
  WRConfig->uartParameter[cmmdChanel].uartStatus=0;		//将数据接收状态位清零  
  
  /*如果是从射频0通道来的数据则直接通过串口发送*/ 
  if(cmmdChanel==0)  
  {
    /*拷贝RX射频数据*/
    mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],(WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+3));
    
    WRConfig->uartParameter[0].uartTxdBuffer[0]=0X55;
    WRConfig->uartParameter[0].uartTxdBuffer[1]=0XAA;
    WRConfig->uartParameter[0].uartTxdBuffer[2]+=  1;   //数据字节长度+1
    
    /*增加一个字节长度的rssi*/
    WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[(WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+3)]=WRConfig->uartParameter[cmmdChanel].IssiStrength;   
    Calculate_Crc16(&WRConfig->uartParameter[0].uartTxdBuffer[3], WRConfig->uartParameter[0].uartTxdBuffer[2]);     //重新计算CRC
    USART1_TxBuf(&WRConfig->uartParameter[0].uartTxdBuffer[0], (WRConfig->uartParameter[0].uartTxdBuffer[2]+5));    //串口发送数据
  }
  else
  {
    excuteLDSW20(WRConfig,cmmdChanel);                  //数据协议解析	
  }
  
  WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;//恢复初始射频通道
  radio_ini(WRConfig,0);
  RxdRF6936(cmmdChanel);
  
  cpu_irq_enable();   //开中断
}

/*******************************************************************************
*
*函 数：main( )
*功 能：主函数
*输 入：none
*输 出：0
*作 者：
*时 间：2018.12.20
*备 注：none
*
********************************************************************************/
int main(void)
{			
  system_init();	//系统初始化
  delay_init();		//系统延时初始化 
  configure_nvm();	//flash初始化
  iniFramMemery();	//初始化结构体参数 
  SYS_Init();		//SPI和RF233初始化 
  InitSystem();		//外设初始化
  initRFOfAll();	//配置RF233
  cpu_irq_enable();	//使能中断	 
  
  while(1)
  {	
    wdt_reset_count();				//喂狗		
    do_UARTcmd(&WriterConfig,0);	//解析接收到的射频数据        
    do_UARTcmd(&WriterConfig,1);	//解析接收到的串口数据
    Runing_Status();				//运行指示灯
  }
}
