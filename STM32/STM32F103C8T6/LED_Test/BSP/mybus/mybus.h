#ifndef    __MYBUS_H
#define    __MYBUS_H


#include "stm32f10x.h"

extern u8  mnflag;

//发送cmd03命令---心跳包
void send_cmd03(void);


//设置数据
void set_data(u8 dat, u8 index);

uint16_t ModbusCRC16_Set(u8* buf, u8 len);
u8 ModbusCRC16_Check(u8* buf, u8 len);
void ModbusCRC16_Insert(u8* buf, u8 len);
void USART1_RecDataProcess(void *pmt);
void PrintDL(void);
void PrintSl(void);
void PrintTempIn(void);
void PrintTempOut(void);
void Task_UPLoad(void);
void Task_UART1_Rec(void);


#endif

