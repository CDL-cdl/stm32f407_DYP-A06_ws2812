#include"timer3.h"
/********************************************************
*				�����Ͻ������˹ɷ����޹�˾				*
*					  �콨��							*
*					 2015/8/24							*
*******************************************************/
//ͨ�ö�ʱ��2 �жϳ�ʼ��
//arr���Զ���װֵ�� psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ�� 3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //��ʹ�� TIM2 ʱ��

  TIM_TimeBaseInitStructure.TIM_Period = arr; //�Զ���װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��ʱ����Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// �ڳ�ʼ����ʱ�� TIM2
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //������ʱ�� 2 �����ж�

  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ�� 2 �ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ� 1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //��Ӧ���ȼ� 3
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);// �ܳ�ʼ�� NVIC

  TIM_Cmd(TIM3,ENABLE); //��ʹ�ܶ�ʱ�� 3
}
u8 tim3_count=0;
//��ʱ�� 3 �жϷ�����
void TIM3_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
   {
      tim3_count++;
   }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //����жϱ�־λ
}
