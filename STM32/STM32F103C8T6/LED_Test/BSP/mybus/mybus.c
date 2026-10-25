#include "mybus.h"
#include "usart.h"
#include "rs485.h"
#include "dts2626.h"
#include <stdio.h>
#include "bsy_os.h"

#define   THREAD4    4
#define   THREAD3    3

/*****************向Android板发送数据协议**********************
*  byte0:       0x06    485地址       
*  byte1:       0x03    命令码
*  byte2:       0x10    数据长度
*----------------------------------------------
*  电表数据段， 两位小数点
*  byte3:       
*  byte4:
*  byte5:
*  byte6:
*----------------------------------------------
*  水表数据段， 四位小数点
*  byte7:
*  byte8:
*  byte9:
*  byte10:
*----------------------------------------------
*  舱内温度数据段， 一位小数点
*  byte11:
*  byte12:
*----------------------------------------------
*  环境温度数据段， 一位小数点
*  byte13:
*  byte14:
*----------------------------------------------
*  预留数据段
*  byte15:
*  byte16:
*  byte17:
*  byte18:
*  --------------------------------------------
*  byte19  		  CRC_L      校验值低位
*  byte20  		  CRC_H      校验值高位
******************************************************************/

//03命令码	长度 21 byte  每10秒发送一次
u8  cmd03[21]={ 0x06,0x03,0x10,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00};

u8  mnflag = 0;
                
//发送cmd03命令数据到安卓板
void send_cmd03(void)
{
	u16 val = ModbusCRC16_Set(cmd03, 19);
	cmd03[19] = val & 0x00ff;
	cmd03[20] = (val>> 8) & 0x00ff;
    RS485_Send_Data(cmd03, 21);
}


void UPLoad_Data(void *pmt)
{
    pmt = pmt;
    send_cmd03();       //上传数据
    
    PrintDL();          //打印电量
    PrintSl();          //打印水量
    PrintTempIn();      //打印舱内温度
    PrintTempOut();     //打印环境温度
}




RUN_Handle_Type UPL_Task_Handle;



void Task_UPLoad(void)
{
    UPL_Task_Handle.R_CYCLE = 10000;      //10S读一次数据
    UPL_Task_Handle.NMS = 10000;          //装载延时计数值
    UPL_Task_Handle.R_STATUS = STOP;     //设置状态为停止态
    UPL_Task_Handle.LEVEL = THREAD3;     //设置该任务优先级为0
    UPL_Task_Handle.LOCK = false;       //0任务锁打开，可以执行该任务
    UPL_Task_Handle.pf = UPLoad_Data;    //任务回调函数
    Task_Add(&UPL_Task_Handle);    
}






//设置命令码段内数据
void set_data(u8 dat, u8 index)
{
	cmd03[index] = dat;
}

//获取 ModbusCRC16校验值 
uint16_t ModbusCRC16_Set(u8* buf, u8 len)
{
    u8 i = 0, j = 0;
    u16 crc_ini = 0xffff;
    
    for(i = 0; i < len; i++){
        crc_ini ^= buf[i];
        for(j = 0; j < 8; j++){
            if(crc_ini & 0x0001){
                crc_ini = (crc_ini >> 1) ^ 0xA001; 
            }else{
                crc_ini >>= 1;
            }
        }
    }
    return crc_ini;
}

//获取 ModbusCRC16校验值,并插入校验值
void ModbusCRC16_Insert(u8* buf, u8 len)
{
	u16 crcVal = 0;
	crcVal = ModbusCRC16_Set(buf, len - 2);
	buf[len - 2] = crcVal & 0x00ff;             //CRC16_L
    buf[len - 1] = (crcVal >> 8) & 0x00ff;      //CRC16_H
}


//检查数据的ModbusCRC16的校验值，OK 返回1，否则返回0
u8 ModbusCRC16_Check(u8* buf, u8 len)
{
    u16 temp = 0;
    temp = ModbusCRC16_Set(buf, len - 2);
    if((temp & 0x00ff) == buf[len - 2] && ((temp >> 8) & 0x00ff) == buf[len - 1]){
        return 1;
    }else{
        return 0;
    }
    
}


//串口1接收数据处理
void USART1_RecDataProcess(void *pmt)
{
    pmt = pmt;
    u8 buf[16];
    u8 len = 0;
    
    USART1_Receive_Data(buf, &len);
    //修改电表的地址10 03 01 1F B4 BC  
    if(len != 0  && buf[0] == 0x10){        //接收到的数据不为零，且地址为0x10
        if(ModbusCRC16_Check(buf, len)){    //crc校验OK
            if(buf[1] == 0x03){             //命令码0x03  修改电表地址指令
                ModifyAddr(buf[3], 0x1f);    //buf[3] 原地址 buf[4] 新地址, 强制0x1f
            }
        }
    }else if(len != 0  && buf[0] == 0x08){
        if(buf[1] == 0x03){
            if(buf[3] == 0x00) mnflag = 0;
            else mnflag = 1;
        }
    }
   
}


RUN_Handle_Type UART1_Task_Handle;


void Task_UART1_Rec(void)
{
    UART1_Task_Handle.R_CYCLE = 10;      //10ms读一次数据
    UART1_Task_Handle.NMS = 10;          //装载延时计数值
    UART1_Task_Handle.R_STATUS = STOP;     //设置状态为停止态
    UART1_Task_Handle.LEVEL = THREAD4;     //设置该任务优先级为4
    UART1_Task_Handle.LOCK = false;       //0任务锁打开，可以执行该任务
    UART1_Task_Handle.pf = USART1_RecDataProcess;    //任务回调函数
    Task_Add(&UART1_Task_Handle);    
}




//打印输出用电量
void PrintDL(void)
{
    u32 value = 0;
    value = cmd03[3] << 24;
    value |= cmd03[4] << 16;
    value |= cmd03[5] << 8;
    value |= cmd03[6];
    if((value % 100) < 10){
        printf("Electricity meter: %d.0%d Kwh     ", value / 100, value % 100);
    }else{
        printf("Electricity meter: %d.%d Kwh     ", value / 100, value % 100);
    }
    
}

//打印输出用水量
void PrintSl(void)
{
    
    printf("Water: %d%d%d%d.%d%d%d%d M3 \r\n", cmd03[7]/16, cmd03[7]%16,cmd03[8]/16, cmd03[8]%16,cmd03[9]/16, cmd03[9]%16,cmd03[10]/16, cmd03[10]%16);
}

//打印输出舱内温度
void PrintTempIn(void)
{
    u16 val = 0;
    val = (cmd03[13]<< 8) + cmd03[14];
    if((val & 0x8000) != 0){		//温度负值处理
            val &= 0x0fff;
            printf("Temp-in: -%d.%d      ", val/10, val%10);
    }else{
            printf("Temp-in: %d.%d      ", val/10, val%10);
    }
}

//打印输出环境温度
void PrintTempOut(void)
{
    u16 val = 0;
    val = (cmd03[11]<< 8) + cmd03[12];
    if((val & 0x8000) != 0){		//温度负值处理
            val &= 0x0fff;
            printf("Temp-out: -%d.%d  \r\n", val/10, val%10);
    }else{
            printf("Temp-out: %d.%d   \r\n", val/10, val%10);
    }
}






