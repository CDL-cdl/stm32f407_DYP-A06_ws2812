#ifndef __RS485_H
#define __RS485_H
#include"sys.h"
#include "delay.h"
#include "led.h" 
#include "usart.h"
#include "serial_protocol_manage.h"
#include "crc16.h"

//模式控制
#define RS485_TX_EN()		PAout(1)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，请不要注释以下宏定义.

extern u8 ledringbuf[7];
extern void RS485_Init(u32 bound);
extern void RS485_Send_Data(u8 *buf,u8 len);
extern void RS485_Receive_Data(u8 *buf,u8 *len);
extern void serial_protocol_usart2_init(void);

#endif
