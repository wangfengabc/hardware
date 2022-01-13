#ifndef EEMFLASH_H_ 
#define EEMFLASH_H_

#include "auxdevice.h"

#define FLASH_BASE_ADDR		0xD000  //FLSH读写基地址


#define DEVICEID			0xFFFFFFFF     //设备ID（地址）
#define GROUPID				0x64    //群设备ID（地址）

void iniFramMemery(void);

extern void Getchannel_timer(pwNodeCondig WRConfig);
extern unsigned char GetLDSW20MapNews(pwNodeCondig WRConfig);

enum status_code Write_flash(unsigned char *pWriterConfig,uint16_t length); //写flash函数
enum status_code Read_flash(unsigned char *pWriterConfig,uint16_t length);  //读flash函数

#endif

