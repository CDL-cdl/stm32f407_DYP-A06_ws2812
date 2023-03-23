#include"iwdg.h"
//初始化独立看门狗
//prer:分频数:0~7(只有低 3 位有效!) rlr:自动重装载值,0~0XFFF.
//分频因子=4*2^prer.但最大值只能是 256!
//rlr:重装载寄存器值:低 11 位有效.
//STM32 F4  开发指南( ( 库函数 版) )
//ALIENTEK  探索者 STM32F407  开发板教程
//时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_init(u8 prer,u16 rlr)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //取消寄存器写保护
    IWDG_SetPrescaler(prer); //设置 IWDG 分频系数
    IWDG_SetReload(rlr); //设置 IWDG 装载值
    IWDG_ReloadCounter(); //reload
    IWDG_Enable(); //使能看门狗
}
//喂独立看门狗
void IWDG_Feed(void)
{
    IWDG_ReloadCounter();//reload
}
