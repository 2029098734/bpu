#ifndef _UART_H
#define _UART_H

#include"gpio.h"
#include"sys.h"
#define UART0_BASE			(0x40016000UL)
#define UART1_BASE			(0x40017000UL)
#define UART2_BASE			(0x40044000UL)
typedef struct
{
    union
    {
         uint32_t RBR;
         uint32_t THR;
        uint32_t DLL;
    } OFFSET_0;
    union
    {
        uint32_t DLH;
        uint32_t IER;
    } OFFSET_4;
    union
    {
        uint32_t IIR;
        uint32_t FCR;
    } OFFSET_8;
    uint32_t LCR;
    uint32_t MCR;
     uint32_t LSR;
     uint32_t MSR;
    uint32_t SCR;
    uint32_t LPDLL;
    uint32_t LPDLH;
     uint32_t RES0[2];
    union
    {
         uint32_t SRBR[16];
         uint32_t STHR[16];
    } OFFSET_48;
    uint32_t FAR;
     uint32_t TFR;
     uint32_t RFW;
     uint32_t USR;
     uint32_t TFL;
     uint32_t RFL;
     uint32_t SRR;
    uint32_t SRTS;
    uint32_t SBCR;
    uint32_t SDMAM;
    uint32_t SFE;
    uint32_t SRT;
    uint32_t STET;
    uint32_t HTX;
    uint32_t DMASA;
     uint32_t RES1[18];
     uint32_t CPR;
     uint32_t UCV;
     uint32_t CTR;
    
} UART_TypeDef;

#define UART2			((UART_TypeDef *) UART2_BASE)
#define UART0     		((UART_TypeDef *) UART0_BASE)
#define UART1     		((UART_TypeDef *) UART1_BASE)
void UART_Init(UART_TypeDef * UART);



#endif	/*#define _UART_H*/
