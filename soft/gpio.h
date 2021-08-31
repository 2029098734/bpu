#ifndef __GPIO_H
#define __GPIO_H

#include"sys.h"

#define GPIO_BASE                  (0x4001D000UL)
#define GPIOB_BASE                 (GPIO_BASE+0x10)
#define GPIOD_BASE                 (GPIO_BASE+0x30)
#define ALT_BASE        		   (GPIO_BASE+0x180)
#define GPIO_Pin_5                 ((uint16_t)0x0020)

typedef struct
{
    uint32_t IODR;
    uint32_t BSRR;
    uint32_t OEN;
    uint32_t PUE;
} GPIO_TypeDef;

typedef struct
{
    uint32_t PA_ALT;
    uint32_t PB_ALT;
    uint32_t PC_ALT;
    uint32_t PD_ALT;
	uint32_t PE_ALT;
	uint32_t PF_ALT;
} ALT_TypeDef;

#define GPIOA 					  ((GPIO_TypeDef *)GPIO_BASE)
#define GPIOB 					  ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOD 				      ((GPIO_TypeDef *)GPIOD_BASE)

#define GPIO_ALT 				  ((ALT_TypeDef *)ALT_BASE)
void GPIOA_init(void);

#endif