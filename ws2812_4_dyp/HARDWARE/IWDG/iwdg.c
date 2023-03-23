#include"iwdg.h"
//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е� 3 λ��Ч!) rlr:�Զ���װ��ֵ,0~0XFFF.
//��Ƶ����=4*2^prer.�����ֵֻ���� 256!
//rlr:��װ�ؼĴ���ֵ:�� 11 λ��Ч.
//STM32 F4  ����ָ��( ( �⺯�� ��) )
//ALIENTEK  ̽���� STM32F407  ������̳�
//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_init(u8 prer,u16 rlr)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ȡ���Ĵ���д����
    IWDG_SetPrescaler(prer); //���� IWDG ��Ƶϵ��
    IWDG_SetReload(rlr); //���� IWDG װ��ֵ
    IWDG_ReloadCounter(); //reload
    IWDG_Enable(); //ʹ�ܿ��Ź�
}
//ι�������Ź�
void IWDG_Feed(void)
{
    IWDG_ReloadCounter();//reload
}
