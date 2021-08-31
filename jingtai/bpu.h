#ifndef __BPK_H
#define __BPK_H

#include "sys.h"

#define BPU_BASE  		 	   (0x40030000UL)

typedef struct
{
    __IO uint32_t FLAG[(0x0174 - 0x00164) >> 2];
} FLAG_TypeDef;

typedef struct
{
    __IO uint32_t KEY[16];
	__I  uint32_t BPK_RSVD0[(0x80-0x40)>>2];	
    __IO uint32_t BPK_RDY;
    __IO uint32_t BPK_CLR;
    __IO uint32_t BPK_LRA;
    __IO uint32_t BPK_LWA;
    __I  uint32_t BPK_RSVD1;	
    __IO uint32_t BPK_LR;
	__IO uint32_t BPK_SCR;
	__IO uint32_t BPK_POWER;
   
    __IO uint32_t RTC_CS;
    __IO uint32_t RTC_REF;
    __IO uint32_t RTC_ARM;
    __I  uint32_t RTC_TIM;
    __O  uint32_t RTC_INTCLR;
    __IO uint32_t OSC32K_CR;
    __IO uint32_t RTC_ATTA_TIM;	

	__IO uint32_t BPK_RR;	
    __IO uint32_t SEN_EXT_TYPE;
    __IO uint32_t SEN_EXT_CFG;
    __IO uint32_t SEN_SOFT_EN;
    __IO uint32_t SEN_STATE;
    __IO uint32_t SEN_BRIDGE;
    __IO uint32_t SEN_SOFT_ATTACK;
    __IO uint32_t SEN_SOFT_LOCK;
    __IO uint32_t SEN_ATTACK_CNT;
    __IO uint32_t SEN_ATTACK_TYP;
    __IO uint32_t SEN_VG_DETECT;
    __IO uint32_t SEN_RNG_INI;
    __IO uint32_t RESERVED3[(0x0104 - 0x00EC) >> 2];
    __IO uint32_t SEN_EXT_EN[8];
	__IO uint32_t RESERVED4[(0x0134 - 0x0124) >> 2];
	__IO uint32_t SEN_VH_EN;
	__IO uint32_t SEN_VL_EN;
	__IO uint32_t SEN_TH_EN;
	__IO uint32_t SEN_TL_EN;
	__IO uint32_t SEN_XTAL32_EN;
	__IO uint32_t SEN_MESH_EN;
	__IO uint32_t SEN_VOLGLTCH_EN;
    __IO uint32_t SEN_EXTS_START;
    __IO uint32_t SEN_LOCK;
    __IO uint32_t SEN_ANA0;
    __IO uint32_t SEN_ANA1;
    __IO uint32_t SEN_ATTCLR;
    FLAG_TypeDef  SEN_FLAG;
    __IO uint32_t SEN_DEBUG;
    __I  uint32_t BPU_RSVD5[(0x200- 0x178) >> 2];	
	__IO uint32_t BPK_RAM[(0x600-0x200) >> 2];
} BPU_TypeDef;

#define BPU            		 	((BPU_TypeDef   *)     BPU_BASE  )














void sensor_tamper_able(void);
void bpk_write(uint32_t number, uint32_t message);
uint32_t bpk_read(uint32_t number);
void sensor_diable(void);


#endif