//#include "dma1_ch2.h"

//#define TIM3_CCR3_Address    0x4000043C  //TIM3_CH3�ĵ�ַ
//#define TIM1_CCR3_Address    0x40000840

//void dma1_ch3_init(u16 *buf,u16 length)
//{
//   DMA_InitTypeDef DMA_InitStructure;
//   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//ʹ�� DMA ʱ��
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//���ܸ��� IO ʱ��

//   TIM_Cmd(TIM4, DISABLE);
//   DMA_Cmd(DMA1_Channel7, DISABLE);
//   DMA_DeInit(DMA1_Channel7);//�� DMA ��ͨ�� 4 �Ĵ�������Ϊȱʡֵ
//   
//   DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)TIM3_CCR3_Address;//DMA ���� ADC ����ַ
//   DMA_InitStructure.DMA_MemoryBaseAddr=(u32)buf; //DMA �ڴ����ַ
//   DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//������Ϊ���ݴ����Ŀ�ĵ�
//   DMA_InitStructure.DMA_BufferSize=length;// //DMA ͨ���� DMA ����Ĵ�С
//   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
//   DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
//   DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//���ݿ�Ϊ 16 λ
//   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
//   DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//������ѭ������ģʽ
//   DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMA ͨ�� x ӵ�и����ȼ�
//   DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
//   DMA_Init(DMA1_Channel7,&DMA_InitStructure);

//   DMA_ClearFlag(DMA1_FLAG_TC7);
//   DMA_Cmd(DMA1_Channel7, ENABLE);
//   TIM_Cmd(TIM4, ENABLE);

//   /* wait send end */
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC7) == RESET);
//}
