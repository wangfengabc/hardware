/**
 * \file sio2host.c
 *
 * \brief Handles Serial I/O  Functionalities For the Host Device
 *
 * Copyright (c) 2013-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 */

/* === INCLUDES ============================================================ */

#include "asf.h"
#include "sio2host.h"
#include "conf_sio2host.h"
#include "auxdevice.h"
#include "io_define.h"

extern swNOdeConfig WriterConfig;

/* === TYPES =============================================================== */

/* === MACROS ============================================================== */

/* === PROTOTYPES ========================================================== */

/* === GLOBALS ========================================================== */
#if SAMD || SAMR21 || SAML21 || SAMR30
static struct usart_module host_uart_module;
#else
static usart_serial_options_t usart_serial_options = {
	.baudrate     = USART_HOST_BAUDRATE,
	.charlength   = USART_HOST_CHAR_LENGTH,
	.paritytype   = USART_HOST_PARITY,
	.stopbits     = USART_HOST_STOP_BITS
};
#endif

/**
 * Receive buffer
 * The buffer size is defined in sio2host.h
 */
static uint8_t serial_rx_buf[SERIAL_RX_BUF_SIZE_HOST];

/**
 * Receive buffer head
 */
static uint8_t serial_rx_buf_head;

/**
 * Receive buffer tail
 */
static uint8_t serial_rx_buf_tail;

/**
 * Number of bytes in receive buffer
 */
static uint8_t serial_rx_count;

/* === IMPLEMENTATION ====================================================== */

void sio2host_init(void)
{
	#if SAMD || SAMR21 || SAML21 || SAMR30
	struct usart_config host_uart_config;
	/* Configure USART for unit test output */
	usart_get_config_defaults(&host_uart_config);
	host_uart_config.mux_setting = USART_RX_1_TX_0_XCK_1;
	//host_uart_config.pinmux_pad0 = HOST_SERCOM_PINMUX_PAD0;
	//host_uart_config.pinmux_pad1 = HOST_SERCOM_PINMUX_PAD1;
	//host_uart_config.pinmux_pad2 = HOST_SERCOM_PINMUX_PAD2;
	//host_uart_config.pinmux_pad3 = HOST_SERCOM_PINMUX_PAD3;	
	host_uart_config.pinmux_pad0 = PINMUX_PA08C_SERCOM0_PAD0;
	host_uart_config.pinmux_pad1 = PINMUX_PA09C_SERCOM0_PAD1;
	host_uart_config.pinmux_pad2 = PINMUX_UNUSED;
	host_uart_config.pinmux_pad3 = PINMUX_UNUSED;
	host_uart_config.baudrate    = USART_HOST_BAUDRATE;
	stdio_serial_init(&host_uart_module, USART_HOST, &host_uart_config);
	usart_enable(&host_uart_module);
	/* Enable transceivers */
	usart_enable_transceiver(&host_uart_module, USART_TRANSCEIVER_TX);
	usart_enable_transceiver(&host_uart_module, USART_TRANSCEIVER_RX);
	#else
	stdio_serial_init(USART_HOST, &usart_serial_options);
	#endif
	USART_HOST_RX_ISR_ENABLE();
//#if SAMD || SAMR21 || SAML21 || SAMR30
	//struct usart_config host_uart_config;
	///* Configure USART for unit test output */
	//usart_get_config_defaults(&host_uart_config);
	//host_uart_config.mux_setting = USART_RX_1_TX_0_XCK_1;
//
	//host_uart_config.pinmux_pad0 = PINMUX_PA08C_SERCOM0_PAD0;//TX
	//host_uart_config.pinmux_pad1 = PINMUX_PA09C_SERCOM0_PAD1;//RX
	//host_uart_config.pinmux_pad2 = PINMUX_UNUSED;
	//host_uart_config.pinmux_pad3 = PINMUX_UNUSED;
	//host_uart_config.baudrate    = 9600;
	//host_uart_config.run_in_standby   = false;
	//stdio_serial_init(&host_uart_module, SERCOM0, &host_uart_config);
	//usart_enable(&host_uart_module);
	///* Enable transceivers */
	//usart_enable_transceiver(&host_uart_module, USART_TRANSCEIVER_TX);
	//usart_enable_transceiver(&host_uart_module, USART_TRANSCEIVER_RX);
//#else
	//stdio_serial_init(SERCOM0, &usart_serial_options);
//#endif
	//USART_HOST_RX_ISR_ENABLE();
}

uint8_t sio2host_tx(uint8_t *data, uint8_t length)
{
#if SAMD || SAMR21 || SAML21 || SAMR30
	status_code_genare_t status;
#else
	status_code_t status;
#endif /*SAMD || SAMR21 || SAML21 */

	do {
#if SAMD || SAMR21 || SAML21 || SAMR30
		status
			= usart_serial_write_packet(&host_uart_module,
				(const uint8_t *)data, length);
#elif SAM4S || SAM4E
        status = usart_serial_write_packet((Usart *)USART_HOST,
				(const uint8_t *)data,
				length);
#else
	    status = usart_serial_write_packet(USART_HOST,
				(const uint8_t *)data,
				length);
#endif
	} while (status != STATUS_OK);
	return length;
}

uint8_t sio2host_rx(uint8_t *data, uint8_t max_length)
{
	uint8_t data_received = 0;
	if(serial_rx_buf_tail >= serial_rx_buf_head)
	{
		serial_rx_count = serial_rx_buf_tail - serial_rx_buf_head;
	}
	else
	{
		serial_rx_count = serial_rx_buf_tail + (SERIAL_RX_BUF_SIZE_HOST - serial_rx_buf_head);
	}
	
	if (0 == serial_rx_count) {
		return 0;
	}

	if (SERIAL_RX_BUF_SIZE_HOST <= serial_rx_count) {
		/*
		 * Bytes between head and tail are overwritten by new data.
		 * The oldest data in buffer is the one to which the tail is
		 * pointing. So reading operation should start from the tail.
		 */
		serial_rx_buf_head = serial_rx_buf_tail;

		/*
		 * This is a buffer overflow case. But still only the number of
		 * bytes equivalent to
		 * full buffer size are useful.
		 */
		serial_rx_count = SERIAL_RX_BUF_SIZE_HOST;

		/* Bytes received is more than or equal to buffer. */
		if (SERIAL_RX_BUF_SIZE_HOST <= max_length) {
			/*
			 * Requested receive length (max_length) is more than
			 * the
			 * max size of receive buffer, but at max the full
			 * buffer can be read.
			 */
			max_length = SERIAL_RX_BUF_SIZE_HOST;
		}
	} else {
		/* Bytes received is less than receive buffer maximum length. */
		if (max_length > serial_rx_count) {
			/*
			 * Requested receive length (max_length) is more than
			 * the data
			 * present in receive buffer. Hence only the number of
			 * bytes
			 * present in receive buffer are read.
			 */
			max_length = serial_rx_count;
		}
	}

	data_received = max_length;
	while (max_length > 0) {
		/* Start to copy from head. */
		*data = serial_rx_buf[serial_rx_buf_head];
		data++;
		max_length--;
		if ((SERIAL_RX_BUF_SIZE_HOST - 1) == serial_rx_buf_head) {
			serial_rx_buf_head = 0;
		}
		else
		{
			serial_rx_buf_head++;
		}
	}
	return data_received;
}

uint8_t sio2host_getchar(void)
{
	uint8_t c;
	while (0 == sio2host_rx(&c, 1)) {
	}
	return c;
}

void sio2host_putchar(uint8_t ch)
{
	sio2host_tx(&ch, 1);
}

int sio2host_getchar_nowait(void)
{
	uint8_t c;
	int back = sio2host_rx(&c, 1);
	if (back >= 1) {
		return c;
	} else {
		return (-1);
	}
}

unsigned char  CheckSum(unsigned char *uBuff, unsigned char uBuffLen)
{
	unsigned char i,uSum=0;
	for(i=0;i<uBuffLen;i++)
	{
		uSum = uSum + uBuff[i];
	}
	uSum = (~uSum) + 1;
	return uSum;
}


/***************************************************
  Function: int USART1_TxBuf(uint8_t *buffer, int nbytes)
  Description: 发送buffer到 串口1 @brief Transmit buffer to USART1
  param:  buffer Array of characters to send；nbytes Number of bytes to transmit
  Calls:        
  Called By:      
  Table Accessed:
  Table Updated:
  Input:               
  Output:         
  Return:  Number of bytes sent
  Timers:  2013.07.15
  author:  ME 	
***************************************************/
int USART1_TxBuf(uint8_t *buffer, int nbytes)
{
  int i;
  for (i = 0; i < nbytes; i++)
  {
    sio2host_putchar(*buffer++);
  }
  return nbytes;
}

/*******************************************************************************
*
*函 数：receiveUartNews( )
*功 能：串口数据接收函数
*输 入：WRConfig，节点串口接收信息存储区,tempData，串口中断接收单个字符，
	    cmmdChanel，协议数据通道(即协议数据是从哪个通道进入的，通道取值0-5)
		
*输 出：
*作 者：
*时 间：2019.1.7
*备 注：
*
********************************************************************************/
void receiveUartNews(pwNodeCondig WRConfig,unsigned char tempData,unsigned char cmmdChanel)
{
	switch(WRConfig->uartParameter[cmmdChanel].uartStatus)
	{
		case 0x00:
		if(tempData==0x55){
			WRConfig->uartParameter[cmmdChanel].uartRxdtemp[0]=0x55;
			WRConfig->uartParameter[cmmdChanel].uartStatus =1;
			}else{
			WRConfig->uartParameter[cmmdChanel].uartStatus =0;
		}
		break;
		
		
		case 0x01:
		if(tempData==0x0aa){

			WRConfig->uartParameter[cmmdChanel].uartRxdtemp[1]=0xaa;
			WRConfig->uartParameter[cmmdChanel].uartStatus =2;
			}else{
			WRConfig->uartParameter[cmmdChanel].uartStatus =0;
		}
		break;
		
		case 0x02:
		if(tempData <= 127){
			WRConfig->uartParameter[cmmdChanel].UartRawDataLen=tempData;
			WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2]=tempData;
			WRConfig->uartParameter[cmmdChanel].uartRxdPointer=3;
			WRConfig->uartParameter[cmmdChanel].uartStatus =3;
			}else{
			WRConfig->uartParameter[cmmdChanel].uartStatus=0;
			WRConfig->uartParameter[cmmdChanel].uartRxdPointer = 0;
		}
		
		WRConfig->uartParameter[cmmdChanel].uartTimer_count=0;
		break;
		
		case 0x03:
		WRConfig->uartParameter[cmmdChanel].uartTimer_count=0;
		WRConfig->uartParameter[cmmdChanel].uartRxdtemp[WRConfig->uartParameter[cmmdChanel].uartRxdPointer++]=tempData;
		
		if(WRConfig->uartParameter[cmmdChanel].uartRxdPointer == (WRConfig->uartParameter[cmmdChanel].UartRawDataLen+5))
		{
			//if(CRC_16( &WRConfig->uartParameter[cmmdChanel].uartRxdtemp[3],(WRConfig->uartParameter[cmmdChanel].UartRawDataLen+2) )==0x00)
			//{
				mov_data(&WRConfig->uartParameter[cmmdChanel].uartRxdtemp[0],&WRConfig->uartParameter[cmmdChanel].uartRxdBuffer[0],\
				(WRConfig->uartParameter[cmmdChanel].uartRxdtemp[2]+5));
				WRConfig->uartParameter[cmmdChanel].uartReci_length = WRConfig->uartParameter[cmmdChanel].UartRawDataLen;
				WRConfig->uartParameter[cmmdChanel].uartRxdPointer = 0;
				WRConfig->uartParameter[cmmdChanel].uartStatus=4;
				WRConfig->uartParameter[cmmdChanel].uartTimer_count=0;
				//WriterConfig.uartParameter[cmmdChanel].uartRxcnt = 1;
			//}
		}
		break;
		
		default:
		//RxData1 = 0;
		WRConfig->uartParameter[cmmdChanel].uartTimer_count=0;
		//WRConfig->uartParameter[cmmdChanel].uartStatus=0;
		WRConfig->uartParameter[cmmdChanel].uartRxdPointer = 0;
		break;
	}
}

void USART_HOST_ISR_VECT(uint8_t instance)
{
	
	uint8_t dataBuffer;
	
	usart_serial_getchar(&host_uart_module, &dataBuffer);
	receiveUartNews(&WriterConfig,dataBuffer,1);
    //DealSerialCom(&WriterConfig,dataBuffer,1);
}

/* EOF */
//=========================================================================
//函数名称：  void CommChannelTimerCovery(Pdevicepara RWpara,unsigned char cmmdChanel)
//函数参数：Pdevicepara RWpara,
//          unsigned char cmmdChanel
//函数返回：无
//功能概要：串口数据接收现场恢复函数。
//=========================================================================
void CommChannelTimerCovery(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	if(WRConfig->uartParameter[cmmdChanel].uartStatus ==0x00){
		return;
	}
	WRConfig->uartParameter[cmmdChanel].uartTimer_count++;
	if(WRConfig->uartParameter[cmmdChanel].uartTimer_count > 5){
		WRConfig->uartParameter[cmmdChanel].uartStatus=0;
		WRConfig->uartParameter[cmmdChanel].uartTimer_count=0;
	}
}
