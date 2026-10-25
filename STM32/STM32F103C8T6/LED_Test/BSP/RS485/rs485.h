#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	

/////////////////////////////////////////////////// 
//DBSB_485控制板   
//修改日期:2024/05/31
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 贝斯源科技有限公司 2024-2034
///////////////////////////////////////////////////
	  		  	
extern u8 RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 RS485_RX_CNT;   			//接收到的数据长度

//模式控制
#define RS485_TX_EN		PAout(4)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，请不要注释以下宏定义
//#define EN_USART2_RX 	0			//0,不接收;1,接收.




void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf,u8 *len);


#endif	   
















