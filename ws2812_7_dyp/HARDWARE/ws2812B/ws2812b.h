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


#define WHITE_LED  	0x00		//������ʾ��ɫ
#define RED_LED  		0x01		//������ʾ��ɫ
#define ORANGE_LED  0x02		//������ʾ��ɫ
#define YELLOW_LED  0x03		//������ʾ��ɫ
#define GREEN_LED  	0x04		//������ʾ��ɫ
#define L_GREEN_LED 0x05		//������ʾ��ɫ
#define BLUE_LED  	0x06		//������ʾ��ɫ
#define PURPLE_LED  0x07		//������ʾ��ɫ

#define WHITE_SLOW_FLASH      0x08		//�׵�����
#define RED_SLOW_FLASH   		  0x09		//�������
#define ORANGE_SLOW_FLASH     0x0A		//�ȵ�����
#define YELLOW_SLOW_FLASH     0x0B		//��ɫ����
#define GREEN_SLOW_FLASH    	0x0C		//��ɫ����
#define L_GREEN_SLOW_FLASH    0x0D		//��ɫ����:
#define BLUE_SLOW_FLASH    		0x0E		//��ɫ����
#define PURPLE_SLOW_FLASH   	0x0F		//��ɫ����

#define RED_T_LEFT    	0x10		//��ɫ��ת
#define RED_T_RIGHT     0x11		//��ɫ��ת
#define ORGNGE_T_LEFT   0x12		//��ɫ��ת
#define ORGNGE_T_RIGHT  0x13		//��ɫ��ת

#define RED_BREATHING_LIGHT   			0x20		//������ģʽ����ƽ�����ͣ0.3s��������ͣ0.7s
#define BLUE_BREATHING_LIGHT  			0x21		//������ģʽ�����ƽ�����ͣ0.3s��������ͣ0.7s
#define GREEN_BREATHING_LIGHT   		0x22		//������ģʽ���̵ƽ�����ͣ0.3s��������ͣ0.7s
#define YELLOW_BREATHING_LIGHT	  	0x23		//������ģʽ���Ƶƽ�����ͣ0.3s��������ͣ0.7s

#define RED_FLASH1    	0x31		//��ɫ��1��
#define RED_FLASH2    	0x32		//��ɫ��2��
#define RED_FLASH3    	0x33		//��ɫ��3��
#define RED_FLASH4    	0x34		//��ɫ��4��
#define RED_FLASH5    	0x35		//��ɫ��5��
#define RED_FLASH6    	0x36		//��ɫ��6��
#define RED_FLASH7    	0x37		//��ɫ��7��

#define ENERGY_SAVING         0xF0		//����ģʽ

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
