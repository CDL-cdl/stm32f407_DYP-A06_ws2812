#include"timer4.h"

////通用定时器4 中断初始化
////arr：自动重装值。 psc：时钟预分频数
////定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
////Ft=定时器工作频率,单位:Mhz
////这里使用的是定时器 4!
//void TIM4_Int_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //①使能 TIM4 时钟

//  TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
//  TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //定时器分频
//  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
//  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);// ②初始化定时器 TIM4
//  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //③允许定时器 4 更新中断

//  NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器 4 中断
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级 1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //响应优先级 3
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//  NVIC_Init(&NVIC_InitStructure);// ④初始化 NVIC

//  TIM_Cmd(TIM4,ENABLE); //⑤使能定时器 4
//}
//u8 led_delay_tick=0;
//定时器 4 中断服务函数
//void TIM4_IRQHandler(void)
//{
//   if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
//   {
//      led_delay_tick++;
//   }
//    TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清除中断标志位
//}
