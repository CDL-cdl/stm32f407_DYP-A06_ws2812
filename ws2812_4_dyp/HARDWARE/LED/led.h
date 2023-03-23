#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "delay.h"


//LED端口定义
#define LED1 PAout(0)	// DS1
#define background_LED PBout(2)	//DS2
#define LED1_GPIO_PORT   GPIOB
#define LED1_GPIO_PIN    GPIO_Pin_2

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

extern void LED_Init(void);//初始化	
extern void GPIO_input_init(void);
extern u8 keyscan(u8 key,u8 value);
u16 Random(void);
	 				    
#endif
