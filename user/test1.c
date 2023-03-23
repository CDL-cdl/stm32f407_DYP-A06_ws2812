#include "includes.h"
#include "stm32f10x.h"
#include "usart.h"
#include "ws2812b.h"

#define LIGHT_LED_NUM_H		7
#define LED_LENTH_H       7

#define LIGHT_LED_NUM		7
#define LED_LENTH       7
extern u32 cmd;

#define BYTE0(cmd)       (*(char *)(&cmd))
#define BYTE1(cmd)       (*((char *)(&cmd) + 1))
#define BYTE2(cmd)       (*((char *)(&cmd) + 2))
#define BYTE3(cmd)       (*((char *)(&cmd) + 3))
u8 test_cmd;
u8 send_buf[7];

void (*f[256])(void);
void devices_init(void)
{
  delay_init();
	LED_Init();
//	GPIO_input_init();
  USART_Config();
	USART3_Configuration();
	USART2_Configuration();
	TIM2_Int_Init(2000-1,36-1);  
	TIM3_PWM_Init(88-1,1-1);
	TIM4_PWM_Init(88-1,1-1);
} 

int number = 0;
bool double_blink_flag = false;
u8 last_cmd = 0;
extern int breating_change;
void breating_white_5(){
	breathing_white(5);
}
void breating_white_3(){
	breathing_white(3);
}
void breating_white_1(){
	breathing_white(1);
}

void blink_blue_middle(){
	blink(0,0,255,0,2);
}
void blink_white_middle(){
	blink(0,0,0,255,4);
}

void double_blink_breating_blue_5(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,255,0);
				}
			}
			breathing_blue(5);
}

void double_blink_breating_blue_3(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,255,0);
				}
			}
			breathing_blue(3);
}

void double_blink_breating_blue_1(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,255,0);
				}
			}
			breathing_blue(1);
}
void double_blink_breating_white_5(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,0,255);
				}
			}
			breathing_white(5);
}

void double_blink_breating_white_3(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,0,255);
				}
			}
			breathing_white(3);
}

void double_blink_breating_white_1(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,0,255);
				}
			}
			breathing_white(1);
}

void running_water_blue(){
	led_fly(1,BLUE_FLY);
	led_fly_H(1,BLUE_FLY);
}

void running_water_green(){
	led_fly(1,GREEN_FLY);
	led_fly_H(1,GREEN_FLY);
}

void colorful_led(){
	switch (breating_change%=3){
		case 0:breathing_color_purple(1);break;
		//case 1:breathing_green(1);break;
		case 1:breathing_color_orange(1);break;
		case 2:breathing_color_blue(1);break;
		//case 4:breathing_red(1);break;
	}
}

void red_or_yellow(){
	send_string_data(255,0,0,0);
	delay_ms(500);
	send_string_data(255,255,0,0);
	delay_ms(500);
}

void blink_red_fast(){
	blink(255,0,0,0,4);
}
void blink_red_middle(){
	blink(255,0,0,0,2);
}

void blink_white_fast(){
	blink(0,0,0,255,4);
}

void Rainbowcolor(){
	multicolor();
}

void always_red(){
	send_string_data(255,0,0,0);
}
void always_yellow(){
	send_string_data(255,255,0,0);
}

void always_blue(){
	send_string_data(0,0,255,0);
}

void always_green(){
	send_string_data(0,255,0,0);
}
void breating_green_5(){
	breathing_green(5);
}

void breating_blue_5(){
	breathing_blue(5);
}
void breating_blue_3(){
	breathing_blue(3);
}
void breating_blue_1(){
	breathing_blue(1);
}

void breating_yellow_5(){
	breathing_yellow(5);
}
void breating_yellow_3(){
	breathing_yellow(3);
}
void breating_yellow_1(){
	breathing_yellow(1);
}

void blink_yellow_middle(){
	blink(255,255,0,0,4);
}


void double_blink_breating_yellow_5(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(255,255,0,0);
				}
			}
			breathing_yellow(5);
}

void double_blink_breating_yellow_3(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(255,255,0,0);
				}
			}
			breathing_yellow(3);
}
void double_blink_breating_yellow_1(){
		if(last_cmd != cmd){
			last_cmd = cmd;
			if(true){
				double_blink(255,255,0,0);
			}
		}
		breathing_yellow(1);
}

void double_blink_blink_white_middle(){
			if(last_cmd != cmd){
				last_cmd = cmd;
				if(true){
					double_blink(0,0,0,255);
				}
			}
			blink_white_middle();
}

void double_blink_yellow_middle(){
		if(last_cmd != cmd){
			last_cmd = cmd;
			if(true){
				double_blink(255,255,0,0);
			}
		}
		blink_yellow_middle();
}
void LEDTest()
{
		send_string_data(0,0,0,64);
}

   u8 R[LED_LENTH_H];
   u8 G[LED_LENTH_H];
   u8 B[LED_LENTH_H];
	 u8 W[LED_LENTH_H];
	 u8 i;

void colors(u8 RR,u8 GG,u8 BB,u8 WW)
{
	send_string_data(RR,GG,BB,WW);
}
int main(void)
{
	int FLAG=1;
	int last_cmd = 0;
  devices_init();     //每0.01s中断一次

	cmd=0;

//	u8 sum1,sum2,sum3,sum4;
	f[0] = running_water_blue;
	f[1] = breating_blue_5;
	f[2] = Rainbowcolor;
	f[3] = breating_blue_5;
	f[4] = breating_blue_3;
	f[5] = breating_blue_1;
	f[6] = breating_white_3;
	f[7] = colorful_led;
	f[8] = blink_white_middle;
	f[9] = blink_blue_middle;
	f[0x12] = always_yellow;
	f[0x13] = breating_yellow_5;
	f[0x14] = breating_yellow_3;
	f[0x15] = breating_yellow_1;
	f[0x16] = breating_yellow_3;
	f[0x18] = blink_yellow_middle;	
	f[0x41] = breating_green_5;
	f[0x42] = always_blue;
	f[0x43] = double_blink_breating_white_5;
	f[0x44] = double_blink_breating_white_3;
	f[0x45] = double_blink_breating_white_1;
	f[0x46] = double_blink_breating_blue_3;
	f[0x47] = colorful_led;
	f[0x48] = double_blink_blink_white_middle;
	f[0x53] = double_blink_breating_yellow_5;
	f[0x54] = double_blink_breating_yellow_3;
	f[0x55] = double_blink_breating_yellow_1;
	f[0x56] = double_blink_breating_yellow_3;

	f[0x58] = double_blink_yellow_middle;
	f[0x59] = breating_yellow_5;
	f[0x60] = breating_yellow_3;
	f[0x61] = breating_yellow_1;
	f[0x81] = red_or_yellow;
	f[0x82] = blink_red_middle;
	f[0x83] = always_red;
	f[0x84] = blink_red_fast;
	f[0x85] = blink_white_fast;
	f[0x86] = Rainbowcolor;
	f[255] = blink_yellow_middle;
	f[254] = LEDTest;
	
	
	//char send_buffer[7];
	

  while(1){ 	
//		led_flow(0x21);
				if(f[cmd] != NULL)
					f[cmd]();
//		Usart_SendString(USART2,"USART2_TEST\r\n");
//		Usart_SendString(USART3,"USART3_TEST\r\n");
		u8 check_sum=0;
		if(dyp_delay_tick>=1){									//  0.1s/tick
			USART_SendData(USART2,0xff);					//向usart2发送ff
			USART_SendData(USART3,0xff);					//向usart3发送ff
			dyp_delay_tick=0;
			
			send_buf[0]=0x44;
			send_buf[1]=0x52;
			
			if((usart2_flag == 1)&&(usart3_flag == 1)){
				int i=0;
				for(i=0;i<2;i++){
					send_buf[2+i]=uart2_buf[i+1];
					send_buf[4+i]=uart3_buf[i+1];
				}
				int j=0;
				for(j=0;j<6;j++){
					check_sum+=send_buf[j];		//校验和
				}
	
				send_buf[6]=check_sum;
				
				int k=0;
				for(k=0;k<7;k++){
					USART_SendData(USART1,send_buf[k]);		//发出
					u8 usart2_flag=0;				
					u8 usart3_flag=0;				
					while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 				//等发送完毕			
				}
			}
		}
	}
}
//		send_buf[0]=0x44;
//		send_buf[1]=0x52;

//		if((usart2_flag == 1)&&(usart3_flag == 1)){
//			int i=0;
//			for(i=0;i<2;i++){
//				send_buf[2+i]=uart2_buf[i+1];
//				send_buf[4+i]=uart3_buf[i+1];
//			}
//			int j=0;
//			for(j=0;j<6;j++){
//				check_sum+=send_buf[j];
//			}
//	
//			send_buf[6]=check_sum;
//			int k=0;
//			for(k=0;k<7;k++){
//				USART_SendData(USART1,send_buf[k]);
//				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  
//			u8 usart2_flag=0;
//			u8 usart3_flag=0;				
//			}
//		}
//		}
//}




