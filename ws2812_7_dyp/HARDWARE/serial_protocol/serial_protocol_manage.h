#ifndef __SERIAL_PROTOCOL_MANAGE_H
#define __SERIAL_PROTOCOL_MANAGE_H
#include "includes.h"
#include "RS485.h"

typedef struct
{
    u8 start_char_one;
	u8 start_char_second;
	u8 address;
	u8 command_code;
	u8 data_length;
	u8 data[40];  //User_data	最大40个字节
	u8 CRC_HI;
	u8 CRC_LO;
}OLD_Frame;

typedef struct protocol{
	  void (*send_frame_data)(OLD_Frame *frame,u8 *data,u8 length,u8 control_code,u8 address_code);
	  void (*old_frame_receive)(OLD_Frame *frame);
	  void (*frame_handle_data)(OLD_Frame *frame);
	  u8 (*board_send_message)(OLD_Frame *frame,u8 *data,u8 length,u8 control_code,u8 address_code);
}serial_protocol;

typedef struct
{
   u8 open_led;
}led_contr;

typedef struct	task
{
	  u8 task_ID;
	  u8 before_check;
	  u8 getpriority;
	  u8 timer_trigger;
	  u32 timer_count;
}T_task;
extern T_task task1;
extern T_task task2;
extern T_task task3;
extern u8 mutex_lock;
extern u8 usart1_buf[40];
extern u8 g_start;

extern led_contr led_control;
extern serial_protocol serial_protocol_usart2;
extern serial_protocol serial_protocol_usart3;

extern void serial_protocol_management_init(void);
extern void frame_handle_data_usart2(OLD_Frame *frame);
extern void frame_handle_data_usart3(OLD_Frame *frame);

#endif
