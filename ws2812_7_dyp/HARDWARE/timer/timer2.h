#ifndef __TIMER2_H
#define __TIMER2_H
#include"sys.h"
#include"led.h"
#include"delay.h"

extern u8 led_delay_tick;
extern u8 dyp_delay_tick;
extern u8 led_delay_tick_h;
extern u8 breating_led_tick;
extern u8 color_tick;
extern u8 blink_tick;
extern u8 color_running_tick;
extern void TIM2_Int_Init(u16 arr,u16 psc);
#endif
