#include <stddef.h>
#include <stdio.h>

#include "eemFlash.h"
#include "ldsw20.h"
#include "nvm.h"




/*******************************************************************************
*
*�� Read_flash( )
*�� �ܣ���flash����
*�� �룺pWriterConfig Э��ṹ�壬�����ݳ���
*�� ����status_code��״̬
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��
*
********************************************************************************/
enum status_code Read_flash(unsigned char *pWriterConfig,uint16_t length)
{
	enum status_code error_code;
	uint16_t i=0,temp_len=0;
	
	if((length%NVMCTRL_PAGE_SIZE)!=0)
	{
		temp_len=(length/NVMCTRL_PAGE_SIZE)+1;
	}
	else
	{
		temp_len=length/NVMCTRL_PAGE_SIZE;
	}

	for(i=0;temp_len>0;i++)
	{
		error_code=nvm_read_buffer((FLASH_BASE_ADDR+i*NVMCTRL_PAGE_SIZE),\
		(unsigned char *)(pWriterConfig),\
		NVMCTRL_PAGE_SIZE);
			
		pWriterConfig+=NVMCTRL_PAGE_SIZE;
		temp_len--;
	}
	
	return error_code;
}


/*******************************************************************************
*
*�� Write_flash( )
*�� �ܣ�дflash����
*�� �룺pWriterConfig Э��ṹ�壬д���ݳ���
*�� ����status_codeд״̬
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��
*
********************************************************************************/
enum status_code Write_flash(unsigned char *pWriterConfig,uint16_t length)
{
	enum status_code error_code;
	uint16_t i=0,temp_len=0;
	
	if((length%NVMCTRL_PAGE_SIZE)!=0)
	{
		temp_len=(length/NVMCTRL_PAGE_SIZE)+1;
	}
	else
	{
		temp_len=length/NVMCTRL_PAGE_SIZE;
	}
	
	for(i=0;temp_len>0;i++)
	{
		nvm_erase_row((FLASH_BASE_ADDR+i*NVMCTRL_PAGE_SIZE));//(100+i)*NVMCTRL_PAGE_SIZE*NVMCTRL_ROW_PAGES
		error_code=nvm_write_buffer((FLASH_BASE_ADDR+i*NVMCTRL_PAGE_SIZE),\
		(unsigned char *)(pWriterConfig),\
		NVMCTRL_PAGE_SIZE);
		
		pWriterConfig+=NVMCTRL_PAGE_SIZE;
		temp_len--;
	}
	
	return error_code;
}


/*******************************************************************************
*
*�� iniFramMemery( )
*�� �ܣ��豸������ʼ��
*�� �룺
*�� ����
*�� �ߣ�
*ʱ �䣺2018.12.20
*�� ע��
*
********************************************************************************/
void iniFramMemery(void)
{
	unsigned long i;
	unsigned short rwLength;
	unsigned char *sdata;
	
	rwLength = (sizeof(WriterConfig.AttrOfDevice)+sizeof(WriterConfig.DeviceChannel)+3);
	/*+sizeof(WriterConfig.Password)+sizeof(WriterConfig.MaprecordOfAlarm)+\sizeof(WriterConfig.LocationDataArea)+3;*/
	
	sdata = (unsigned char *)(&WriterConfig);
	for(i=0;i<(sizeof(WriterConfig)-4);i++)
	{
		*sdata++ =0;
	}

	
	//Read_flash((unsigned char *)&WriterConfig,rwLength);
		
	#ifdef  REDeviceID
	WriterConfig.ini_flag[0] = 0;
	#endif
	//�жϴӴ洢���ж�ȡ�������Ƿ���ȷ�ı�־λ
	if((WriterConfig.ini_flag[0]==0x5a)  &&(WriterConfig.ini_flag[1]==0xa5)&&(WriterConfig.ini_flag[2]==0x65))
	{
		//WriterConfig.AttrOfDevice.GroupId=GROUPID;
	}
	else 
	{
		sdata =(unsigned char *)&WriterConfig;
		for(i=0;i<sizeof(WriterConfig);i++)
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
        WriterConfig.DeviceChannel.F7= 0x17;    //����ģ��Ĭ�ϳ�ʼ��ͨ��
        WriterConfig.DeviceChannel.T0= 0x1A;
        WriterConfig.DeviceChannel.T1= 0x17;
        WriterConfig.DeviceChannel.T2= 0x17;
        WriterConfig.DeviceChannel.T3= 0x17;		
		
		WriterConfig.AttrOfDevice.DeviceID=DEVICEID;
		WriterConfig.AttrOfDevice.GroupId=GROUPID;
        
		WriterConfig.AttrOfDevice.PCId =150;
		WriterConfig.AttrOfDevice.RspTime=1;
		WriterConfig.AttrOfDevice.HeartBeatenTime = 10000;
		WriterConfig.AttrOfDevice.ComRateConfig.RF[0]=0x00;
		WriterConfig.AttrOfDevice.ComRateConfig.RF[1]=0x03;    
		WriterConfig.ini_flag[0]=0x5a;
		WriterConfig.ini_flag[1]=0xa5;
		WriterConfig.ini_flag[2]=0x65;	
		
		//Write_flash((unsigned char *)&WriterConfig,rwLength);
		nop();
	}
	WriterConfig.spiDataLength =rwLength;
	//GetLDSW20MapNews(WriterConfig);
	// Getchannel_timer(WRConfig);
	Getchannel_timer(&WriterConfig);
}

