/******************************************************************************
* $Id: QSTHAL.c    jungerzou@gmail.com $
******************************************************************************
*
* Copyright (C) 2014 QST Corp.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/



#include "QMA7981.h"
#include "SoftwareI2C.h"
#include "io_define.h"
#include "delay.h"

//const byte AS_WA_QMC =  0x24; //7981  6981
//const byte AS_RA_QMC  =  0x25;//7981  6981

#define __isNegative(_val)  (_val&0x80)

void QST_IIC_Write(uint8 chip_addr, uint8 reg, uint8  value)
{
  SoftI2C_start();
  SoftI2C_write_byte(chip_addr );
  SoftI2C_write_byte(reg);
  SoftI2C_write_byte(value);
  SoftI2C_stop();
}
unsigned char QST_IIC_ReadByte(uint8 chip_addr,  uint8  reg)
{
  unsigned char val = 0;
  
  SoftI2C_start();
  SoftI2C_write_byte(chip_addr);
  SoftI2C_write_byte(reg);
  SoftI2C_start();
  SoftI2C_write_byte(chip_addr|0x01);
  val = SoftI2C_read_byte(1);
  SoftI2C_stop();
  
  return val;
}

void QST_IIC_Read(uint8 chip_addr,  uint8  *data, uint8  numberOfBytesToRead)
{
  unsigned char val = data[0];
  unsigned char i=0;
  for(i=0;i<numberOfBytesToRead;i++)
  {
    data[i]= QST_IIC_ReadByte(chip_addr,val);
    val++;
  }
  
  ///
}
void QMA_7981_DEVICE_INIT(void)
{
	QST_IIC_Write(0x24,0x11,0x80);  //获取寄存器默认值
	
	QST_IIC_Write(0x24,0x10,0x2a);	//设置带宽	
	QST_IIC_Write(0x24,0x0f,0x04);	//设置最大范围
  
	QST_IIC_Write(0x24,0x12,0x8f); 
	QST_IIC_Write(0x24,0x13,0x10);  
	    
	QST_IIC_Write(0x24,0x14,0x04);  
	QST_IIC_Write(0x24,0x15,0x14);
	 
	QST_IIC_Write(0x24,0x32,0x02);	//设置自检激励正值
 

	QST_IIC_Write(0x24,0x27,0x60); 
	QST_IIC_Write(0x24,0x28,0x60);      
	QST_IIC_Write(0x24,0x29,0x60); 
   
	QST_IIC_Write(0x24,0x1d,0x01);	//开启步数中断 
	QST_IIC_Write(0x24,0x16,0x40);	//开启步数中断 	
	QST_IIC_Write(0x24,0x19,0x40);	//中断输出口选择INT1 
	QST_IIC_Write(0x24,0x20,0x05);	//推挽输出 高电平触发
     
	//set mode 
	QST_IIC_Write(0x24,0x11,0x80);
	QST_IIC_Write(0x24,0x5F,0x80); 
	QST_IIC_Write(0x24,0x5F,0x00); 
	QST_IIC_Write(0x24,0xff,0x01);
}

void QMA_6981_DEVICE_INIT(void)
{ 
 // QST_IIC_Write(0x24,0x36,0xb6);
  
 // QST_IIC_Write(0x24,0xff,0x05);//delay 5ms
  
//  QST_IIC_Write(0x24,0x36,0x00);
  
  QST_IIC_Write(0x24,0x0f,0x02);   // scale  =4G 
  
  QST_IIC_Write(0x24,0x10,0x05);  // 125Hz 
  
  QST_IIC_Write(0x24,0x11,0x80);  //set mode 
  
  /*
  //interrupt comfiguration
  QST_IIC_Write(0x24,0x2A,0x80); 
  
  QST_IIC_Write(0x24,0x2B,0x01);  //配置为4g时，val值要稍小点，配置为2g或者g时，val值为0x03
  
  QST_IIC_Write(0x24,0x16,0x20);
  
  */
}
  
float IicData[3]={0};
void qma7981_read_raw_xyz(float *data)
{	
  unsigned char databuf[6] = {0}; 
  short rawdata[3]={0,0,0}; //int16

  databuf[0]=0x01;
  
  QST_IIC_Read(0x24,databuf,6);
  
  nop();

  rawdata[0] = (short)((databuf[1]<<8)|(databuf[0]));
  rawdata[1] = (short)((databuf[3]<<8)|(databuf[2]));
  rawdata[2] = (short)((databuf[5]<<8)|(databuf[4]));
  rawdata[0] = rawdata[0]>>2;
  rawdata[1] = rawdata[1]>>2;
  rawdata[2] = rawdata[2]>>2;
  
  nop();
  data[0]=rawdata[0]/2048.0f*9.8f;
  data[1]=rawdata[1]/2048.0f*9.8f;
  data[2]=rawdata[2]/2048.0f*9.8f; 
  
  
  IicData[0] =data[0]/9.8f;
  IicData[1] =data[1]/9.8f;
  IicData[2] =data[2]/9.8f;   
nop();

  //printf("read x,y,z ")
}

uint8_t QMA_7981_DEVICE_CHECK(void)
{
  unsigned char buf[6]={0};
  buf[0] = 0x00;
  QST_IIC_Read(0x24,buf,1);
  
  if((buf[0]>=0xe0) && (buf[0]<=0xe6))
  {
    return TRUE;
  }
  return FALSE;
}


#define QMA681_AXIS_X 0
#define QMA681_AXIS_Y 1
#define QMA681_AXIS_Z 2
int QMA6981_GetACCData(float *data)
{
  
  unsigned char databuf[6] = { 0,0,0,0,0,0};
  signed short  Accdata[3];
  int i;
  // read data 
  //CleanUart();
  databuf[0] = 0x01; //  addr
  QST_IIC_Read(0x24,databuf,6);
  
  Accdata[QMA681_AXIS_X] = (signed short)((databuf[QMA681_AXIS_X * 2 + 1] << 2) | (databuf[QMA681_AXIS_X * 2] >> 6));
  Accdata[QMA681_AXIS_Y] = (signed short)((databuf[QMA681_AXIS_Y * 2 + 1] << 2) | (databuf[QMA681_AXIS_Y * 2] >> 6));
  Accdata[QMA681_AXIS_Z] = (signed short)((databuf[QMA681_AXIS_Z * 2 + 1] << 2) | (databuf[QMA681_AXIS_Z * 2] >> 6));
  
  for(i=0;i<3;i++)				
  {					//because the data is store in binary complement number formation in computer system
    if ( Accdata[i] == 0x0200 ) 	//so we want to calculate actual number here
      Accdata[i]= -512;			//10bit resolution, 512= 2^(10-1)
    else if ( Accdata[i] & 0x0200 )     //transfor format
    {					//printk("data 0 step %x \n",data[i]);
      Accdata[i] -= 0x1;		//printk("data 1 step %x \n",data[i]);
      Accdata[i] = ~Accdata[i];		//printk("data 2 step %x \n",data[i]);
      Accdata[i] &= 0x01ff;		//printk("data 3 step %x \n\n",data[i]);
      Accdata[i] = -Accdata[i];	
    }
  }
    
  data[0]= Accdata[0]/128.0f*9.80f;
  data[1]= Accdata[1]/128.0f*9.80f;
  data[2]=-Accdata[2]/128.0f*9.80f;
  
  IicData[0] =data[0]/9.8f;
  IicData[1] =data[1]/9.8f;
  IicData[2] =data[2]/9.8f;
  
  nop();
  return 0;
}

void LZWL_QMA7981_INIT(void)
{
	QMA7981_OPEN();
	delay_ms(10);
	QMA_7981_DEVICE_INIT();
}