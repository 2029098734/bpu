#include"uart.h"

/*  管脚复用
				ALT0    ALT1		ALT2	   ALT3
		PD8    		   PD[8]  UART2_RX  DCMIS_DATA3
		PD9    	       PD[9]  UART2_TX  DCMIS_DATA4
 		PA0  UART0_RX  PA[0]  PWM0
		PA1  UART0_TX  PA[1]  PWM1
		PA2  UART0_CTS  PA[2]  PWM2  I2C0_SCL
		PA3  UART0_RTS  PA[3]  PWM3  I2C0_SDA
		PB2  SPI2_SCK  PB[2]  PWM2  UART2_RX/IrDA_IN
		PB3  SPI2_CSN  PB[3]  PWM3  UART2_TX/IrDA_OUT
 */	


void UART_Init(UART_TypeDef * UART)
{ 
	SYSCTRL->CG_CTRL1 |= 1 << 20; //打开门控,使能GPIO时钟
	if(UART == UART0)
	{
		SYSCTRL->CG_CTRL1 |= 0x1;      //使能UART0时钟
		SYSCTRL->SOFT_RST1 |= 0x1;     //使能UART0软复位
		GPIO_ALT->PA_ALT &= 0xFFFFFFF0;  //端口复用     
	}
	if(UART == UART2)
	{
		SYSCTRL->CG_CTRL1 |= 0x1<<2;      
		SYSCTRL->SOFT_RST1 |= 0x1<<2;
		GPIO_ALT->PD_ALT &=0xF0FFFFFF;
	}
	if(UART == UART1)
	{
		SYSCTRL->CG_CTRL1 |= 0x1<<1;      
		SYSCTRL->SOFT_RST1 |= 0x1<<1;
		GPIO_ALT->PB_ALT |=0x0F000000;
	}
		
/* 		GPIOA->OEN  = 0x0000FFFE;
		GPIOA->PUE  = 0x0000FFFF;  */
		
		/* UART1:
		SYSCTRL->CG_CTRL1 |= 0x2;      
		SYSCTRL->SOFT_RST1 |= 0x2;     
		break;
		
		UART2:
		SYSCTRL->CG_CTRL1 |= 0x4;      
		SYSCTRL->SOFT_RST1 |= 0x4;
		GPIO_ALT->PB_ALT =0x555555F5;
		GPIOB->OEN  = 0x0000FFFB;
		GPIOB->PUE  = 0x0000FFFF;		
		break;
		
		UART3:
		SYSCTRL->CG_CTRL1 |= 0x8;      
		SYSCTRL->SOFT_RST1 |= 0x8;     
		break; */

	

	
	UART->LCR |= 0x00000080; //DLL和DLH读写操作使能

	uint32_t F_PCLK = 1000 * SYSCTRL->PCLK_1MS_VAL;	//读取PCLK频率
    //UART外设时钟由内部PCLK提供，即UART外设时钟频率等于PCLK时钟频率。波特率=输入时钟/(16*分频波特率寄存器值)
	uint32_t Div = (uint32_t)((F_PCLK /16 + 57600) / 115200); //向上取整
	UART->OFFSET_0.DLL = (Div & 0x00FF);
	UART->OFFSET_4.DLH = ((Div >> 8) & 0x00FF);
	UART->LCR = 0x00000003;            //00011        DLL和DLH读写操作禁用,无奇偶校验,停止位个数为1,8bit
}