#include "sys.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stdint.h"
#include "ws2812b.h"
#include "stdbool.h"

#define        USART_RX_MAX_LEN  		10 	//�����������ֽ��� 10
#define        USART_TX_MAX_LEN      50          //��������ֽ�

 
//u8 USART1_RX_Data_Len = 0;        //ʵ�ʽ��������ֽڳ���
//u8 USART1_TX_Data_Len = 0;        //�����������ֽڳ���
//u8 USART1_RX_Flag = 0;            //����1�Ƿ����������
 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
	
//void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* Ƕ�������жϿ�������ѡ�� */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* �������ȼ�*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//  /* �����ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //??D��DT??��?��?
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	   	//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   //?��??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			   //������??��???a0
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
	
	
	//GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//ʹ��USART1,GPIOA,Cʱ��

	
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX      GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10

    //Usart1 NVIC ����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�   0-3;

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3 ;    //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);    //����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������

    USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1
	
	
}

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	

u32 ex_cmd;
u32 cmd;

u8 USART1_RX_BUF[5]; 
u8 USART1_RX_CNT=0;
int flag = 0;
void USART1_IRQHandler(void)                    //����1�жϷ������
{
    u8 Res;
static	u8 data_head = 0;
	int i = 0;
	u8 crc = 0;
	u8 RxDate;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
        {
            Res =USART_ReceiveData(USART1);    //��ȡ���յ�������
						cmd = Res;
//						if(Res == 0X0A){
//							data_head = 1;
//						}
//						if(data_head == 1){
//							if(USART1_RX_CNT < 5){											 //���ڽ���ָ�����ȵ��ַ���
//                USART1_RX_BUF[USART1_RX_CNT++]=Res;        //��¼���յ���ֵ
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
//								USART_ClearITPendingBit(USART1,USART_IT_RXNE);      /*��������жϱ�־*/
//								RxDate =USART_ReceiveData (USART1);
//			   
//								USART_SendData(USART1,RxDate);
//								cmd = RxDate;
//						}

     }
         //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ����������������жϵ�����
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET)
    {
        USART_ReceiveData(USART1);
        USART_ClearFlag(USART1,USART_FLAG_ORE);
    }
     USART_ClearFlag(USART1,USART_IT_RXNE); //һ��Ҫ��������ж�
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //��������ģʽ	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = 9600;						//����9600bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ
	/* Configure USART2 */
	USART_Init(USART2, &USART_InitStructure);							//���ô��ڲ�������
	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                    //ʹ�ܽ����ж�
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //????��?��??�꨺?	   
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //?��
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	   	// 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//
	USART_InitStructure.USART_Parity = USART_Parity_No;				//?TD��?��??
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
			 //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ����������������жϵ�����
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET){
			USART_ReceiveData(USART2);
			USART_ClearFlag(USART2,USART_FLAG_ORE);
	}
	 USART_ClearFlag(USART2,USART_IT_RXNE); //һ��Ҫ��������ж�	
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
			 //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ����������������жϵ�����
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE) == SET){
			USART_ReceiveData(USART3);
			USART_ClearFlag(USART3,USART_FLAG_ORE);
	}
	 USART_ClearFlag(USART3,USART_IT_RXNE); //һ��Ҫ��������ж�	
}




/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
//		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


