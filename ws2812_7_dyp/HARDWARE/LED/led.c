#include "led.h" 
#include "stdlib.h" 

	    
//LED IO��ʼ��
void LED_Init(void)
{    	 
   GPIO_InitTypeDef   GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB,&GPIO_InitStructure);
   GPIO_SetBits(GPIOB,GPIO_Pin_2); 
}

u16 Random(void)
{
  static int sed = 2; // �������
	srand(sed);
	sed = rand();
	return sed %17;
}





















//void GPIO_input_init(void)
//{
//   GPIO_InitTypeDef  GPIO_InitStructure;

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

//  //GPIOF9,F10��ʼ������
//  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;//LED0��LED1��ӦIO��
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO 
//}
//u8 keyscan(u8 key,u8 value)
//{
//    u8  res=0;
//    if(key==value)		//��ⰴ��K1�Ƿ���
//	{
//	   delay_ms(10);	//��������
//	   if(key==value)
//	   {
//		    res=1;
//	   }
//	   else
//	   {
//	        res=0;
//	   }
//	} 
//	return res;
//}






