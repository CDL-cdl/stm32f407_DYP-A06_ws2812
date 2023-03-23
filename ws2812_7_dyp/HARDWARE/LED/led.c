#include "led.h" 
#include "stdlib.h" 

	    
//LED IO初始化
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
  static int sed = 2; // 随机种子
	srand(sed);
	sed = rand();
	return sed %17;
}





















//void GPIO_input_init(void)
//{
//   GPIO_InitTypeDef  GPIO_InitStructure;

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOB时钟

//  //GPIOF9,F10初始化设置
//  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;//LED0和LED1对应IO口
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO 
//}
//u8 keyscan(u8 key,u8 value)
//{
//    u8  res=0;
//    if(key==value)		//检测按键K1是否按下
//	{
//	   delay_ms(10);	//消除抖动
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






