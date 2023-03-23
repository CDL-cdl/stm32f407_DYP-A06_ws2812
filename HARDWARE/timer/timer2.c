#include "timer2.h"

//ͨ�ö�ʱ��2 �жϳ�ʼ��
//arr���Զ���װֵ�� psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.  Ft=72Mhz 
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ�� 2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //��ʹ�� TIM2 ʱ��

  TIM_TimeBaseInitStructure.TIM_Period = arr; //�Զ���װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��ʱ����Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//����ʱ�ӷָ�
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);// �ڳ�ʼ����ʱ�� TIM2
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //������ʱ�� 2 �����ж�

  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ�� 2 �ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ� 1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //��Ӧ���ȼ� 3
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);// �ܳ�ʼ�� NVIC
   
  TIM_Cmd(TIM2,ENABLE); //��ʹ�ܶ�ʱ�� 2
}
//��ʱ�� 2 �жϷ�����
u8 led_delay_tick=0,led_delay_tick_h=0,breating_led_tick = 0,breating_ppms=0,ppms = 0;
u8 dyp_delay_tick=0, dyp_ppms=0;
u8 color_tick=0,color_ppms=0;
u8 blink_tick=0;
u8 switch_tick=0; 
u8 color_running_ppms=0, color_running_tick=0;

void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
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
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ
}

