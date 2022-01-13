/**
 * \file phy.c
 *
 * \brief AT86RF233 PHY implementation
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 *
 */

#ifdef PHY_AT86RF233

/*- Includes ---------------------------------------------------------------*/
#include <stdbool.h>
#include "phy.h"
#include "sal.h"
#include "trx_access.h"
#include "delay.h"
#include "at86rf233.h"
#include "config.h"
#include "nwk.h"
#include "ldsw20rf.h"
#include "string.h"
#include "io_define.h"

extern swNOdeConfig WriterConfig;

/*- Definitions ------------------------------------------------------------*/
#define PHY_CRC_SIZE    2
#define SFD_VALUE       0X59
/*- Types ------------------------------------------------------------------*/
typedef enum {
	PHY_STATE_INITIAL,
	PHY_STATE_IDLE,
	PHY_STATE_SLEEP,
	PHY_STATE_TX_WAIT_END,
} PhyState_t;

/*- Prototypes -------------------------------------------------------------*/
void phyWriteRegister(uint8_t reg, uint8_t value);
uint8_t phyReadRegister(uint8_t reg);
void phyWaitState(uint8_t state);
void phyTrxSetState(uint8_t state);
void phySetRxState(void);

/*- Variables --------------------------------------------------------------*/
static PhyState_t phyState = PHY_STATE_INITIAL;
static uint8_t phyRxBuffer[128];
static bool phyRxState;

/*- Implementations --------------------------------------------------------*/

uint8_t MPDUPayload[127] = {0};


void initRFOfAll(void)
{
	radio_ini(&WriterConfig,0);
	RxdRF6936(0);
	OPENPOWER();
}

void PHY_Init(void)
{
	trx_spi_init();
	PhyReset();
	
	do {phyWriteRegister(TRX_STATE_REG, TRX_CMD_TRX_OFF);
	} while (TRX_STATUS_TRX_OFF !=
			(phyReadRegister(TRX_STATUS_REG) & TRX_STATUS_MASK));

	phyWriteRegister(TRX_CTRL_1_REG,
			(1 << TX_AUTO_CRC_ON) | (3 << SPI_CMD_MODE) |
			(1 << IRQ_MASK_MODE) | (1 << PA_EXT_EN));

	phyWriteRegister(TRX_CTRL_2_REG,
			(1 << RX_SAFE_MODE) | (1 << OQPSK_SCRAM_EN));
	
}

void PHY_SetSFD_Value(uint8_t SFD_Value)
{
	uint8_t reg;
	
	reg = phyReadRegister(SFD_VALUE_REG) & ~0xff;
	phyWriteRegister(SFD_VALUE_REG, reg | SFD_Value);
}

void initAtrf233(void)
{
	PhyReset();
	do {phyWriteRegister(TRX_STATE_REG, TRX_CMD_TRX_OFF);
	} while (TRX_STATUS_TRX_OFF !=
	(phyReadRegister(TRX_STATUS_REG) & TRX_STATUS_MASK));

	phyWriteRegister(TRX_CTRL_1_REG,
	(1 << TX_AUTO_CRC_ON) | (3 << SPI_CMD_MODE) |
	(1 << IRQ_MASK_MODE) | (1 << PA_EXT_EN));

	phyWriteRegister(TRX_CTRL_2_REG,
	(1 << RX_SAFE_MODE) | (1 << OQPSK_SCRAM_EN));
	
}

void PHY_SetDataRate(uint8_t DataRate)
{
	uint8_t reg;
	
	reg = phyReadRegister(TRX_CTRL_2_REG) & ~0x07;
	phyWriteRegister(TRX_CTRL_2_REG, reg | DataRate);
}

void appInit(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	NWK_SetAddr(APP_ADDR);
	NWK_SetPanId(APP_PANID);
	setRfPowerOfDevice(WRConfig,cmmdChanel);
	SelectChanel(WRConfig,cmmdChanel);
	PHY_SetRxState(true);
}

void radio_ini(pwNodeCondig WRConfig,unsigned char cmmdChanel)
{
	initAtrf233();
	appInit(WRConfig,cmmdChanel);
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetRxState(bool rx)
{
	phyRxState = rx;
	phySetRxState();
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetChannel(uint8_t channel)
{
	uint8_t reg;

	reg = phyReadRegister(PHY_CC_CCA_REG) & ~0x1f;
	phyWriteRegister(PHY_CC_CCA_REG, reg | channel);
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetPanId(uint16_t panId)
{
	uint8_t *d = (uint8_t *)&panId;

	phyWriteRegister(PAN_ID_0_REG, d[0]);
	phyWriteRegister(PAN_ID_1_REG, d[1]);
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetShortAddr(uint16_t addr)
{
	uint8_t *d = (uint8_t *)&addr;

	//phyWriteRegister(SHORT_ADDR_0_REG, d[0]);
	//phyWriteRegister(SHORT_ADDR_1_REG, d[1]);
	phyWriteRegister(CSMA_SEED_0_REG, d[0] + d[1]);
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetTxPower(uint8_t txPower)
{
	uint8_t reg;

	reg = phyReadRegister(PHY_TX_PWR_REG) & ~0x0f;
	phyWriteRegister(PHY_TX_PWR_REG, reg | txPower);
}

void PHY_SetRxSensitivity(uint8_t rxSensitivity)
{
	uint8_t reg;

	reg = phyReadRegister(RX_SYN_REG) & ~0x0f;
	phyWriteRegister(RX_SYN_REG, reg | rxSensitivity);
}

/*************************************************************************//**
*****************************************************************************/
void PHY_Sleep(void)
{
	PhyReset();
	phyTrxSetState(TRX_CMD_TRX_OFF);
	TRX_SLP_TR_HIGH();
	phyState = PHY_STATE_SLEEP;
}

/*************************************************************************//**
*****************************************************************************/
void PHY_Wakeup(void)
{
	TRX_SLP_TR_LOW();
	phySetRxState();
	phyState = PHY_STATE_IDLE;
}

/*************************************************************************//**
*****************************************************************************/
void PHY_DataReq(uint8_t *data,uint8_t length)
{
	phyTrxSetState(TRX_CMD_PLL_ON);

	TRX_SLP_TR_HIGH();
	TRX_TRIG_DELAY();
	TRX_SLP_TR_LOW();
	LED2_OPEN();

	/* size of the buffer is sent as first byte of the data
	 * and data starts from second byte.
	 */
	
	mov_data(&data[3],&MPDUPayload[1],length);
	MPDUPayload[0] = length+2;//加两个字节CRC
	trx_frame_write(MPDUPayload, MPDUPayload[0] /* length value*/);

	//data[0] = 10;
	//data[0] += 2;
	//memcpy(temp,data,10);
	//temp[0] = 22;
	////trx_frame_write(data, (data[0] - 1) /* length value*/);
	//trx_frame_write(temp, sizeof(temp) /* length value*/);
	//phyState = PHY_STATE_TX_WAIT_END;
	//TRX_SLP_TR_HIGH();
	//TRX_TRIG_DELAY();
	//TRX_SLP_TR_LOW();
}

/*************************************************************************//**
*****************************************************************************/
uint16_t PHY_RandomReq(void)
{
	uint16_t rnd = 0;
	uint8_t rndValue;

	phyTrxSetState(TRX_CMD_RX_ON);

	for (uint8_t i = 0; i < 16; i += 2) {
		delay_us(RANDOM_NUMBER_UPDATE_INTERVAL);
		rndValue = (phyReadRegister(PHY_RSSI_REG) >> RND_VALUE) & 3;
		rnd |= rndValue << i;
	}

	phySetRxState();

	return rnd;
}

/*************************************************************************//**
*****************************************************************************/
void PHY_EncryptReq(uint8_t *text, uint8_t *key)
{
	sal_aes_setup(key, AES_MODE_ECB, AES_DIR_ENCRYPT);
#if (SAL_TYPE == AT86RF2xx)
	sal_aes_wrrd(text, NULL);
#else
	sal_aes_exec(text);
#endif
	sal_aes_read(text);
}

/*************************************************************************//**
*****************************************************************************/
int8_t PHY_EdReq(void)
{
	uint8_t ed;

	phyTrxSetState(TRX_CMD_RX_ON);
	phyWriteRegister(PHY_ED_LEVEL_REG, 0);

	while (0 == (phyReadRegister(IRQ_STATUS_REG) & (1 << CCA_ED_DONE))) {
	}

	ed = (int8_t)phyReadRegister(PHY_ED_LEVEL_REG);

	phySetRxState();

	return ed + PHY_RSSI_BASE_VAL;
}

/*************************************************************************//**
*****************************************************************************/
void phyWriteRegister(uint8_t reg, uint8_t value)
{
	trx_reg_write(reg, value);
}

/*************************************************************************//**
*****************************************************************************/
uint8_t phyReadRegister(uint8_t reg)
{
	uint8_t value;

	value = trx_reg_read(reg);

	return value;
}

/*************************************************************************//**
*****************************************************************************/
void phyWaitState(uint8_t state)
{
	while (state != (phyReadRegister(TRX_STATUS_REG) & TRX_STATUS_MASK)) {
	}
}

/*************************************************************************//**
*****************************************************************************/
void phySetRxState(void)
{
	phyTrxSetState(TRX_CMD_TRX_OFF);

	phyReadRegister(IRQ_STATUS_REG);

	if (phyRxState) {
		phyTrxSetState(TRX_CMD_PLL_ON);
	}
	phyReadRegister(IRQ_STATUS_REG);
}

/*************************************************************************//**
*****************************************************************************/
void phyTrxSetState(uint8_t state)
{
	//do { phyWriteRegister(TRX_STATE_REG, TRX_CMD_FORCE_TRX_OFF);
	//} while (TRX_STATUS_TRX_OFF !=
			//(phyReadRegister(TRX_STATUS_REG) & TRX_STATUS_MASK));
phyWriteRegister(TRX_STATE_REG,
			     state);
	//do { phyWriteRegister(TRX_STATE_REG,
			     //state); } while (state !=
			//(phyReadRegister(TRX_STATUS_REG) & TRX_STATUS_MASK));
}

/*************************************************************************//**
*****************************************************************************/
void PHY_SetIEEEAddr(uint8_t *ieee_addr)
{
	uint8_t *ptr_to_reg = ieee_addr;
	for (uint8_t i = 0; i < 8; i++) {
		trx_reg_write((IEEE_ADDR_0_REG + i), *ptr_to_reg);
		ptr_to_reg++;
	}
}

/*************************************************************************//**
*****************************************************************************/
void PHY_TaskHandler(void)
{
	if (PHY_STATE_SLEEP == phyState) {
		return;
	}

	if (phyReadRegister(IRQ_STATUS_REG) & (1 << TRX_END)) {
		if (PHY_STATE_IDLE == phyState) {
			PHY_DataInd_t ind;
			uint8_t size;
			int8_t rssi;

			rssi = (int8_t)phyReadRegister(PHY_ED_LEVEL_REG);

			trx_frame_read(&size, 1);

			trx_frame_read(phyRxBuffer, size + 2);

			ind.data = phyRxBuffer + 1;

			ind.size = size - PHY_CRC_SIZE;
			ind.lqi  = phyRxBuffer[size + 1];
			ind.rssi = rssi + PHY_RSSI_BASE_VAL;
			PHY_DataInd(&ind);

			phyWaitState(TRX_STATUS_RX_AACK_ON);
		} else if (PHY_STATE_TX_WAIT_END == phyState) {
			uint8_t status
				= (phyReadRegister(TRX_STATE_REG) >>
					TRAC_STATUS) & 7;

			if (TRAC_STATUS_SUCCESS == status) {
				status = PHY_STATUS_SUCCESS;
			} else if (TRAC_STATUS_CHANNEL_ACCESS_FAILURE ==
					status) {
				status = PHY_STATUS_CHANNEL_ACCESS_FAILURE;
			} else if (TRAC_STATUS_NO_ACK == status) {
				status = PHY_STATUS_NO_ACK;
			} else {
				status = PHY_STATUS_ERROR;
			}

			phySetRxState();
			phyState = PHY_STATE_IDLE;

			PHY_DataConf(status);
		}
	}
}

#endif /* PHY_AT86RF233 */
