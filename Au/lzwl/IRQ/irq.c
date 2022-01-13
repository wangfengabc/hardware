#include "auxdevice.h"
#include "sio2host.h"
#include "ldsw20.h"
#include "trx_access.h"
#include "irq.h"
#include "tcc.h"

/*******************************************************************************
*
*函 数：tcc1_callback( )
*功 能：定时器1溢出中断处理程序
*输 入：
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/

void tcc1_callback(struct tcc_module *const module_inst)
{
	nop();
}

/*******************************************************************************
*
*函 数：tcc2_callback( )
*功 能：定时器2溢出中断处理程序
*输 入：
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：CommChannelTimerCovery 清除串口状态（恢复现场功能）
*
********************************************************************************/

void tcc2_callback(struct tcc_module *const module_inst)
{
	CommChannelTimerCovery(&WriterConfig, 1);
}


/*******************************************************************************
*
*函 数：AT86RFX_ISR( )
*功 能：射频接受中断处理函数
*输 入：
*输 出：
*作 者：
*时 间：2018.12.20
*备 注：
*
********************************************************************************/
void AT86RFX_ISR(void)
{
	
	__disable_irq();					//关全局中断
	Ldsw20RfPackReci(&WriterConfig,0);
	trx_irq_flag_clr();					//清RF（PB0）接收中断
	__enable_irq();						//使能全局中断
}
