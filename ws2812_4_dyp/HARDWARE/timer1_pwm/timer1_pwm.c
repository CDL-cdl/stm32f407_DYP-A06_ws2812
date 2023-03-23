#include"timer1_pwm.h"
//TIM1 PWM ���ֳ�ʼ��
//PWM �����ʼ��
//arr���Զ���װֵ psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u32 arr,u32 psc)
{
	    //PE 8 9
	  GPIO_InitTypeDef GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
      TIM_OCInitTypeDef  TIM_OCInitStructure;
	  
      
	  /*u32 TimerPeriod =  (SystemCoreClock / 20000 ) - 1;
      u32 ccr1 = TimerPeriod / 2;  //ռ�ձ�1/2 = 50%
      u32 ccr2 = TimerPeriod / 3;  //ռ�ձ�1/3 = 33%
      u32 ccr3 = TimerPeriod / 4;  //ռ�ձ�1/4 = 25%
      u32 ccr4 = TimerPeriod / 5;  //ռ�ձ�1/5 = 20%*/
  

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	  
      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	  
	  
     //ʱ����ʼ��
     TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//TIM_CKD_DIV1; //���������á�
     TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������
     TIM_TimeBaseInitStructure.TIM_Prescaler = psc;   //Timer clock = sysclock /(TIM_Prescaler+1) = 168M
     //TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInitStructure.TIM_Period =arr;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
     TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

  
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM_OCMode_PWM1;//�� control or ��control
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
     TIM_OCInitStructure.TIM_Pulse = 0;	//ע��˴�ӦΪ0����Ȼ�ϵ���һ��ws2812�ƻ������ɫ
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM_OCPolarity_High;
	 //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
     TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	 TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ��� ��䲻��Ӱ�춨ʱ�����ܣ��׵�ʱ������˸
	 TIM_ARRPreloadConfig(TIM1, ENABLE);//ARPE ʹ��
     /* TIM1 Update DMA Request enable */
	 TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);
  	 
     TIM_Cmd(TIM1,ENABLE);
     TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

 
     
   


