#include"sys.h"
#include"irqn.h"
#include"uart.h"
#include"bpu.h"
#include"irqn.h"

int main(void)
{
	SYSCTRL->CG_CTRL1 |= 0x04000000;
	UART_Init(UART1);
	sensor_diable();
	BPU->BPK_LR &= 0xFFFFFF00;	
	for(int i = 0; i < 16; i++)
	{
		bpk_write(i, 0xFF);
	}

	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x11;

	BPU->SEN_STATE = 0x0; 
	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0x55;    //关闭外部所有传感器
	while(BPU->SEN_EXTS_START & 0x800000000){}
	BPU->SEN_LOCK = 0x00000000;
	for(int i = 0; i < 6; i++)
	{
		while(BPU->SEN_EXTS_START & 0x800000000){}
		BPU->SEN_EXT_EN[i] = 0xAA;
	}
	BPU->SEN_EXT_EN[6] = 0x55;
	BPU->SEN_EXT_EN[7] = 0x55;
	while(BPU->SEN_EXTS_START & 0x800000000){}
	BPU->SEN_EXT_TYPE = 0x000FF000;   //全部上拉电阻，设为静态传感器
	BPU->SEN_EXT_CFG =0x00068000;
	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0xAA;    //开启外部所有传感器
	

	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x11;

	SCB->AIRCR =  0x05FA0300 | (SCB->AIRCR & 0xF0FF);
	NVIC->IP[17] = 0x00;
	NVIC->ISER[0] = ((1 << 17));
	





/* 	BPU->SEN_LOCK = 0x00000000;
	BPU->BPK_LR &= 0xFFFFFF00;
	BPU->SEN_STATE = 0;
	BPU->SEN_EXT_CFG = 0x04A58000; 
	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x11;
	sensor_tamper_able();
	
	NVIC->ISER[0] |= ((1 << 17));
	SCB->AIRCR =  0x05FA0300 | (SCB->AIRCR & 0xF0FF);
	BPU->SEN_STATE = 0; */
	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x11;


	while(1)
	{
		if((UART1->LSR) & 0x1)
		{
			if(UART1->OFFSET_0.RBR == 0x21)
			{
				for(int i = 0; i < 16; i++)
				{
					bpk_write(i, i);
				}
			}

			if(UART1->OFFSET_0.RBR == 0x31)
			{
				UART1->OFFSET_0.THR = BPU->SEN_STATE & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->ISPR[0] & (1 << 17)) >> 17);
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->IABR[0] & (1 << 17)) >> 17);
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->ISER[0] & (1 << 17)) >> 17);
			}

			if(UART1->OFFSET_0.RBR == 0x22)
			{
				for(int i = 0; i < 16; i++)
				{
					UART1->OFFSET_0.THR = bpk_read(i) & 0xFF;
					while(((UART1->USR) & 0x1)){}
				} 
			}
			UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
			while(((UART1->USR) & 0x1)){}
		}
	}
	
	return 0;
}


void SENSOR_IRQHandler(void)
{
	UART1->OFFSET_0.THR = BPU->SEN_STATE & 0xFF;
	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0xF;
	while(((UART1->USR) & 0x1)){}
	BPU->SEN_STATE = 0;
	NVIC->ICPR[0] = ((1 << 17));
}
