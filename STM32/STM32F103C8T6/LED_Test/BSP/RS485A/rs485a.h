#ifndef __RS485A_H
#define __RS485A_H			 
#include "sys.h"	

/////////////////////////////////////////////////// 
//DBSB_485控制板   
//修改日期:2024/05/31
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 贝斯源科技有限公司 2024-2034
///////////////////////////////////////////////////
	  		  	
extern u8 RS485A_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 RS485A_RX_CNT;   			//接收到的数据长度

//模式控制
#define RS485A_TX_EN		PBout(1)	//485A模式控制.0,接收;1,发送.
//如果想串口中断接收，请不要注释以下宏定义
#define EN_USART3_RX 	1			//0,不接收;1,接收.




void RS485A_Init(u32 bound);
void RS485A_Send_Data(u8 *buf,u8 len);
void RS485A_Receive_Data(u8 *buf,u8 *len);


#endif	   
















