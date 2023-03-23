#include "sys.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stdint.h"
#include "ws2812b.h"
#include "stdbool.h"

#define        USART_RX_MAX_LEN  		10 	//定义最大接收字节数 10
#define        USART_TX_MAX_LEN      50          //发送最大字节

 
//u8 USART1_RX_Data_Len = 0;        //实际接收数据字节长度
//u8 USART1_TX_Data_Len = 0;        //待发送数据字节长度
//u8 USART1_RX_Flag = 0;            //串口1是否接收完数据
 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
	
//void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* 嵌套向量中断控制器组选择 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* 配置USART为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* 抢断优先级*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//  /* 子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //??DèDT??ò?′?
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	   	//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //?à??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			   //×óó??è???a0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	   	// 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	

}

		
	
void USART_Config(void)
{
	
	
	//GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//使能USART1,GPIOA,C时钟

	
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    //USART1_RX      GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10

    //Usart1 NVIC 配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级   0-3;

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3 ;    //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);    //根据指定的参数初始化VIC寄存器

   //USART 初始化设置

    USART_InitStructure.USART_BaudRate = 115200;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1
	
	
}

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	

u32 ex_cmd;
u32 cmd;

u8 USART1_RX_BUF[5]; 
u8 USART1_RX_CNT=0;
int flag = 0;
void USART1_IRQHandler(void)                    //串口1中断服务程序
{
    u8 Res;
static	u8 data_head = 0;
	int i = 0;
	u8 crc = 0;
	u8 RxDate;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
        {
            Res =USART_ReceiveData(USART1);    //读取接收到的数据
						cmd = Res;
//						if(Res == 0X0A){
//							data_head = 1;
//						}
//						if(data_head == 1){
//							if(USART1_RX_CNT < 5){											 //对于接收指定长度的字符串
//                USART1_RX_BUF[USART1_RX_CNT++]=Res;        //记录接收到的值
//							}
//							if(USART1_RX_CNT >= 5) {
//								data_head = 0;
//								
//								send_string_data(USART1_RX_BUF[1],USART1_RX_BUF[2],USART1_RX_BUF[3],USART1_RX_BUF[4]);
//								USART1_RX_CNT = 0;
////								for(i = 0; i < 4; i++){
////									crc += USART1_RX_BUF[i];
////								}
////								if(crc == USART1_RX_BUF[4])
////									cmd = USART1_RX_BUF[3];
////								USART1_RX_CNT = 0;
//							}
//						}	
//						else
//							{
//								USART_ClearITPendingBit(USART1,USART_IT_RXNE);      /*清楚接收中断标志*/
//								RxDate =USART_ReceiveData (USART1);
//			   
//								USART_SendData(USART1,RxDate);
//								cmd = RxDate;
//						}

     }
         //溢出-如果发生溢出需要先读SR,再读DR寄存器则可清除不断入中断的问题
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET)
    {
        USART_ReceiveData(USART1);
        USART_ClearFlag(USART1,USART_FLAG_ORE);
    }
     USART_ClearFlag(USART1,USART_IT_RXNE); //一定要清除接收中断
}


void USART2_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure USART2 Rx (PA.3) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //浮空输入模式	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = 9600;						//速率9600bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
	/* Configure USART2 */
	USART_Init(USART2, &USART_InitStructure);							//配置串口参数函数
	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                    //使能接收中断
	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);	            
}

void USART3_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //????ê?è??￡ê?	   
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //?′
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	   	// 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//
	USART_InitStructure.USART_Parity = USART_Parity_No;				//?TD￡?é??
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//
	/* Configure USART3 */
	USART_Init(USART3, &USART_InitStructure);							//
	/* Enable USART3 Receive and Transmit interrupts */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                    //
	//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//
	/* Enable the USART3 */
	USART_Cmd(USART3, ENABLE);	                  //
}


char uart2_buf[4];
int dis_uart2 = 0;
int data_head2;
u8 usart2_flag;

void USART2_IRQHandler (void)
{
	char res2;
	int i = 0;
	static int count = 0;
	static char check_sum = 0;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
			res2=USART_ReceiveData(USART2);  
			if(res2 == 0xff){
				data_head2 = 1;
				check_sum = 0;
			}
			if(data_head2 == 1){
				uart2_buf[count++] = res2;
			}
			if(count == 4){
				count = 0;
				data_head2 = 0;
			
				for(i = 0; i < 3; i++){
					check_sum += uart2_buf[i];
				}
				if(check_sum == uart2_buf[3]){
					dis_uart2 = uart2_buf[1]*256 +  uart2_buf[2];
					usart2_flag=1;
				}
			}
	 }
			 //溢出-如果发生溢出需要先读SR,再读DR寄存器则可清除不断入中断的问题
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET){
			USART_ReceiveData(USART2);
			USART_ClearFlag(USART2,USART_FLAG_ORE);
	}
	 USART_ClearFlag(USART2,USART_IT_RXNE); //一定要清除接收中断	
}


char uart3_buf[4];
int dis_uart3 = 0;
int data_head3=0;
u8 usart3_flag;

void USART3_IRQHandler (void)
{
	char res3;
	int i = 0;
	static int count = 0;	
	static char check_sum = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
			res3=USART_ReceiveData(USART3);  
			if(res3 == 0xff){
				data_head3 = 1;
				check_sum = 0;
//				usart3_flag=0;
			}
			if(data_head3 == 1){
				uart3_buf[count++] = res3;
			}
			if(count == 4){
				count = 0;
				data_head3 = 0;
			
				for(i = 0; i < 3; i++){
					check_sum += uart3_buf[i];
				}
				if(check_sum == uart3_buf[3]){
					dis_uart3 = uart3_buf[1]*256 +  uart3_buf[2];
					usart3_flag=1;
				}
			}
	 }
			 //溢出-如果发生溢出需要先读SR,再读DR寄存器则可清除不断入中断的问题
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE) == SET){
			USART_ReceiveData(USART3);
			USART_ClearFlag(USART3,USART_FLAG_ORE);
	}
	 USART_ClearFlag(USART3,USART_IT_RXNE); //一定要清除接收中断	
}




/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
//		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


