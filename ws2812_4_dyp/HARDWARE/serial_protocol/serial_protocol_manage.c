#include "serial_protocol_manage.h"
u8 usart1_buf[40]; 
u8 g_start = 0;
u8 mutex_lock=0;

serial_protocol serial_protocol_usart2;
serial_protocol serial_protocol_usart3;
led_contr led_control={0};	
T_task task1={0};
T_task task2={0};
T_task task3={0};


void serial_protocol_management_init(void)
{
	serial_protocol_usart2_init();
}
/********************************usart2******************************/
void frame_handle_data_usart2(OLD_Frame *frame)
{
			
}
/*****************************usart2**********************************/
