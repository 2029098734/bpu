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
	BPU->SEN_STATE = 0x0;
	BPU->BPK_LR &= 0xFFFFFF00;
	BPU->SEN_SOFT_EN = 0x1;	
	BPU->SEN_SOFT_ATTACK = 0x000000F0;
	for(int i = 0; i < 16; i++)
	{
		bpk_write(i, 0xFF);
	}
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
			if(UART1->OFFSET_0.RBR == 0x32)
			{
				BPU->SEN_SOFT_LOCK = 0x00000000;
				BPU->SEN_SOFT_ATTACK |= 0x00000001;
				UART1->OFFSET_0.THR = (BPU->SEN_STATE >> 24) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (BPU->SEN_STATE >> 16) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (BPU->SEN_STATE >> 8) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (BPU->SEN_STATE ) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->ISPR[0] & (1 << 17)) >> 17);
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->IABR[0] & (1 << 17)) >> 17);
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = ((NVIC->ISER[0] & (1 << 17)) >> 17);
				NVIC->ISER[0] = ((1 << 17));
			}
			if(UART1->OFFSET_0.RBR == 0x33)
			{
				BPU->SEN_SOFT_ATTACK = (BPU->SEN_SOFT_ATTACK  - (1 << 4));
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
