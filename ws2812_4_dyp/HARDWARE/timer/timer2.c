#include "timer2.h"

//通用定时器2 中断初始化
//arr：自动重装值。 psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.  Ft=72Mhz 
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器 2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //①使能 TIM2 时钟

  TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
  TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //定时器分频
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//设置时钟分割
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);// ②初始化定时器 TIM2
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //③允许定时器 2 更新中断

  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器 2 中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级 1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //响应优先级 3
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);// ④初始化 NVIC
   
  TIM_Cmd(TIM2,ENABLE); //⑤使能定时器 2
}
//定时器 2 中断服务函数
u8 led_delay_tick=0,led_delay_tick_h=0,breating_led_tick = 0,breating_ppms=0,ppms = 0;
u8 dyp_delay_tick=0, dyp_ppms=0;
u8 color_tick=0,color_ppms=0;
u8 blink_tick=0;
u8 switch_tick=0; 
u8 color_running_ppms=0, color_running_tick=0;

void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
   {
		 //breating_led_tick ++;
		 color_ppms++;
		 breating_ppms++;
		 ppms ++;
		 dyp_ppms++;
		 blink_tick++;				//0.001s/blink_tick
		 color_running_ppms++;	
				 
		 if(color_ppms>=3){
			 color_tick ++;
			 color_ppms=0;
		 }
		 if(breating_ppms >=10){							
			 breating_led_tick++;														//0.01s/breating_led_tick
			 breating_ppms=0;
		 }
		 if(color_running_ppms>=10){
			 color_running_tick ++;
			 color_running_ppms=0;
		 }
		 if(ppms >= 100){
      led_delay_tick++;led_delay_tick_h++;
			ppms = 0;
		 }
		 if(dyp_ppms >= 100){															//  0.1s/dyp_delay_tick
      dyp_delay_tick++;
			dyp_ppms = 0;
		 }
   }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位
}

