#include"sys.h"
#include"irqn.h"
#include"uart.h"
#include"bpu.h"
#include"irqn.h"

int main(void)
{
	SCB->VTOR = 0x01001000;
	__asm__ volatile ("dsb");
	SYSCTRL->CG_CTRL1 |= 0x04000000;
	SYSCTRL->SOFT_RST1 |= 0x2; 
	UART_Init(UART0);
	UART0->OFFSET_0.THR = BPU->SEN_STATE & 0xFF;
	while(((UART0->USR) & 0x1)){}
	BPU->SEN_STATE = 0x0; 				//清除传感器中断
	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0x55;    //关闭外部所有传感器,外部传感器寄存器需在外部传感器停止工作的状况下配置
	while(BPU->SEN_EXTS_START & 0x800000000){}	//等待外部传感器关闭
	BPU->SEN_EXT_CFG = 0x00058000;		//配置传感器参数
	BPU->SEN_EXT_TYPE = 0x000FF000;   	//全部上拉电阻，设为静态传感器
	//使能各个外部传感器
	for(int i = 0; i < 6; i++)
	{
		while(BPU->SEN_EXTS_START & 0x800000000){}
		BPU->SEN_EXT_EN[i] = 0xAA;
	}
	BPU->SEN_EXT_EN[6] = 0x55;
	BPU->SEN_EXT_EN[7] = 0x55;
	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0xAA;    //开启外部所有传感器
	BPU->SEN_VH_EN = 0x55;
	BPU->SEN_VL_EN = 0x55;
	BPU->SEN_TH_EN = 0x55;
	BPU->SEN_TL_EN = 0x55;
	BPU->SEN_XTAL32_EN = 0x55;
	BPU->SEN_MESH_EN = 0x80000055;
	BPU->SEN_VOLGLTCH_EN = 0x55;
/* 	BPU->BPK_LR &= 0x00000000;	
	for(int i = 0; i < 16; i++)
	{
		bpk_write(i, 0xFF);
	} */
/* 
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = 0x11; */
/* 	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = 0x11; */

	SCB->AIRCR =  0x05FA0400;
	NVIC->IP[17] = 0x20;
	NVIC->ISER[0] = 0x1 << 17;
	





/* 	BPU->SEN_LOCK = 0x00000000;
	BPU->BPK_LR &= 0xFFFFFF00;
	BPU->SEN_STATE = 0;
	BPU->SEN_EXT_CFG = 0x04A58000; 
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = 0x11;
	sensor_tamper_able();
	
	NVIC->ISER[0] |= ((1 << 17));
	SCB->AIRCR =  0x05FA0300 | (SCB->AIRCR & 0xF0FF);
	BPU->SEN_STATE = 0; */
/* 	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = 0x11; */
	/* UART0->OFFSET_0.THR = (SCB->VTOR >>24) & 0xFF;
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = (SCB->VTOR >>16) & 0xFF;
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = (SCB->VTOR >>8) & 0xFF;
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = (SCB->VTOR) & 0xFF;
	while(((UART0->USR) & 0x1)){} */

	while(1)
	{
		if((UART0->LSR) & 0x1)
		{
			if(UART0->OFFSET_0.RBR == 0x21)
			{
				for(int i = 0; i < 16; i++)
				{
					bpk_write(i, i);
				}
			}

			if(UART0->OFFSET_0.RBR == 0x31)
			{
				UART0->OFFSET_0.THR = BPU->SEN_STATE & 0xFF;
				while(((UART0->USR) & 0x1)){}
				UART0->OFFSET_0.THR = ((NVIC->ISPR[0] & (1 << 17)) >> 17);
				while(((UART0->USR) & 0x1)){}
				UART0->OFFSET_0.THR = ((NVIC->IABR[0] & (1 << 17)) >> 17);
				while(((UART0->USR) & 0x1)){}
				UART0->OFFSET_0.THR = ((NVIC->ISER[0]) >> 14);
				NVIC->ISER[0] = ((1 << 17));
			}

			if(UART0->OFFSET_0.RBR == 0x22)
			{
				for(int i = 0; i < 16; i++)
				{
					UART0->OFFSET_0.THR = bpk_read(i) & 0xFF;
					while(((UART0->USR) & 0x1)){}
				} 
			}
			UART0->OFFSET_0.THR = UART0->OFFSET_0.RBR;
			while(((UART0->USR) & 0x1)){}
		}
	}
}


void SENSOR_IRQHandler(void)
{
	UART0->OFFSET_0.THR = BPU->SEN_STATE & 0xFF;
	while(((UART0->USR) & 0x1)){}
	UART0->OFFSET_0.THR = 0xF;
	while(((UART0->USR) & 0x1)){}
	BPU->SEN_STATE = 0;
	NVIC->ICPR[0] = ((1 << 17));
	//while(BPU->SEN_EXTS_START & 0x800000000){}
}
