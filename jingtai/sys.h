#ifndef __SYS_H
#define __SYS_H

#ifndef NULL
#define NULL   ( 0 )
#endif

#define   	__I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile            


#define uint8_t					   char
#define uint32_t				   unsigned int
#define SYSCTRL_BASE               (0x4001F000UL)
//#define PCLK_1MS_VAL			   (SYSCTRL_BASE + 0x30)
#define NVIC_BASE                  (0xE000E100UL)
#define SCB_BASE           		   (0xE000ED00UL)                    /*!< System Control Block Base Address  */
#define SysTick_BASE  		 	   (0xE000E010UL)                    /*!< SysTick Base Address               */



typedef enum IRQn
{
/******  Cortex-M# Processor Exceptions Numbers ***************************************************/

/* ToDo: use this Cortex interrupt numbers if your device is a CORTEX-M3 / Cortex-M4 device       */
	NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt                      */
	MemoryManagement_IRQn         = -12,      /*!<  4 Memory Management Interrupt                 */
	BusFault_IRQn                 = -11,      /*!<  5 Bus Fault Interrupt                         */
	UsageFault_IRQn               = -10,      /*!<  6 Usage Fault Interrupt                       */
	SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                           */
	DebugMonitor_IRQn             = -4,       /*!< 12 Debug Monitor Interrupt                     */
	PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                           */
	SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                       */

/******  Device Specific Interrupt Numbers ********************************************************/
/* ToDo: add here your device specific external interrupt numbers
         according the interrupt handlers defined in startup_Device.s
         eg.: Interrupt for Timer#1       TIM1_IRQHandler   ->   TIM1_IRQn                        */
    DMA_IRQn                                        = 0,
    USB_IRQn                                        = 1,
    USBDMA_IRQn                                     = 2,
    LCD_IRQn                                        = 3,
    SCI0_IRQn                                       = 4,
    UART0_IRQn                                      = 5,
    UART1_IRQn                                      = 6,
    SPI0_IRQn                                       = 7,
    CRYPT0_IRQn                                     = 8,
    TIM0_0_IRQn                                     = 9,
    TIM0_1_IRQn                                     = 10,
    TIM0_2_IRQn                                     = 11,
    TIM0_3_IRQn                                     = 12,
    EXTI0_IRQn                                      = 13,
    EXTI1_IRQn                                      = 14,
    EXTI2_IRQn                                      = 15,
    RTC_IRQn                                        = 16,
    SENSOR_IRQn                                     = 17,
    TRNG_IRQn                                       = 18,
    ADC0_IRQn                                       = 19,
    SSC_IRQn                                        = 20,
    TIM0_4_IRQn                                     = 21,
    TIM0_5_IRQn                                     = 22,
    KBD_IRQn                                        = 23,
    MSR_IRQn                                        = 24,
    EXTI3_IRQn                                      = 25,
    SPI1_IRQn                                       = 26,
    SPI2_IRQn                                       = 27,
    
    SCI2_IRQn                                       = 29,
   
    UART2_IRQn                                      = 32,
    UART3_IRQn                                      = 33,

    QSPI_IRQn                                       = 35,
    I2C0_IRQn                                       = 36,
    EXTI4_IRQn                                      = 37,
    EXTI5_IRQn                                      = 38,
    TIM0_6_IRQn                                     = 39,
    TIM0_7_IRQn                                     = 40,
    
    DCMI_IRQn                                       = 42,
   
    QR_IRQn                                         = 46,
	GPU_IRQn										= 47,

	AWD_IRQn										= 49,
	DAC_IRQn										= 50,
	SPI5_IRQn										= 51
} IRQn_Type;



typedef struct
{
    __IO uint32_t FREQ_SEL;
    __IO uint32_t CG_CTRL1;
    __IO uint32_t CG_CTRL2;
    __O uint32_t  SOFT_RST1;
    __O uint32_t  SOFT_RST2;
    __IO uint32_t LOCK_R;
    __IO uint32_t PHER_CTRL;
	__I uint32_t  SYS_RSVD[(0x2C-0x1C) >> 2];
    __I uint32_t  HCLK_1MS_VAL;
    __I uint32_t  PCLK_1MS_VAL;
    __IO uint32_t ANA_CTRL;
    __IO uint32_t DMA_CHAN;
    __IO uint32_t SCI0_GLF;
    __IO uint32_t SW_RSV1;
    __IO uint32_t SW_RSV2;
    __IO uint32_t CARD_RSVD;
    __IO uint32_t LDO25_CR;
	__IO uint32_t DMA_CHAN1;
    __I uint32_t  SYS_RSVD2[(0x100-0x54) >> 2];
    __IO uint32_t MSR_CR1;
    __IO uint32_t MSR_CR2;
    __IO uint32_t USBPHY_CR1;
    __IO uint32_t USBPHY_CR2;
    __IO uint32_t USBPHY_CR3;
	__IO uint32_t ISO7816_CR;
	__IO uint32_t LDO_CR;
	__IO uint32_t CHG_CSR;
    __I uint32_t  SYS_RSVD3[(0x204-0x120) >> 2];
    __IO uint32_t RSVD_POR;
    __I uint32_t  SYS_RSVD4[(0x3EC-0x208) >> 2];
    __IO uint32_t PM2_WK_FLAG;
    __IO uint32_t CALIB_CSR;
    __IO uint32_t DBG_CR;
    __IO uint32_t CHIP_ID;
} SYSCTRL_TypeDef;

typedef struct
{
  __IO uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  __O  uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_Type;


typedef struct
{
  __I  uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
  __IO uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
  __IO uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  __IO uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
  __IO uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  __IO uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  __IO uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  __IO uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  __IO uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
  __IO uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  __IO uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
  __IO uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
  __IO uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  __I  uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  __I  uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
       uint32_t RESERVED0[5];
  __IO uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} SCB_Type;

typedef struct
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;


#define SCB                			((SCB_Type*) SCB_BASE)   /*!< SCB configuration struct           */
#define SYSCTRL 					((SYSCTRL_TypeDef *) SYSCTRL_BASE)
#define SysTick            		 	((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct       */
//#degine PCLK_1MS 					(*(uint32_t *)PCLK_1MS_VAL)            //初始值0x00005DC0
#define NVIC                		((NVIC_Type      *)     NVIC_BASE     )

#endif