#include"bpu.h"
#include"uart.h"

void bpk_write(uint32_t number, uint32_t message)
{
	while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
	BPU->BPK_LWA &= 0xFFFFFFFC;     //清除写锁定
	BPU->KEY[number] = message;     
	BPU->BPK_LWA |= 0x3;            //使能写锁定
}

void bpk_read(uint32_t number, UART_TypeDef* UART)
{
	while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
	BPU->BPK_LRA &= 0xFFFFFFFC;     //清除读锁定
	UART->OFFSET_0.THR = BPU->KEY[number] & 0xFF;
	while(((UART->USR) & 0x1)){}     
	UART->OFFSET_0.THR = (BPU->KEY[number] >> 8) & 0xFF;
	while(((UART->USR) & 0x1)){}     
	UART->OFFSET_0.THR = (BPU->KEY[number] >> 16) & 0xFF;
	while(((UART->USR) & 0x1)){}     
	UART->OFFSET_0.THR = (BPU->KEY[number] >> 24) & 0xFF;
	while(((UART->USR) & 0x1)){}
	BPU->BPK_LRA |= 0x3;            //使能读锁定
}

void sensor_diable(void)
{
	//关闭所有传感器
	BPU->SEN_VH_EN = 0x55;
	BPU->SEN_VL_EN = 0x55;
	BPU->SEN_TH_EN = 0x55;
	BPU->SEN_TL_EN = 0x55;
	BPU->SEN_XTAL32_EN = 0x55;
	BPU->SEN_MESH_EN = 0x55;
	BPU->SEN_VOLGLTCH_EN = 0x55;
    BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0x55;    //关闭外部所有传感器
	while(BPU->SEN_EXTS_START & 0x800000000){}
	BPU->SEN_STATE = 0x0;            //exts_intp,对该寄存器进行写操作会清除所有中断
}





