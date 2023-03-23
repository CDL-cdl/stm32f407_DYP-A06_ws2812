#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "delay.h"


//LED�˿ڶ���
#define LED1 PAout(0)	// DS1
#define background_LED PBout(2)	//DS2
#define LED1_GPIO_PORT   GPIOB
#define LED1_GPIO_PIN    GPIO_Pin_2

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

extern void LED_Init(void);//��ʼ��	
extern void GPIO_input_init(void);
extern u8 keyscan(u8 key,u8 value);
u16 Random(void);
	 				    
#endif
