#ifndef __TIMER3_H
#define __TIMER3_H
#include"sys.h"
#include"led.h"
#include"delay.h"
#include"iwdg.h"

extern u8 tim3_count;
extern void TIM3_Int_Init(u16 arr,u16 psc);

#endif
