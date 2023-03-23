#ifndef __WS2812B_H
#define __WS2812B_H
#include "sys.h"
#include "delay.h"
#include "dma1_ch_init.h"
#include "timer3.h"
#include "timer2.h"
#include "stdint.h"
#include "stdbool.h"

#define WHITE_FLY  	0x00
#define RED_FLY 	 	0x01
#define ORGANGE_FLY 0x02
#define YELLOW_FLY  0x03
#define GREEN_FLY 	0x04
#define L_GREEN_FLY 0x05
#define BLUE_FLY  	0x06
#define PURPLE_FLY  0x07


#define WHITE_LED  	0x00		//灯条显示白色
#define RED_LED  		0x01		//灯条显示红色
#define ORANGE_LED  0x02		//灯条显示橙色
#define YELLOW_LED  0x03		//灯条显示黄色
#define GREEN_LED  	0x04		//灯条显示绿色
#define L_GREEN_LED 0x05		//灯条显示青色
#define BLUE_LED  	0x06		//灯条显示蓝色
#define PURPLE_LED  0x07		//灯条显示紫色

#define WHITE_SLOW_FLASH      0x08		//白灯慢闪
#define RED_SLOW_FLASH   		  0x09		//红灯慢闪
#define ORANGE_SLOW_FLASH     0x0A		//橙灯慢闪
#define YELLOW_SLOW_FLASH     0x0B		//黄色慢闪
#define GREEN_SLOW_FLASH    	0x0C		//绿色慢闪
#define L_GREEN_SLOW_FLASH    0x0D		//青色慢闪:
#define BLUE_SLOW_FLASH    		0x0E		//蓝色慢闪
#define PURPLE_SLOW_FLASH   	0x0F		//紫色慢闪

#define RED_T_LEFT    	0x10		//红色左转
#define RED_T_RIGHT     0x11		//红色右转
#define ORGNGE_T_LEFT   0x12		//橙色左转
#define ORGNGE_T_RIGHT  0x13		//橙色右转

#define RED_BREATHING_LIGHT   			0x20		//呼吸灯模式：红灯渐渐暗停0.3s、渐渐亮停0.7s
#define BLUE_BREATHING_LIGHT  			0x21		//呼吸灯模式：蓝灯渐渐暗停0.3s、渐渐亮停0.7s
#define GREEN_BREATHING_LIGHT   		0x22		//呼吸灯模式：绿灯渐渐暗停0.3s、渐渐亮停0.7s
#define YELLOW_BREATHING_LIGHT	  	0x23		//呼吸灯模式：黄灯渐渐暗停0.3s、渐渐亮停0.7s

#define RED_FLASH1    	0x31		//红色闪1次
#define RED_FLASH2    	0x32		//红色闪2次
#define RED_FLASH3    	0x33		//红色闪3次
#define RED_FLASH4    	0x34		//红色闪4次
#define RED_FLASH5    	0x35		//红色闪5次
#define RED_FLASH6    	0x36		//红色闪6次
#define RED_FLASH7    	0x37		//红色闪7次

#define ENERGY_SAVING         0xF0		//节能模式

extern void led_turn(bool dir_l,u8 RR,u8 GG,u8 BB,u8 WW);
extern void led_turn_h(bool dir_l,u8 RR,u8 GG,u8 BB,u8 WW);
extern void led_flow(u8 code_cmd);
extern void led_flow_H(u8 code_cmd);
extern void led_fly(u8 spd,u8 date_cmd);
extern void led_fly_H(u8 spd,u8 date_cmd);


extern void breathing_blue(u8 per);
extern void breathing_red(u8 per);
extern void breathing_green(u8 per);
extern void breathing_purple(u8 per);
extern void breathing_orange(u8 per);
extern void breathing_white(u8 per);
extern void breathing_yellow(u8 per);
extern void breathing_color_blue(u8 per);
extern void breathing_color_purple(u8 per);
extern void breathing_color_orange(u8 per);
extern void double_blink(u8 r, u8 g, u8 b, u8 w);
extern void blink(u8 r, u8 g, u8 b, u8 w, u8 freq);


void send_string_data(u8 RR,u8 GG,u8 BB,u8 WW);
void send_string_data_H(u8 RR,u8 GG,u8 BB,u8 WW);
void multicolor();
void multicolor_h();
void led_one(u8 one);
void flash_and_stay_H(u8 flash_times,u8 stay_time,u8 r,u8 g ,u8 b,u8 w);
void flash_and_stay (u8 flash_times,u8 stay_time,u8 r,u8 g ,u8 b,u8 w);
#endif
