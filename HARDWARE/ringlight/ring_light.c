#include"ring_light.h"
#define START_N1   0x4E    //'N'
#define START_J1   0x4A    //'J'

ring_light_frame led_ring={0};/*赋缺省值*/

void send_data_crc(u8 *buf)
{
     u16 crc_value;
     crc_value=CRC16(buf,4);
	 buf[4]= crc_value&0xff;
	 buf[5]= (crc_value>>8)&0xff;
	 RS485_Send_Data(buf,6);  
}
u8 right_data_circl=0;
void right_light_recieve()
{
   u16 	 crc_value;
   u16  data_crc_value=0;
   u8 dat_buf[7],i,TX_buf[8];

   if(ledringbuf[0]==0x68)	 //有数据了
   {  
	   for(i=0;i<7;i++)
	   {
		   dat_buf[i]=ledringbuf[i];
	   }
	   ledringbuf[0]=0x00;
      
      if(dat_buf[3]==light_ID)
	  {
	      crc_value=CRC16(&dat_buf[1],4);
	      data_crc_value= (u16)(dat_buf[6])<<8 | (u16) (dat_buf[5]);
		  //printf("crc:%d,  data_crc:%d\r\n",crc_value,data_crc_value);
	      if(data_crc_value==crc_value)
	      {
			  TX_buf[0]=0x4E;
              TX_buf[1]=0x4A;
              TX_buf[2]=0x00;/*主机地址为0x00*/
	          TX_buf[3]=light_ID;
	          send_data_crc(TX_buf);  /*发送回复字*/
			  right_data_circl=(dat_buf[4] & 0x0f);
	       }
		   else
		   {
		   }
	  }
   }
}


