#include"timer1_pwm.h"
//TIM1 PWM 部分初始化
//PWM 输出初始化
//arr：自动重装值 psc：时钟预分频数
void TIM1_PWM_Init(u32 arr,u32 psc)
{
	    //PE 8 9
	  GPIO_InitTypeDef GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
      TIM_OCInitTypeDef  TIM_OCInitStructure;
	  
      
	  /*u32 TimerPeriod =  (SystemCoreClock / 20000 ) - 1;
      u32 ccr1 = TimerPeriod / 2;  //占空比1/2 = 50%
      u32 ccr2 = TimerPeriod / 3;  //占空比1/3 = 33%
      u32 ccr3 = TimerPeriod / 4;  //占空比1/4 = 25%
      u32 ccr4 = TimerPeriod / 5;  //占空比1/5 = 20%*/
  

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	  
      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	  
	  
     //时基初始化
     TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//TIM_CKD_DIV1; //死区控制用。
     TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器方向
     TIM_TimeBaseInitStructure.TIM_Prescaler = psc;   //Timer clock = sysclock /(TIM_Prescaler+1) = 168M
     //TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInitStructure.TIM_Period =arr;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
     TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

  
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM_OCMode_PWM1;//正 control or 反control
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
     TIM_OCInitStructure.TIM_Pulse = 0;	//注意此处应为0，不然上电后第一个ws2812灯会出现绿色
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM_OCPolarity_High;
	 //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
     TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	 TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能预装载寄存器 这句不加影响定时器性能，白灯时出现闪烁
	 TIM_ARRPreloadConfig(TIM1, ENABLE);//ARPE 使能
     /* TIM1 Update DMA Request enable */
	 TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);
  	 
     TIM_Cmd(TIM1,ENABLE);
     TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

 
     
   


