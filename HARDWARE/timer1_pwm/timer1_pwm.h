#ifndef  __TIMER1_PWM_H
#define  __TIMER1_PWM_H
#include "sys.h"


extern void TIM1_PWM_Init(u32 arr,u32 psc);
void init_led_timer(void);
#endif

