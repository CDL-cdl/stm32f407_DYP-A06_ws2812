#ifndef __RING_LIGHT_H
#define __RING_LIGHT_H
#include "sys.h"
#include "crc16.h"
#include "RS485.h"
#include "ws2812b.h"

#define light_ID   0x01	/*左是0x02,右是0x01*/

typedef union
{
   u8   all;
   struct 
   {
      u8 crash_error_flag:1; //碰撞或者故障发生
      u8 battery_empty_flag:1;/*电池电量低标志位*/
	  u8 battery_charging:1; /*电池充电中*/
	  u8 agv_motion_status:1;/*小车运动状态 1 表示运动中 0表示静止*/
      u8 reserved:2;
	  u8 left_right_led_ctl:1;/*环形灯左右控制位 1 表示控制左边 0 表示控制右边*/
      u8 led_status_valid:1;
   }bit;
}LED_CMD_UNION;

typedef struct
{
   u8 packet_head1;//包起始符
   u8 packet_head2;
   LED_CMD_UNION led_cmd;
   u8 crc_l;
   u8 crc_h;
}ring_light_frame;

extern u8 right_data_circl;
extern ring_light_frame led_ring;
extern void ring_light_frame_send(ring_light_frame *led_frame);
extern void right_light_recieve(void);
extern void send_data_crc(u8 *buf);

#endif
