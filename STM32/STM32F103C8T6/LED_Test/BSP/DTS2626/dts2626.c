#include "dts2626.h"
#include "rs485a.h"
#include "mybus.h"
#include "stdio.h"
#include "bsy_os.h"

#define  LEN  9
#define  THREAD0   0


//电表的地址全部改为 0x1f
u8  dlBuf[] = {0x1F, 0x03, 0x00, 0x1D, 0x00, 0x02, 0x57, 0xB3};
u8  dlRec[9];
u8  len = 0;

u8 addr = 0x1f;


//读取电表电量数据
void  ReadDl(void *pmt)
{
    pmt = pmt;
    dlBuf[0] = addr;                //初始化电表地址
    RS485A_Send_Data(dlBuf, 8);     //发送数据进行读操作
    //printf("read DL value is send\n");
    delay_ms(100);                  //延时函数,此处因为任务较轻，采用阻塞延时
    //Task_Dalay_ms                 //非阻塞延时
    DLRecProcess();
}


//运行任务结构体定义
RUN_Handle_Type DL_Task_Handle;

//读取电量任务
void Task_ReadDl(void )
{
    DL_Task_Handle.R_CYCLE = 5000;      //2000ms读一次数据
    DL_Task_Handle.NMS = 5000;          //装载延时计数值
    DL_Task_Handle.R_STATUS = STOP;     //设置状态为停止态
    DL_Task_Handle.LEVEL = THREAD0;     //设置该任务优先级为0或称线程0，不能重复，数值越低优先级越高，最大值255
                                        //并且线程从0 1 2 3 4 5 .....连续排列,最后根据线程数量设置线程数量(MAX_TASK)的值。
    DL_Task_Handle.LOCK = false;        //0任务锁打开，可以执行该任务
    DL_Task_Handle.pf = ReadDl;         //任务回调函数
    Task_Add(&DL_Task_Handle);          //创建任务
}





void DLRecProcess(void)
{
	u8 i = 0;
	len = 0;
	RS485A_Receive_Data(dlRec, &len);  //接收返回数据
	if(len == 9){
		
		if( ModbusCRC16_Check(dlRec, 9)){
        
			for(i = 0; i < 4; i++){
				set_data(dlRec[i + 3], i + 3);      //写入数据到电量数据段
			}
        
		}
    }else if(len == 8){
        if(dlRec[0] == 0x1f){
            if(dlRec[3] == 0x61 && dlRec[5] == 0x01){
                printf("Modify Success!");      //修改成功
            }else{
                printf("Modify Failed!");       //修改失败
            }
        }
    }
    
    if(mnflag == 1){
        set_data(0x00, 3);      //写入数据到电量数据段
        set_data(0x0d, 4);      //写入数据到电量数据段
        set_data(0x80, 5);      //写入数据到电量数据段
        set_data(0x52, 6);      //写入数据到电量数据段
    }
    
}


void  ModifyAddr(u8 oldAddr, u8 newAddr)
{
    u8 buf[] = {0x03, 0x10, 0x00, 0x61, 0x00, 0x01, 0x02, 0x00, 0x1F, 0xF6, 0x89};
    buf[0] = oldAddr;           //原地址
    buf[8] = newAddr;           //新地址
    
    ModbusCRC16_Insert(buf, 11);     //计算CRC16,并插入结果
    
    RS485A_Send_Data(buf, 11);     //发送数据进行读操作
   
}

