#ifndef __RING_LIGHT_H
#define __RING_LIGHT_H
#include "sys.h"
#include "crc16.h"
#include "RS485.h"
#include "ws2812b.h"

#define light_ID   0x01	/*����0x02,����0x01*/

typedef union
{
   u8   all;
   struct 
   {
      u8 crash_error_flag:1; //��ײ���߹��Ϸ���
      u8 battery_empty_flag:1;/*��ص����ͱ�־λ*/
	  u8 battery_charging:1; /*��س����*/
	  u8 agv_motion_status:1;/*С���˶�״̬ 1 ��ʾ�˶��� 0��ʾ��ֹ*/
      u8 reserved:2;
	  u8 left_right_led_ctl:1;/*���ε����ҿ���λ 1 ��ʾ������� 0 ��ʾ�����ұ�*/
      u8 led_status_valid:1;
   }bit;
}LED_CMD_UNION;

typedef struct
{
   u8 packet_head1;//����ʼ��
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
