#include "njsmsb.h"
#include "rs485a.h"
#include "mybus.h"
//#include "SysTick.h"
#include "bsy_os.h"

#define THREAD1      1


//水表默认地址 0x01
u8  sbBuf[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09};
u8  sbRec[24];
u8  lens = 0;
u8 addrs = 0x01;

//读取水量
void  ReadSl(void *pmt)
{
    pmt = pmt;
    sbBuf[0] = addrs;                //设置地址，默认0x01
    
    RS485A_Send_Data(sbBuf, 8);     //发送水表读取数据命令
    delay_ms(100);                  //延时函数,此处因为任务较轻，采用阻塞延时
    //Task_Dalay_ms                 //非阻塞延时
    SLRecProcess();
}

RUN_Handle_Type SL_Task_Handle;


void Task_ReadSl(void)
{
    SL_Task_Handle.R_CYCLE = 5000;      //2000ms读一次数据
    SL_Task_Handle.NMS = 5000;          //装载延时计数值
    SL_Task_Handle.R_STATUS = STOP;     //设置状态为停止态
    SL_Task_Handle.LEVEL = THREAD1;           //设置该任务优先级为1
    SL_Task_Handle.LOCK = false;        //0任务锁打开，可以执行该任务
    SL_Task_Handle.pf = ReadSl;         //任务回调函数
    Task_Add(&SL_Task_Handle);    
}



void SLRecProcess(void)
{
	u8 i = 0;
	lens = 0;
	RS485A_Receive_Data(sbRec, &lens);  //接收返回数据
	if(lens == 13){
		RS485A_Send_Data(sbRec, 13);     //发送数据进行读操作
		if( ModbusCRC16_Check(sbRec, 13)){
        
			for(i = 0; i < 4; i++){
				set_data(sbRec[i + 3], i + 7);      //写入数据到水量数据段
			}
        
		}
    }
    
    if(mnflag == 1){
        set_data(0x12, 7);      //写入数据到水量数据段
        set_data(0x34, 8);      //写入数据到水量数据段
        set_data(0x56, 9);      //写入数据到水量数据段
        set_data(0x78, 10);      //写入数据到水量数据段
    }
}


u8  ModifySbAddr(u8 oldAddr, u8 newAddr)
{
    u8 len;
    u8 recBuf[24];
    u8 buf[] = {0x03, 0x10, 0x00, 0x61, 0x00, 0x01, 0x02, 0x00, 0x1F, 0xF6, 0x89};
    buf[0] = oldAddr;           //旧地址
    buf[8] = newAddr;           //新地址
    
    ModbusCRC16_Insert(buf, 11);     //计算CRC16，并插入结果
   
    RS485A_Send_Data(buf, 11);          //发送地址修改指令
    delay_ms(5);
    RS485A_Receive_Data(recBuf, &len);  //接收数据
    
    if(ModbusCRC16_Check(recBuf, len) && len == 8){
        return 1;
    }else{
        return 0;
    }
}



