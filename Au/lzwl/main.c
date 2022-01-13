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
*�� ����InitSystem( )
*�� �ܣ�ϵͳ�����ʼ������
*�� �룺none
*�� ����
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��none
*
********************************************************************************/
void InitSystem(void)
{
  sio2host_init();    //���ڳ�ʼ��   PA08 09
  configure_tcc2();	//��ʱ����ʼ��
  configure_wdt();	//�������Ź���ʼ��
  wdt_reset_count();  //ι�� 8s���
}

/*******************************************************************************
*
*�� ����Runing_Status( )
*�� �ܣ�����ָʾ�ƺ���
*�� �룺none
*�� ����
*�� �ߣ�
*ʱ �䣺2019.1.8
*�� ע��none
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
*�� ����do_UARTcmd( )
*�� �ܣ��������ݴ�����
*�� �룺WRConfig���ڵ㴮�ڽ�����Ϣ�洢��,cmmdChanel��Э������ͨ��(��Э�������Ǵ��ĸ�ͨ������ģ�ͨ��ȡֵ0-5)
*�� ����
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��none
*.
********************************************************************************/
void do_UARTcmd(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{	 
  /*�Ƿ���Ҫ������ֻ�б�־Ϊ4�Ž������ݽ���*/
  if(WRConfig->uartParameter[cmmdChanel].uartStatus != 4)	
  {
    return;
  }
  
  cpu_irq_disable();  //���ж�
  
  WRConfig->uartParameter[cmmdChanel].uartStatus=0;		//�����ݽ���״̬λ����  
  
  /*����Ǵ���Ƶ0ͨ������������ֱ��ͨ�����ڷ���*/ 
  if(cmmdChanel==0)  
  {
    /*����RX��Ƶ����*/
    mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],&WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[0],(WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+3));
    
    WRConfig->uartParameter[0].uartTxdBuffer[0]=0X55;
    WRConfig->uartParameter[0].uartTxdBuffer[1]=0XAA;
    WRConfig->uartParameter[0].uartTxdBuffer[2]+=  1;   //�����ֽڳ���+1
    
    /*����һ���ֽڳ��ȵ�rssi*/
    WRConfig->uartParameter[cmmdChanel].uartTxdBuffer[(WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[2]+3)]=WRConfig->uartParameter[cmmdChanel].IssiStrength;   
    Calculate_Crc16(&WRConfig->uartParameter[0].uartTxdBuffer[3], WRConfig->uartParameter[0].uartTxdBuffer[2]);     //���¼���CRC
    USART1_TxBuf(&WRConfig->uartParameter[0].uartTxdBuffer[0], (WRConfig->uartParameter[0].uartTxdBuffer[2]+5));    //���ڷ�������
  }
  else
  {
    excuteLDSW20(WRConfig,cmmdChanel);                  //����Э�����	
  }
  
  WRConfig->DeviceChannel.channel_temp=RFchanelOfDevice;//�ָ���ʼ��Ƶͨ��
  radio_ini(WRConfig,0);
  RxdRF6936(cmmdChanel);
  
  cpu_irq_enable();   //���ж�
}

/*******************************************************************************
*
*�� ����main( )
*�� �ܣ�������
*�� �룺none
*�� ����0
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��none
*
********************************************************************************/
int main(void)
{			
  system_init();	//ϵͳ��ʼ��
  delay_init();		//ϵͳ��ʱ��ʼ�� 
  configure_nvm();	//flash��ʼ��
  iniFramMemery();	//��ʼ���ṹ����� 
  SYS_Init();		//SPI��RF233��ʼ�� 
  InitSystem();		//�����ʼ��
  initRFOfAll();	//����RF233
  cpu_irq_enable();	//ʹ���ж�	 
  
  while(1)
  {	
    wdt_reset_count();				//ι��		
    do_UARTcmd(&WriterConfig,0);	//�������յ�����Ƶ����        
    do_UARTcmd(&WriterConfig,1);	//�������յ��Ĵ�������
    Runing_Status();				//����ָʾ��
  }
}
