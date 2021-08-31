#include"bpu.h"

void bpk_write(uint32_t number, uint32_t message)
{
	while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
	BPU->BPK_LWA &= 0xFFFFFFFC;     //清除写锁定
	BPU->KEY[number] = message;     
	BPU->BPK_LWA |= 0x3;            //使能写锁定
}

uint32_t bpk_read(uint32_t number)
{
	uint32_t message = 0;
	while(!(BPU->BPK_RDY & 0x1)){}  //等待复位结束
	BPU->BPK_LRA &= 0xFFFFFFFC;     //清除读锁定
	message = BPU->KEY[number];     
	BPU->BPK_LRA |= 0x3;            //使能读锁定
	return message;
}

void sensor_diable(void)
{

	BPU->SEN_VH_EN = 0x55;
	BPU->SEN_VL_EN = 0x55;
	BPU->SEN_TH_EN = 0x55;
	BPU->SEN_TL_EN = 0x55;
	BPU->SEN_XTAL32_EN = 0x55;
	BPU->SEN_MESH_EN = 0x80000055;
	BPU->SEN_VOLGLTCH_EN = 0x55;
    BPU->SEN_EXTS_START = (BPU->SEN_EXTS_START & 0xFFFFFF00) | 0x55;    //关闭外部所有传感器
	while(BPU->SEN_EXTS_START & 0x800000000){}
	BPU->SEN_STATE = 0x0;            //exts_intp,对该寄存器进行写操作会清除所有中断
}

void sensor_tamper_able(void)
{
	for(int i = 0; i < 8; i++)
	{
		while(BPU->SEN_EXTS_START & 0x800000000){}
		BPU->SEN_EXT_EN[i] = 0xAA;
	}
	while(BPU->SEN_EXTS_START & 0x800000000){}
	BPU->SEN_EXT_TYPE = 0x000FF000;   //全部上拉电阻，设为静态传感器
}




