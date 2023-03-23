#include "dma1_ch_init.h"

#define TIM4_CCR3_Address    0x4000043C  //TIM4_CH3的地址  PB0
#define TIM4_CCR3_Address    0x4000083C   //TIM4_CH3的地址  PB8
//#define TIM4_CCR3_Address    0x40000840   //TIM4_CH4的地址  PB9


void dma1_ch7_init(u16 *buf,u16 length)
{
   DMA_InitTypeDef DMA_InitStructure;
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能 DMA 时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//功能复用 IO 时钟

   TIM_Cmd(TIM4, DISABLE);
   DMA_Cmd(DMA1_Channel4, DISABLE);
   DMA_DeInit(DMA1_Channel4);//将 DMA 的通道 7 寄存器重设为缺省值
   
   DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&(TIM4->CCR2);//DMA 外设 ADC 基地址
   DMA_InitStructure.DMA_MemoryBaseAddr=(u32)buf; //DMA 内存基地址
   DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
   DMA_InitStructure.DMA_BufferSize=length;// //DMA 通道的 DMA 缓存的大小
   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址寄存器不变
   DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//内存地址寄存器递增
   DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//数据宽为 16 位
   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//数据宽度为16位
   DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//工作在循环缓存模式
   DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMA 通道 x 拥有高优先级
   DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
   
	 DMA_Init(DMA1_Channel4,&DMA_InitStructure);

   DMA_ClearFlag(DMA1_FLAG_TC4);
   DMA_Cmd(DMA1_Channel4, ENABLE);
   TIM_Cmd(TIM4, ENABLE);

   /* wait send end */
	while(DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET);
}

void dma1_ch3_init(u16 *buf,u16 length)
{
   DMA_InitTypeDef DMA_InitStructure;
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能 DMA 时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//功能复用 IO 时钟

   TIM_Cmd(TIM4, DISABLE);
   DMA_Cmd(DMA1_Channel1, DISABLE);
   DMA_DeInit(DMA1_Channel1);//将 DMA 的通道 3 寄存器重设为缺省值
   
   DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&(TIM4->CCR1);//DMA 外设 ADC 基地址
   DMA_InitStructure.DMA_MemoryBaseAddr=(u32)buf; //DMA 内存基地址
   DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
   DMA_InitStructure.DMA_BufferSize=length;// //DMA 通道的 DMA 缓存的大小
   DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设地址寄存器不变
   DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//内存地址寄存器递增
   DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//数据宽为 16 位
   DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//数据宽度为16位
   DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//工作在循环缓存模式
   DMA_InitStructure.DMA_Priority=DMA_Priority_High;//DMA 通道 x 拥有高优先级
   DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
   DMA_Init(DMA1_Channel1,&DMA_InitStructure);

   DMA_ClearFlag(DMA1_FLAG_TC1);
   DMA_Cmd(DMA1_Channel1, ENABLE);
   TIM_Cmd(TIM4, ENABLE);

   /* wait send end */
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
}

