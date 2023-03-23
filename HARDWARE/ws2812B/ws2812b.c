#include "ws2812b.h"
#include "timer2.h"
#include "stdint.h"
#include "stdbool.h"

#define LIGHT_LED_NUM_H		7
#define LED_LENTH_H       7

#define LIGHT_LED_NUM		7
#define LED_LENTH       7

#define T_LEFT  1
#define T_RIGHT 0

const u16 ws_dat_0_duty_cnt=30;
const u16 ws_dat_1_duty_cnt=53;


u16  ws_dat_bit_buf_h[LIGHT_LED_NUM_H * 32 + 1];
u16  ws_dat_bit_buf [LIGHT_LED_NUM  * 32 + 1];

void ws_set_led_rgb(u8 *r, u8 *g, u8 *b, u8 *w, u8 led_cnt);
void ws_set_led_rgb_H(u8 *r, u8 *g, u8 *b, u8 *w, u8 led_cnt);

void ws_set_led_rgb_H_left(u8 *r, u8 *g, u8 *b, u8 *w, u8 led_cnt);

u8 brightness_h=0,brightness_h_flag=0;  //brightness_h_flag=0变亮 =1变暗

#define size_h LIGHT_LED_NUM_H  //数据显示个数变量 控制LED数量

u8 Table_R[3]={ 255,128,0};   //白色 无色
u8 Table_G[3]={	255,128,0};
u8 Table_B[3]={	255,128,0};
u8 Table_W[3]={	255,128,0};
	u8 r[LED_LENTH+1];
	u8 g[LED_LENTH+1];
	u8 b[LED_LENTH+1];
	u8 w[LED_LENTH+1];
void multicolor()
{

	 u8 i;
	 u8 temp_c = 0;
	 static int count = 0;
	
	 u8 r0,g0,b0,w0;

//	 r[0] = 255; g[0] = 0;   b[0] = 0;   w[0] = 0;
//	 r[1] = 255; g[1] = 128; b[1] = 0;   w[1] = 0;
//	 r[2] = 255; g[2] = 255; b[2] = 0;   w[2] = 0;
//	 r[3] = 0;   g[3] = 255; b[3] = 0;   w[3] = 0;
//	 r[4] = 0;   g[4] = 0;   b[4] = 255; w[4] = 0;
//	 r[5] = 0;   g[5] = 255; b[5] = 255; w[5] = 0;
//	 r[6] = 255; g[6] = 0;   b[6] = 255; w[6] = 0;

	if(!count){
//	 r[0] = 0;     g[0] = 0;     b[0] = 255;   w[0] = 0;
//	 r[1] = 0;     g[1] = 255;   b[1] = 255;   w[1] = 0;
//	 r[2] = 255;   g[2] = 0;     b[2] = 255;   w[2] = 0;
//	 r[3] = 0;     g[3] = 0;     b[3] = 255;   w[3] = 0;
//	 r[4] = 0;     g[4] = 255;   b[4] = 255;   w[4] = 0;
//	 r[5] = 255;   g[5] = 0;     b[5] = 255;   w[5] = 0;		//紫
//	 r[6] = 0;     g[6] = 0;     b[6] = 255;   w[6] = 0;
	 r[0] = 78;     g[0] = 62;     b[0] = 217;   w[0] = 0;
	 r[1] = 156;     g[1] = 83;   b[1] = 232;   w[1] = 0;
	 r[2] = 222;   g[2] = 68;     b[2] = 248;   w[2] = 0;
	 r[3] = 248;     g[3] = 0;     b[3] = 255;   w[3] = 0;
	 r[4] = 216;     g[4] = 71;   b[4] = 247;   w[4] = 0;
	 r[5] = 152;   g[5] = 85;     b[5] = 231;   w[5] = 0;		//紫
	 r[6] = 72;     g[6] = 60;     b[6] = 215;   w[6] = 0;
		
		 ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM);
		 ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
		count = 1;
	}
//	r0=r[0];g0=g[0];b0=b[0];w0=w[0];
//	for(i = 1; i < LIGHT_LED_NUM; i++){
//			 test1++;
//			 r[i-1]=r[i];
//			 g[i-1]=g[i];
//			 b[i-1]=b[i];
//			 w[i-1]=w[i];			 
//	}
//	 r[6]=r0;g[6]=g0;b[6]=b0;w[6]=w0;
//		 ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM);
//		 ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
//		 delay_ms(100);
		
	if(color_running_tick>=10)
	 {
		 color_running_tick=0;
		
		 r0=r[0];g0=g[0];b0=b[0];w0=w[0];
		
		 for(i=1;i<LIGHT_LED_NUM;i++)
		 { 
			 r[i-1]=r[i];
			 g[i-1]=g[i];
			 b[i-1]=b[i];
			 w[i-1]=w[i];			 
		 }
		 r[6]=r0;g[6]=g0;b[6]=b0;w[6]=w0;
		 
		 ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM);
		 ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
    } 
}

void multicolor_h()
{
	 u8 r[LED_LENTH];
   u8 g[LED_LENTH];
   u8 b[LED_LENTH];
	 u8 w[LED_LENTH];
	 u8 i;
	 u8 r0,g0,b0,w0;
	
	 r[0] = 0;   g[0] = 255; b[0] = 0;     w[0] = 0;
	 r[1] = 0;   g[1] = 0;   b[1] = 255;   w[1] = 0;
	 r[2] = 0;   g[2] = 0;   b[2] = 255;   w[2] = 0;
	 r[3] = 0;   g[3] = 255; b[3] = 255;   w[3] = 0;
	 r[4] = 0;   g[4] = 255; b[4] = 255;   w[4] = 0;
	 r[5] = 128; g[5] = 0;   b[5] = 255;   w[5] = 0;		//紫
	 r[6] = 128; g[6] = 0;   b[6] = 255;   w[6] = 0;
	
	 if(color_running_tick>=10)
	 {
		 color_running_tick=0;
		 
		 r0=r[6];g0=g[6];b0=b[6];w0=w[6];
		 
		 for(i=0;i<6;i++)
		 {
			 r[i+1]=r[i];
			 g[i+1]=g[i];
			 b[i+1]=b[i];
			 w[i+1]=w[i];
		 }
		 r[0]=r0;g[0]=g0;b[0]=b0;w[0]=w0;
		 ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);	
	 }
}


/*
 *
 *RR,GG,BB三原色
 *
 */
void send_string_data(u8 RR,u8 GG,u8 BB,u8 WW)
{
   u8 r[LED_LENTH];
   u8 g[LED_LENTH];
   u8 b[LED_LENTH];
	 u8 w[LED_LENTH];
   u8 i;
      
    for(i=0;i<LED_LENTH;i++)
    {
      r[i] = RR;
	    g[i] = GG;
	    b[i] = BB;
			w[i] = WW;
    }
   ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM);
	 send_string_data_H(RR, GG, BB, WW);
}

void send_string_data_H(u8 RR,u8 GG,u8 BB,u8 WW)
{
   u8 r[LED_LENTH_H];
   u8 g[LED_LENTH_H];
   u8 b[LED_LENTH_H];
	 u8 w[LED_LENTH_H];
   u8 i;
      
    for(i=0;i<LED_LENTH_H;i++)
    {
      r[i] = RR;
	    g[i] = GG;
	    b[i] = BB;
			w[i] = WW;
    }
   ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
}

void led_turn_h(bool dir_l,u8 RR,u8 GG,u8 BB,u8 WW)
{
   u8 r[LED_LENTH_H];
   u8 g[LED_LENTH_H];
   u8 b[LED_LENTH_H];
	 u8 w[LED_LENTH_H];
   u8 i;
	
   if(dir_l)
	 {
			for(i=0;i<LED_LENTH_H;i++)
			{ 
				
					if(i>=LED_LENTH_H/2)
						{
							r[i] = 0;
							g[i] = 0;
							b[i] = 0;
							w[i] = 0;
						}
					else
						{
						r[i] = RR;
						g[i] = GG;
						b[i] = BB;
						w[i] = WW;
						}
			 }
		}
	 else 
	 {
		 	for(i=0;i<LED_LENTH_H;i++)
			{ 
				
					if(i<=LED_LENTH_H/2)
						{
							r[i] = 0;
							g[i] = 0;
							b[i] = 0;
							w[i] = 0;
						}
					else
						{
						r[i] = RR;
						g[i] = GG;
						b[i] = BB;
						w[i] = WW;
						}
			 }
		 
	 }
   ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
}

void led_turn(bool dir_l,u8 RR,u8 GG,u8 BB,u8 WW)
{
   u8 r[LED_LENTH_H];
   u8 g[LED_LENTH_H];
   u8 b[LED_LENTH_H];
	 u8 w[LED_LENTH_H];
   u8 i;
	
   if(dir_l)
	 {
			for(i=0;i<LED_LENTH;i++)
			{ 
				
					if(i>=LED_LENTH/2)
						{
							r[i] = 0;
							g[i] = 0;
							b[i] = 0;
							w[i] = 0;
						}
					else
						{
						r[i] = RR;
						g[i] = GG;
						b[i] = BB;
						w[i] = WW;
						}
			 }
		}
	 else 
	 {
		 	for(i=0;i<LED_LENTH;i++)
			{ 
				
					if(i<=LED_LENTH/2)
						{
							r[i] = 0;
							g[i] = 0;
							b[i] = 0;
							w[i] = 0;
						}
					else
						{
						r[i] = RR;
						g[i] = GG;
						b[i] = BB;
						w[i] = WW;
						}
			 }
		 
	 }
   ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM);
}

/*
 *将数据发送给底层hardware 
 */
void ws_set_led_rgb(u8 *r, u8 *g, u8 *b, u8 *w, u8 led_cnt)
{
   u16 i;
   u8  j;
   u8  k;
   u8  temp;

   i=0;
   for(j=0;j<led_cnt;j++)
   {
       temp=*(g+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }

	   temp=*(r+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }

	   temp=*(b+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }
	   	   temp=*(w+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }
   }
  ws_dat_bit_buf[i++]=0;//给发送位的结束赋值

   dma1_ch3_init(ws_dat_bit_buf,i);
   delay_us(50);	  
}

void ws_set_led_rgb_H(u8 *r, u8 *g, u8 *b, u8 *w, u8 led_cnt)
{
   u16 i;
   u8  j;
   u8  k;
   u8  temp;

   i=0;
   for(j=0;j<led_cnt;j++)
   {
       temp=*(g+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf_h[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf_h[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }

	   temp=*(r+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf_h[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf_h[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }

	   temp=*(b+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf_h[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf_h[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }
	   	   temp=*(w+j);
	   for(k=0; k<8; k++)
	   {
	   	   if(temp & 0x80)ws_dat_bit_buf_h[i++]=ws_dat_1_duty_cnt;
		   else ws_dat_bit_buf_h[i++]=ws_dat_0_duty_cnt;
		   temp<<=1;
	   }
   }
  ws_dat_bit_buf_h[i++]=0;//给发送位的结束赋值

   dma1_ch7_init(ws_dat_bit_buf_h,i);
   delay_us(50);	  
}



int breating_max = 0;
int breating_change = 0;
extern int number;
extern bool double_blink_flag;
extern u8 last_cmd;
void led_flow(u8 code_cmd)
{

    switch(code_cmd)
    {
			case 0x00://灯条显示白色
	    	{
					send_string_data(0,0,0,255);
					break;
       	}
		  case 0x01://灯条显示红色
	   	  {
					send_string_data(255,0,0,0);
					break;
       	 }
		  case 0x02://灯条显示橙色
		    {
		      send_string_data(255,100,0,0);
			    break;
		    }
		  case 0x03://灯条显示黄色
	   	  {
			    send_string_data(255,255,0,0);
			    break;
       	}
		  case 0x04://灯条显示绿色
	   	  {
			    send_string_data(0,255,0,0);
			    break;
       	}	
		  case 0x05://灯条显示青色
	   	  {
			    send_string_data(0,120,255,0);
			    break;
       	}
		  case 0x06://灯条显示蓝色
	   	  {
			    send_string_data(0,0,255,0);
			    break;
       	}			
		  case 0x07://灯条显示紫色
	   	  {
			    send_string_data(150,0,150,0);
			    break;
       	}				
		  case 0x08://白灯慢闪
	   	  {
		       if(led_delay_tick_h<=5)
			       {  
			   	     send_string_data(0,0,0,255);			    
			       }
		    	else
			       {
			        	send_string_data(0,0,0,0);
		        	}
		     	if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
			    break;
         }
		  case 0x09://红灯慢闪
	    	{
					 if(led_delay_tick_h<=5)
						{  
							send_string_data(255,0,0,0);   
						}
					else
						{
							send_string_data(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
			    break;
       	}
		  case 0x0A://橙灯慢闪
	   	  {
			    if(led_delay_tick_h<=5)
						{  
							send_string_data(255,100,0,0);   
						}
					else
						{
							send_string_data(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
						break;
       	}
		  case 0x0B://黄色慢闪
				{
				  if(led_delay_tick_h<=5)
						{  
							send_string_data(255,255,0,0);   
						}
				  else
						{
							send_string_data(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
					  break;
       	}
		  case 0x0C://绿色慢闪
				{
					 if(led_delay_tick_h<=5)
						 {  
							 send_string_data(0,255,0,0);   
						 }
				   else
				     {
					     send_string_data(0,0,0,0);
				     }
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
					}
		  case 0x0D://青色慢闪
				{
					 if(led_delay_tick_h<=5)
						{  
							send_string_data(0,120,255,0);    
						}
					 else
						{
						  send_string_data(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
					}
			case 0x0E://蓝色慢闪
				{
		      if(led_delay_tick_h<=5)
						{  
							send_string_data(0,0,255,0);    
						}
					 else
						{
						  send_string_data(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
       	}
			case 0x0F://紫色慢闪
				{
		      if(led_delay_tick_h<=5)
						{  
							send_string_data(150,0,150,0);    
						}
					 else
						{
						  send_string_data(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
       	}
			case 0x10://红色左转
				{
					led_turn(T_LEFT,255,0,0,0);
					break;
				}				
			case 0x11://红色右转
				{
					led_turn(T_RIGHT,255,0,0,0);
					break;
				}	  
			case 0x12://橙色左转
				{
					led_turn(T_LEFT,255,255,0,0);
					break;
				}				
			case 0x13://红色右转
				{
					led_turn(T_RIGHT,255,255,0,0);
					break;
				}	
		
			case 0x20://呼吸灯模式：红灯渐渐暗停0.3s、渐渐亮停0.7s
				{ 
					if(led_delay_tick_h%2==0)
				 {
							if(brightness_h_flag==0)brightness_h++;									//渐渐亮
							else brightness_h--;																	//渐渐暗
					 
							send_string_data(brightness_h,0,0,0);
					 
							if(brightness_h>=253){delay_ms(700);brightness_h_flag=1;}//停0.7s切换成渐渐暗
							else if (brightness_h <=0){delay_ms(300);brightness_h_flag=0;}//停0.3s切换成渐渐亮
					}
				 if(led_delay_tick_h>=4)led_delay_tick_h=0;												//时间归零用于循环
		     break;
       	}
			case 0x21://呼吸灯模式：蓝灯   步进1 2 3 对应周期5s 3s 1.5s
				{ 
				 if(brightness_h_flag == 0){
							brightness_h = 1 * breating_led_tick;
							if(brightness_h > 250){
								
								brightness_h_flag = 1;
								breating_max = breating_led_tick;
								breating_led_tick = 0;
							}
						}else if(brightness_h_flag == 1){
							brightness_h = 1*(breating_max - breating_led_tick);
							if(brightness_h <= 0){
								breating_led_tick = 0;
								brightness_h_flag = 0;
							}
						}		
					send_string_data(0,0,brightness_h,0); 						
		     break;
       	}
			case 0x22://呼吸灯模式：绿灯  步进1 2 3 对应周期5s 3s 1.5s
				{ 
				  if(brightness_h_flag == 0){
							brightness_h = 1 * breating_led_tick;
							if(brightness_h > 250){
								
								brightness_h_flag = 1;
								breating_max = breating_led_tick;
								breating_led_tick = 0;
							}
						}else if(brightness_h_flag == 1){
							brightness_h = 1*(breating_max - breating_led_tick);
							if(brightness_h <= 0){
								breating_led_tick = 0;
								brightness_h_flag = 0;
							}
						}	
						send_string_data(0,brightness_h,0,0);    
			
		     break;
       	}
			case 0x23://呼吸灯模式：黄灯  步进1 2 3 对应周期5s 3s 1.5s
				{
						if(brightness_h_flag == 0){
							brightness_h = 1 * breating_led_tick;
							if(brightness_h > 250){
								
								brightness_h_flag = 1;
								breating_max = breating_led_tick;
								breating_led_tick = 0;
							}
						}else if(brightness_h_flag == 1){
							brightness_h = 1*(breating_max - breating_led_tick);
							if(brightness_h <= 0){
								breating_led_tick = 0;
								brightness_h_flag = 0;
							}
						}	
						send_string_data(brightness_h,brightness_h,0,0);    
		     break;
       	}
			case 0x24://呼吸灯模式：紫灯  步进1 2 3 对应周期5s 3s 1.5s
				{
//						blink(100,100,0,0,50);	
//					double_blink(100,100,0,0)		;	
						if(last_cmd != code_cmd){
								last_cmd = code_cmd;
								if(double_blink_flag){
									double_blink(255,255,0,0);
				//					cmd = cmd-0x40;
				//					last_cmd = cmd;
								}
							}
							breathing_yellow(1);					
//					switch (breating_change%=5){
//						case 0:breathing_purple(1);break;
//						case 1:breathing_green(1);break;
//						case 2:breathing_orange(1);break;
//						case 3:breathing_blue(1);break;
//						case 4:breathing_red(1);break;
//					}
						
					
//						if(brightness_h_flag == 0){
//							brightness_h = 3 * breating_led_tick;
//							if(brightness_h > 250){
//								
//								brightness_h_flag = 1;
//								breating_max = breating_led_tick;
//								breating_led_tick = 0;
//							}
//						}else if(brightness_h_flag == 1){
//							brightness_h = 3*(breating_max - breating_led_tick);
//							if(brightness_h <= 0){
//								breating_led_tick = 0;
//								brightness_h_flag = 0;
//							}
//						}
//						send_string_data(brightness_h,0,brightness_h,0);
		     break;
       	}
 
		  case 0x31://红色闪1次
	   	  {
					flash_and_stay( 1, 2, 255, 0, 0, 0); //闪烁次数、暂停时间、 r、g、b、w  
					break;
       	 }
		  case 0x32://红色闪2次
		    {
					flash_and_stay( 2, 2, 255, 0, 0, 0); 
			    break;
		    }
		  case 0x33://红色闪3次
	   	  {
					flash_and_stay( 3, 2, 255, 0, 0, 0); 
			    break;
       	}
		  case 0x34://红色闪4次
	   	  {
					flash_and_stay( 4, 2, 255, 0, 0, 0); 
			    break;
       	}	
		  case 0x35://红色闪5次
	   	  {
					flash_and_stay( 5, 2, 255, 0, 0, 0); 
			    break;
       	}
		  case 0x36://红色闪6次
	   	  {
					flash_and_stay( 6, 2, 255, 0, 0, 0); 
			    break;
       	}			
				
				
			case 0xF0://节能模式
				{
		     send_string_data(0,0,0,0);
		    // LED1_OFF;
		     break;
       	}
		 default:
        {
			    break;
		    }
    }
}

void led_blink(u8 code_cmd){
	switch (code_cmd){
	}
}


void led_flow_H(u8 code_cmd)
{
	
		switch(code_cmd)
    {
			case 0x00://灯条显示白色
	    	{
					send_string_data_H(0,0,0,255);
					break;
       	}
		  case 0x01://灯条显示红色
	   	  {
					send_string_data_H(255,0,0,0);
					break;
       	 }
		  case 0x02://灯条显示橙色
		    {
		      send_string_data_H(255,100,0,0);
			    break;
		    }
		  case 0x03://灯条显示黄色
	   	  {
			    send_string_data_H(255,255,0,0);
			    break;
       	}
		  case 0x04://灯条显示绿色
	   	  {
			    send_string_data_H(0,255,0,0);
			    break;
       	}	
		  case 0x05://灯条显示青色
	   	  {
			    send_string_data_H(0,120,255,0);
			    break;
       	}
		  case 0x06://灯条显示蓝色
	   	  {
			    send_string_data_H(0,0,255,0);
			    break;
       	}			
		  case 0x07://灯条显示紫色
	   	  {
			    send_string_data_H(150,0,150,0);
			    break;
       	}				
		  case 0x08://白灯慢闪
	   	  {
		       if(led_delay_tick_h<=5)
			       {  
			   	     send_string_data_H(0,0,0,255);			    
			       }
		    	else
			       {
			        	send_string_data_H(0,0,0,0);
		        	}
		     	if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
			    break;
         }
		  case 0x09://红灯慢闪
	    	{
				  if(led_delay_tick_h<=5)
						{  
							send_string_data_H(255,0,0,0);   
						}
					else
						{
							send_string_data_H(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
			    break;
       	}
		  case 0x0A://橙灯慢闪
	   	  {
			    if(led_delay_tick_h<=5)
						{  
							send_string_data_H(255,100,0,0);   
						}
					else
						{
							send_string_data_H(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
						break;
       	}
		  case 0x0B://黄色慢闪
				{
				  if(led_delay_tick_h<=5)
						{  
							send_string_data_H(255,255,0,0);   
						}
				  else
						{
							send_string_data_H(0,0,0,0);
						}
					if(led_delay_tick_h>=10)
						led_delay_tick_h=0;
					  break;
       	}
		  case 0x0C://绿色慢闪
				{
					 if(led_delay_tick_h<=5)
						 {  
							 send_string_data_H(0,255,0,0);   
						 }
				   else
				     {
					     send_string_data_H(0,0,0,0);
				     }
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
					}
		  case 0x0D://青色慢闪
				{
					 if(led_delay_tick_h<=5)
						{  
							send_string_data_H(0,120,255,0);    
						}
					 else
						{
						  send_string_data_H(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
					}
			case 0x0E://蓝色慢闪
				{
		      if(led_delay_tick_h<=5)
						{  
							send_string_data_H(0,0,255,0);    
						}
					 else
						{
						  send_string_data_H(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
       	}
			case 0x0F://紫色慢闪
				{
		      if(led_delay_tick_h<=5)
						{  
							send_string_data_H(150,0,150,0);    
						}
					 else
						{
						  send_string_data_H(0,0,0,0);
						}
				   if(led_delay_tick_h>=10)
						 led_delay_tick_h=0;
				     break;
       	}
				
			case 0x10://红色左转
				{
				led_turn_h(T_LEFT,255,0,0,0);
				break;
			}				
			case 0x11://红色右转
				{
				led_turn_h(T_RIGHT,255,0,0,0);
				break;
			}	  
		 	case 0x12://橙色左转
				{
				led_turn_h(T_LEFT,255,255,0,0);
				break;
			}				
			case 0x13://红色右转
				{
				led_turn_h(T_RIGHT,255,255,0,0);
				break;
			}	
			
			case 0x20://呼吸灯模式：红灯渐渐暗停0.3s、渐渐亮停0.7s
				{ 
				 if(led_delay_tick_h%2==0)
				 {
							if(brightness_h_flag==0)brightness_h++;									//渐渐亮
							else brightness_h--;																	//渐渐暗
					 
							send_string_data_H(brightness_h,0,0,0);
					 
							if(brightness_h>=253){delay_ms(700);brightness_h_flag=1;}//停0.7s切换成渐渐暗
							else if (brightness_h <=0){delay_ms(300);brightness_h_flag=0;}//停0.3s切换成渐渐亮
					}
				 if(led_delay_tick_h>=4)led_delay_tick_h=0;												//时间归零用于循环
		     break;
       	}
			case 0x21://呼吸灯模式：蓝灯渐渐暗停0.3s、渐渐亮停0.7s
				{ 
				 if(led_delay_tick_h%2==0)
				 {
							if(brightness_h_flag==0)brightness_h++;									//渐渐亮
							else brightness_h--;																	//渐渐暗
					 
							send_string_data_H(0,0,brightness_h,brightness_h);    //brightness_h/5 是白灯 增加蓝灯亮度
					 
							if(brightness_h>=253){delay_ms(700);brightness_h_flag=1;}//停0.7s切换成渐渐暗
							else if (brightness_h <=0){delay_ms(300);brightness_h_flag=0;}//停0.3s切换成渐渐亮
					}
				 if(led_delay_tick_h>=4)led_delay_tick_h=0;												//时间归零用于循环
		     break;
       	}
			case 0x22://呼吸灯模式：绿灯渐渐暗停0.3s、渐渐亮停0.7s
				{ 
				 if(led_delay_tick_h%2==0)
				 {
							if(brightness_h_flag==0)brightness_h++;									//渐渐亮
							else brightness_h--;																	//渐渐暗
					 
							send_string_data_H(0,brightness_h,0,0);    
					 
							if(brightness_h>=253){delay_ms(700);brightness_h_flag=1;}//停0.7s切换成渐渐暗
							else if (brightness_h <=0){delay_ms(300);brightness_h_flag=0;}//停0.3s切换成渐渐亮
					}
				 if(led_delay_tick_h>=4)led_delay_tick_h=0;												//时间归零用于循环
		     break;
       	}
			case 0x23://呼吸灯模式：黄灯  
				{
				 if(led_delay_tick_h%2==0)
				 {
							if(brightness_h_flag==0)brightness_h++;									//渐渐亮
							else brightness_h--;																	//渐渐暗
					 
							send_string_data_H(brightness_h,brightness_h,0,0);    
					 
							if(brightness_h>=253){delay_ms(700);brightness_h_flag=1;}//停0.7s切换成渐渐暗
							else if (brightness_h <=0){delay_ms(300);brightness_h_flag=0;}//停0.3s切换成渐渐亮
					}
				 if(led_delay_tick_h>=4)led_delay_tick_h=0;												//时间归零用于循环
		     break;
       	}
			case 0x31://红色闪1次
	   	  {
					flash_and_stay_H( 1, 2, 255, 0, 0, 0); //闪烁次数、暂停时间、 r、g、b、w  
					break;
       	 }
		  case 0x32://红色闪2次
		    {
					flash_and_stay_H( 2, 2, 255, 0, 0, 0); 
			    break;
		    }
		  case 0x33://红色闪3次
	   	  {
					flash_and_stay_H( 3, 2, 255, 0, 0, 0); 
			    break;
       	}
		  case 0x34://红色闪4次
	   	  {
					flash_and_stay_H( 4, 2, 255, 0, 0, 0); 
			    break;
       	}	
		  case 0x35://红色闪5次
	   	  {
					flash_and_stay_H( 5, 2, 255, 0, 0, 0); 
			    break;
       	}
		  case 0x36://红色闪6次
	   	  {
					flash_and_stay_H( 6, 2, 255, 0, 0, 0); 
			    break;
       	}			


			case 0xF0://节能模式
				{
		     send_string_data_H(0,0,0,0);
		     LED1_OFF;
		     break;
       	}
		 default:
        {
			    break;
		    }
    }
}
	
static u8 Stack_left=1;

void led_fly_H(u8 spd,u8 date_cmd)
{
    u32 i,j;

		u8  h1,h2,h3;
		u8 r[LIGHT_LED_NUM_H];
		u8 g[LIGHT_LED_NUM_H];
		u8 b[LIGHT_LED_NUM_H];
		u8 w[LIGHT_LED_NUM_H];
		h1=0;
		h2=1;
	  h3=2;
	
	   for(i=0;i<LIGHT_LED_NUM_H;i++)
	   {
		   j = (i + 7) % LIGHT_LED_NUM_H;

	       switch(date_cmd)
	       {
	       	 case 0x00://白色跑马
						 {
							if(i>=Stack_left)
								{
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
								}
							else
								{			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h3];
									w[j] = Table_W[h1];
								}
							break;
								 }
					 case 0x01: //红色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; //红色
									g[j] = Table_G[h3];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x02: //橙色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; 
									g[j] = Table_G[h2];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x03: //黄色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; 
									g[j] = Table_G[h1];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x04: //绿色跑马
						  {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h1];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x05: //青色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h1]-130;//青色
									b[j] = Table_B[h1];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x06: //蓝色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h1];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }						 
					 case 0x07: //紫色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]-105; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h1]-105;
									w[j] = Table_W[h3];
							  }
						  break;							
						 }						 
			    default:
			     {break;}
	       }
	    }

			if(led_delay_tick_h>=spd)
			{
				led_delay_tick_h=0;
					{
					Stack_left++;
					if(Stack_left>size_h)
						{ 
							Stack_left=0;
						}
					}	
				
			}
	ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
}


  void led_fly(u8 spd,u8 date_cmd)
{
    u32 i,j;
	
		u8  h1,h2,h3;
		u8 r[LIGHT_LED_NUM_H];
		u8 g[LIGHT_LED_NUM_H];
		u8 b[LIGHT_LED_NUM_H];
		u8 w[LIGHT_LED_NUM_H];
		h1=0;
		h2=1;
	  h3=2;
	
	   for(i=0;i<LIGHT_LED_NUM;i++)
	   {
		   j = (i + 7) % LIGHT_LED_NUM;

	       switch(date_cmd)
	       {
	       	 case 0x00://白色跑马
						 {
							if(i>=Stack_left)
								{
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
								}
							else
								{			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h3];
									w[j] = Table_W[h1];
								}
							break;
								 }
					 case 0x01: //红色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; //红色
									g[j] = Table_G[h3];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x02: //橙色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; 
									g[j] = Table_G[h2];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x03: //黄色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]; 
									g[j] = Table_G[h1];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x04: //绿色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h1];
									b[j] = Table_B[h3];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x05: //青色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h1]-130;//青色
									b[j] = Table_B[h1];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
					 case 0x06: //蓝色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h3]; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h1];
									w[j] = Table_W[h3];
							  }
						  break;							
						 }						 
					 case 0x07: //紫色跑马
						 {
							if(i>=Stack_left)
							  {
									r[j] = Table_R[h3];
									g[j] = Table_G[h3];
									b[j] = Table_B[h3]; 
									w[j] = Table_W[h3];
							  }
							else
							  {			
									r[j] = Table_R[h1]-105; 
									g[j] = Table_G[h3];
									b[j] = Table_B[h1]-105;
									w[j] = Table_W[h3];
							  }
						  break;							
						 }
			    default:
			     {break;}
	       }
	    }

			if(led_delay_tick_h>=spd)
			{
				led_delay_tick_h=0;
					{
					Stack_left++;
					if(Stack_left>size_h)
						{ 
							Stack_left=0;
						}
					}	
				
			}
	ws_set_led_rgb(r, g, b, w, LIGHT_LED_NUM );
}


u8 Table_R1[2]={255,0}; 
u8 Table_G1[2]={255,0};
u8 Table_B1[2]={255,0};
u8 Table_W1[2]={255,0};

void led_one(u8 one)
{
    u32 j;
		u8  h1,h2;
		u8  r[LIGHT_LED_NUM_H];
		u8  g[LIGHT_LED_NUM_H];
		u8  b[LIGHT_LED_NUM_H];
		u8  w[LIGHT_LED_NUM_H];
		h1 = 0;
		h2 = 1;
	
	   for(j=0;j<LIGHT_LED_NUM_H;j++)
	   {
				if(j==one)							
					{			
						r[j] = Table_R1[h1];
						g[j] = Table_G1[h2];
						b[j] = Table_B1[h2]; 
						w[j] = Table_W1[h2];
					}
				else
					{			
						r[j] = Table_R1[h2]; 
						g[j] = Table_G1[h2];
						b[j] = Table_B1[h2];
						w[j] = Table_W1[h2];
					}
			}
	   ws_set_led_rgb_H(r, g, b, w, LIGHT_LED_NUM_H);
}
/*flash_times闪烁次数 /次  stay_time 闪烁时间 /秒 */
void flash_and_stay_H(u8 flash_times,u8 stay_time,u8 r,u8 g ,u8 b,u8 w)
{ const u8 flashtime=3; 
		if(led_delay_tick_h<=(flashtime*flash_times*2))
						{
							if((led_delay_tick_h/flashtime)%2==1)
								 {  
									 send_string_data_H(r,g,b,w);			    
								 }
							else if ((led_delay_tick_h/flashtime)%2==0)
								 {
										send_string_data_H(0,0,0,0);
									}
						}
						else send_string_data_H(0,0,0,0);
		     	if(led_delay_tick_h>=(flashtime*flash_times*2+stay_time*10))
						led_delay_tick_h=0;
}
void flash_and_stay(u8 flash_times,u8 stay_time,u8 r,u8 g ,u8 b,u8 w)
{
	const u8 flashtime=3; 
		if(led_delay_tick_h<=(flashtime*flash_times*2))
						{
							if((led_delay_tick_h/flashtime)%2==1)
								 {  
									 send_string_data(r,g,b,w);			    
								 }
							else if ((led_delay_tick_h/flashtime)%2==0)
								 {
										send_string_data(0,0,0,0);
									}
						}
						else send_string_data_H(0,0,0,0);
		     	if(led_delay_tick_h>=(flashtime*flash_times*2+stay_time*10))
						led_delay_tick_h=0;
}

void breathing_blue(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(0,0,brightness_h,0); 			
}

void breathing_color_blue(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * color_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = color_tick;
			color_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - color_tick);
		if(brightness_h <= 0){
			color_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(0,0,brightness_h,0); 			
}

void breathing_red(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,0,0,0); 			
}
void breathing_green(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(0,brightness_h,0,0); 			
}
void breathing_purple(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,0,brightness_h,0); 			
}

void breathing_color_purple(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * color_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = color_tick;
			color_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - color_tick);
		if(brightness_h <= 0){
			color_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,0,brightness_h,0); 			
}

void breathing_orange(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,brightness_h/3,0,0); 			
}

void breathing_color_orange(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 3;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * color_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = color_tick;
			color_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - color_tick);
		if(brightness_h <= 0){
			color_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,brightness_h/3,0,0); 			
}

void breathing_white(u8 per){
	u8 step = 3;
	switch (per)
	{
		case 1: step = 5;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(0,0,0,brightness_h); 			
}

void breathing_yellow(u8 per){
		u8 step = 3;
	switch (per)
	{
		case 1: step = 5;break;
		case 3: step = 2;break;
		case 5: step = 1;break;
		default : step = 3;break;
	}
	 if(brightness_h_flag == 0){
		brightness_h = step * breating_led_tick;
		if(brightness_h > 250){
			
			brightness_h_flag = 1;
			breating_max = breating_led_tick;
			breating_led_tick = 0;
		}
	}else if(brightness_h_flag == 1){
		brightness_h = step*(breating_max - breating_led_tick);
		if(brightness_h <= 0){
			breating_led_tick = 0;
			brightness_h_flag = 0;
			breating_change ++;
		}
	}		
	send_string_data(brightness_h,brightness_h,0,0); 
}


void blink(u8 r, u8 g, u8 b, u8 w, u8 freq){
	if(freq > 10)
		freq = 10;
		if(breating_led_tick < 50/freq)
				send_string_data(r,g,b,w);
		else 
				send_string_data(0,0,0,0);
		if(breating_led_tick >= 100/freq)
			breating_led_tick = 0;
}

void double_blink(u8 r, u8 g, u8 b, u8 w){
	send_string_data(r,g,b,w);
	if(125<=blink_tick<250){								//delay_ms(125);
		send_string_data(0,0,0,0);
	}
	if(250<=blink_tick<375){								//delay_ms(125);
		send_string_data(r,g,b,w);
	}
	if(375<=blink_tick<500){								//delay_ms(125);
		send_string_data(0,0,0,0);
	}
	if(blink_tick>=500){								//delay_ms(125);
		blink_tick=0;
	}
}