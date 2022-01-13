#ifndef EEMFLASH_H_ 
#define EEMFLASH_H_

#include "auxdevice.h"

#define FLASH_BASE_ADDR		0xD000  //FLSH��д����ַ


#define DEVICEID			0xFFFFFFFF     //�豸ID����ַ��
#define GROUPID				0x64    //Ⱥ�豸ID����ַ��

void iniFramMemery(void);

extern void Getchannel_timer(pwNodeCondig WRConfig);
extern unsigned char GetLDSW20MapNews(pwNodeCondig WRConfig);

enum status_code Write_flash(unsigned char *pWriterConfig,uint16_t length); //дflash����
enum status_code Read_flash(unsigned char *pWriterConfig,uint16_t length);  //��flash����

#endif

