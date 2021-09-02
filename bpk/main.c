#include"sys.h"
#include"irqn.h"
#include"uart.h"
#include"bpu.h"

int main(void)
{
	uint32_t time = 0;
	SysTick->LOAD = (0x00FFFFFF & 0x927C00);
	SysTick->CTRL = 0x00000004; //不使能系统定时器,不使能中断,使用内部处理器时钟源
	UART_Init(UART1);
	BPU->BPK_LR &= 0xFFFFFF00; 
	//UART1->OFFSET_0.THR = BPU->BPK_LR & 0xFF;
	BPU->SEN_LOCK = 0x00000000;
	//UART1->OFFSET_0.THR = BPU->SEN_LOCK & 0x1;
	sensor_diable();
	//while(((UART1->USR) & 0x1)){}
	//UART1->OFFSET_0.THR = 0x11;
	//UART1->OFFSET_0.THR = 0x11;
	for(int i = 0; i < 16; i++)
	{
		bpk_read(i, UART1);
		while(((UART1->USR) & 0x1)){}
	}
	//UART1->OFFSET_0.THR = 0x11;
	while(1)
	{
		if((UART1->LSR) & 0x1)
		{
			if(UART1->OFFSET_0.RBR == 0x11)
			{
				
				SysTick->CTRL |= 0x1;
				while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
				BPU->BPK_LWA &= 0xFFFFFFFC;     //清除写锁定
				for(int i = 0; i < 16; i++)
				{
					time += (SysTick->VAL & 0x00FFFFFF);
					BPU->KEY[i] = i;
					time -= (SysTick->VAL & 0x00FFFFFF);    
				}
				BPU->BPK_LWA |= 0x3;            //使能写锁定
				UART1->OFFSET_0.THR = (time >> 24) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time >> 16) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time >> 8) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				time = 0;
				SysTick->CTRL &= 0xFFFFFFFE;
			}
			if(UART1->OFFSET_0.RBR == 0x12)
			{
				
				uint32_t mm = 0;
				SysTick->CTRL |= 0x1;
				while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
				BPU->BPK_LRA &= 0xFFFFFFFC;     //清除读锁定
				for(int i = 0; i < 16; i++)
				{
					time += (SysTick->VAL & 0x00FFFFFF);
					mm = BPU->KEY[i];
					time -= (SysTick->VAL & 0x00FFFFFF);    
				}
				BPU->BPK_LRA |= 0x3;            //使能读锁定
				UART1->OFFSET_0.THR = (time >> 24) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time >> 16) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time >> 8) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				UART1->OFFSET_0.THR = (time) & 0xFF;
				while(((UART1->USR) & 0x1)){}
				time = 0;
				SysTick->CTRL &= 0xFFFFFFFE;
			}
			UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
			while(((UART1->USR) & 0x1)){}
		}
	}
	return 0;
}