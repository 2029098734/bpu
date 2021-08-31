#include"sys.h"
#include"irqn.h"
#include"uart.h"
#include"bpu.h"

int main(void)
{
	UART_Init(UART1);
	BPU->BPK_LR &= 0xFFFFFF00; 
	//UART1->OFFSET_0.THR = BPU->BPK_LR & 0xFF;
	BPU->SEN_LOCK = 0x00000000;
	//UART1->OFFSET_0.THR = BPU->SEN_LOCK & 0x1;
	sensor_diable();
	//while(((UART1->USR) & 0x1)){}
	//UART1->OFFSET_0.THR = 0x11;
	for(int i = 0; i < 16; i++)
	{
		bpk_write(i, i);
	}
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
			
			UART1->OFFSET_0.THR = UART1->OFFSET_0.RBR;
			while(((UART1->USR) & 0x1)){}
		}
	}
	return 0;
}