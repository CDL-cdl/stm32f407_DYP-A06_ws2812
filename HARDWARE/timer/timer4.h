#ifndef __TIMER4_H
#define __TIMER4_H
#include"sys.h"
#include"led.h"
#include"delay.h"
#include"iwdg.h"

extern u8 led_delay_tick;
extern void TIM4_Int_Init(u16 arr,u16 psc);

#endif
