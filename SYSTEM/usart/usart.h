#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x.h"

/** 
  * 串口宏定义，不同的串口挂载的总线不一样，移植时需要修改这几个宏
  */
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT         GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


#define  STAND_WALK_STA   0x00
#define  PROSTRATE_STA 		0x01
#define  BACK_UP_STA 		  0x02
#define  TURN_RIGHT_STA 	0x03
#define  TURN_LEFT_STA 		0x04
#define  HALF_SQUAT_STA 	0x05



#define  DANCE_STA        0x0A
#define  FLIP_STA         0x0B
#define  GREET_STA        0x0C


#define  FAULT1  					0x10
#define  FAULT2 					0x11
#define  FAULT3  					0x12
#define  FAULT4 					0x13
#define  FAULT5  					0x14
#define  FAULT6 					0x15
#define  FAULT7  					0x16
#define  FAULT8 					0x17

extern char uart3_buf[4];
extern int data_head3;
extern char uart2_buf[4];
extern int data_head2;
extern u8 usart2_flag;
extern u8 usart3_flag;

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void USART3_Configuration(void);
void USART2_Configuration(void);


#endif


