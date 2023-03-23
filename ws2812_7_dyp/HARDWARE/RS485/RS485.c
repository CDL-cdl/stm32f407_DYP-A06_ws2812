#include "RS485.h"	 

/******************************queue*******************************/
#define queue_rec_size    512 //ע�ⲻҪΪ1*512,�������ݲ���
#define rec_buf_size      80
static  u8  queue_rec[queue_rec_size]={0};
										
static int g_iReadPos  = 0;
static int g_iWritePos = 0;

static int isFull(void)
{
    return (((g_iWritePos + 1) % queue_rec_size) == g_iReadPos);
}
static int isEmpty(void)
{
   return (g_iWritePos == g_iReadPos);
}
static int PutData(u8 cVal)
{
   if(isFull())
   	  return -1;
   else
   {
      queue_rec[g_iWritePos]= cVal;
	  g_iWritePos =(g_iWritePos+1) % queue_rec_size;
      return 0;
   }
}
static int GetData(u8 *pcVal)
{
   if (isEmpty())
		return -1;
   else
   {
      *pcVal = queue_rec[g_iReadPos];
	  g_iReadPos = (g_iReadPos + 1) % queue_rec_size;
	  return 0;
   }
}
/*********************************************************************/		  
static u8 recieve_start=0x00;
static u8 recieve_buf[40];
static u8 recieve_num=0;
void USART2_IRQHandler(void)
{
  	u8 temp=0;
	s16 i;  
//	u8 buf[40];  
//	OLD_Frame frame_senda;                       
 	 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
	{	 
	 			 
		temp=USART_ReceiveData(USART2);//;��ȡ���յ�������USART2->DR
	     	if( (recieve_start&0x0f) ==0x0a)//�Ѿ��յ������ַ�
		    {
				  if(recieve_start==0x2a)//��ȷУ�������ַ��ͳ���
				  {
				       recieve_buf[++recieve_num]=temp;
					    if(recieve_num>=4)
					   {	//USART2_Send_Byte(recieve_buf[4]);
					       	 if(recieve_num==recieve_buf[4]-1)
						     {
						         for(i=0;i<recieve_buf[4];i++)
						         {
						            PutData(recieve_buf[i]);
									//USART2_Send_Byte(queue_rec[i]);
						         }
								 //old_frame_send_inital(&frame_senda,recieve_buf,recieve_buf[4],0x01,0xA5);
					          	 recieve_num=0;
					        	 recieve_start&=0x00;
						     }      
					   }	    
				 }
				 else
			     {
				    recieve_buf[++recieve_num]=temp;
				    if(recieve_num==1)
				    {
				        if(recieve_buf[0]==0x4E && recieve_buf[1]==0x4A)
				        {
				            
				             recieve_start|=0x20;//��ȷУ�������ַ��ͳ���
						//	 buf[0]=recieve_buf[0];
						 //    buf[1]=recieve_buf[1];
						//	 buf[2]=recieve_start;
						//	RS485_2_Send_Data(buf,3);
						     // printf("%02X\r\n",recieve_start);
							 // for(i=0;i<4;i++)printf("%02X ",recieve_buf[i]);printf("\r\n");

				        }
				    	else
					    {
					         recieve_start&=0x00;
						     recieve_num=0;
	
					    }
				    }
				}
			
		 }
	     else
		 {
		       if(temp==0x4E)//�յ������ַ�
		       {
		           recieve_start=0x0a;
			       recieve_buf[recieve_num]=temp;
				  // buf[0]= recieve_buf[recieve_num];
				 //  buf[1]= recieve_start;
			      //RS485_2_Send_Data(buf,2);
		       }

		 }	
   	}							

}						 
//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void RS485_Init(u32 bound)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,Gʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PA1�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ
 
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

    RS485_TX_EN()=0;			//Ĭ��Ϊ����ģʽ
 
}

//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN()=1;			//����Ϊ����ģʽ
	//USART_ClearFlag(USART2,USART_FLAG_TC); 
  	for(t=0;t<len;t++)		//ѭ����������
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	//ע������ġ�;��  
		USART_SendData(USART2,buf[t]);
	}	 
 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	//ע������ġ�;��  	 
	RS485_TX_EN()=0;				//����Ϊ����ģʽ	
}
/******************************protocol****************************************/
static void old_frame_send(OLD_Frame *frame)
{
    u8 buf[40];
	u16 i;
    buf[0]=frame->start_char_one;
    buf[1]=frame->start_char_second;
    buf[2]=frame->address;
    buf[3]=frame->command_code;
    buf[4]=frame->data_length;
    for(i=0;i<frame->data_length-7;i++)
	{
	    buf[5+i]=frame->data[i];
	}
	buf[frame->data_length-2]=frame->CRC_HI;
	buf[frame->data_length-1]=frame->CRC_LO;
	RS485_Send_Data(buf,frame->data_length);
//	for(i=0;i<frame->data_length;i++)
//	{
//	    USART2_Send_Byte(buf[i]);
//	}
}
/*
 * length:data����
 *
 */
static void old_frame_send_inital(OLD_Frame *frame,u8 *data,u8 length,u8 control_code,u8 address_code)
{
   u8  i,buf[40];
   u16 crc;
   frame->start_char_one=0x4E;
   frame->start_char_second=0x4A;
   frame->address=address_code;
   frame->command_code=control_code;
   frame->data_length=length+7;
   for(i=0;i<length;i++)
   {
      frame->data[i]=data[i];
   }
   buf[0]=0x4E;
   buf[1]=0x4A;
   buf[2]=address_code;
   buf[3]=control_code;
   buf[4]=length+7;
   for(i=0;i<length;i++)
   {
      buf[i+5]=data[i];
   }
   crc=CRC16(buf,length+5);
   frame->CRC_LO=(u8)crc & 0xff;
   frame->CRC_HI=(u16)crc>>8 & 0xff;
   //RS485_Send_Data(buf,frame->data_length+7);
   //��frame���ͳ�ȥ
   old_frame_send(frame);
} 
/*
 * data�����յ���һ֡����
 * length :֡���ݳ���
 *
 */
static u8 old_freame_receive_assignment(OLD_Frame *frame,u8 *data,u8 length)
{  
    u16 crc_recieve,crc_self,i;
	crc_recieve=(u16)((data[length-2]<<8)&0xff00) + (data[length-1]&0xff);
	crc_self=CRC16(data,length-2); //CRC�������crc����λǰ�������
	if(crc_recieve==crc_self)
	{	 
	   frame->start_char_one=data[0];
       frame->start_char_second=data[1];
       frame->address=data[2];
       frame->command_code=data[3];
       frame->data_length=data[4];
	   for(i=0;i<frame->data_length-7;i++)
	   {
	      frame->data[i]=data[i+5];
	   } 
	   frame->CRC_LO=data[length-1]&0xff; 
	   frame->CRC_HI=(data[length-2])&0xff;
	  // old_frame_send(frame);  
       return  1;//��ȷ����
    }
	else
	{
	   
	   return  0;//CRCУ��ʧ��
	}
}
static void old_frame_receive(OLD_Frame *frame)
{
   u8 data;
   u8 found_resource=0;
   u8 buf[rec_buf_size];
   u32 num=0;
   	
   while(GetData(&data)==0)
   {  
      // USART2_Send_Byte(data);
	  if(found_resource==0)
	  { 
	     buf[num++]=data;
		 
	     if(num>=2)
	     {
	       if( (buf[0])==0x4E && (buf[1]==0x4A) )
	       	{
	       	   	 //USART2_Send_Byte(0x88);
	       	}	  
		    else
		    {
		       num = 0;
		    }
	     }
	     if(num >= 6)
	     { 
	        found_resource=1;
	     } 
	  }
	  else if(found_resource==1)
	  {
	      if(num<buf[4])/*buf[4]:����*/
	      {
	         buf[num++]=data;/*��ȡ���ݳɹ�*/
	      }
		  if(num==buf[4])
		  {
		      //serial_protocol_usart2.send_frame_data(&frame_senda,buf,num,0x01,0xA5);
		      old_freame_receive_assignment(frame,buf,num);/*��ȥ����*/
		       break;
		  }
	  }
	  IWDG_Feed();
   }
}
/***************************************************************************/
void  serial_protocol_usart2_init(void)
{
   serial_protocol_usart2.send_frame_data   = old_frame_send_inital;
   serial_protocol_usart2.old_frame_receive = old_frame_receive;
   serial_protocol_usart2.frame_handle_data = frame_handle_data_usart2;	
}




















