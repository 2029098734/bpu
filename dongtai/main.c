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
	BPU->SEN_LOCK = 0x00000000;
	BPU->SEN_STATE = 0x0; 
	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0x55;    //关闭外部所有传感器
	BPU->SEN_EXT_TYPE = 0x000FF000;   //全部上拉电阻，设为静态传感器
	for(int i = 0; i < 8; i++)
	{
		while(BPU->SEN_EXTS_START & 0x800000000){}
		BPU->SEN_EXT_EN[i] = 0x55;
	}

	BPU->SEN_EXT_EN[2] = 0xAA;
	BPU->SEN_EXT_EN[3] = 0xAA;
	BPU->SEN_EXT_CFG = 0x00758000;
	BPU->SEN_EXT_TYPE = 0x000F3004;  //配置动态传感器,未引出管脚设为静态上拉电阻


	BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0xAA;    //开启外部所有传感器
	BPU->SEN_STATE = 0x0; 


	while(((UART1->USR) & 0x1)){}
	UART1->OFFSET_0.THR = 0x11;

	SCB->AIRCR =  0x05FA0300 | (SCB->AIRCR & 0xF0FF);
	NVIC->IP[17] = 0x00;
	NVIC->ISER[0] = ((1 << 17));
	

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
				NVIC->ISER[0] = ((1 << 17));
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
