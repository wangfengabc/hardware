/******************************************************************************
* $Id: QSTHAL.h    jungerzou@gmail.com $
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



#ifndef __QSTHAL_H__
#define __QSTHAL_H__

#ifdef __cplusplus

extern "C" {

#endif


#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define QST_SUCCESS			1	///< The return value. It represents success.
#define QST_ERROR			0	///< The return value. It represents error.
#define QST_FAIL			-1	///< The return value. It represents the function fails.

typedef unsigned char BYTE;
typedef	unsigned char	uint8;
typedef	short           int16;
typedef long            int32;
typedef	unsigned short	uint16;
typedef unsigned long	uint32;

//#define SNG2DBLBYTE(high, low)		((int16)((((uint16)(high))<<8)+(uint16)(low)))

uint8_t QMA_7981_DEVICE_CHECK(void);
void QST_IIC_Write(uint8 chip_addr, uint8 reg, uint8  value);
void QST_IIC_Read(uint8 chip_addr,  uint8  *data, uint8  numberOfBytesToRead);	
void QMA_7981_DEVICE_INIT(void);
void qma7981_read_raw_xyz(float *data);
void QMA_6981_DEVICE_INIT(void);
void LZWL_QMA7981_INIT(void);
unsigned char QST_IIC_ReadByte(uint8 chip_addr,  uint8  reg);
#ifdef __cplusplus
}
#endif
#endif 
