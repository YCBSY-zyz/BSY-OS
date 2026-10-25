#include  "temp.h"
#include  "adc.h"
#include  "stdlib.h"
#include  "mybus.h"
#include  "bsy_os.h"

#define  THREAD2  2


//上分压电阻10K，下电阻NTC10K  3950，3.3V基准电压下温度检测数据表，共123个数据，-20--102度
const  u16 tb10K[] = {
    3706, 3686, 3664, 3641, 3618, 3594, 3569, 3543, 3516, 3489,     //-20 至 -11度
    3460, 3431, 3401, 3370, 3338, 3305, 3271, 3237, 3201, 3165,     //-10 至 -1度
    3128, 3091, 3052, 3013, 2973, 2933, 2892, 2850, 2808, 2765,     //0 至 9度
    2721, 2678, 2635, 2589, 2544, 2499, 2454, 2409, 2363, 2318,     //10 至 19度
    2272, 2227, 2181, 2136, 2091, 2047, 2001, 1956, 1912, 1869,     //20 至 29度
    1825, 1782, 1740, 1698, 1656, 1615, 1575, 1535, 1496, 1458,     //30 至 39度
    1420, 1383, 1347, 1311, 1276, 1241, 1208, 1175, 1143, 1111,     //40 至 49度
    1081, 1050, 1021, 992, 964, 937, 911, 885, 860, 835,    //50 至 59度
    811, 788, 766, 744, 722, 701, 681, 662, 643, 624,       //60 至 69度
    606, 589, 572, 556, 540, 524, 509, 495, 480, 467,       //70 至 79度
    453, 441, 428, 416, 404, 393, 382, 371, 361, 351,       //80 至 89度
    341, 332, 323, 314, 305, 297, 289, 281, 273, 266,       //90 至 99度
    259, 252, 245                                           //100 至 102度
};

u8 tempflag = 0;


const float Rp = 10000.0;
const float T2 = (273.15 + 25.0);
const float Bx = 3950.0;
const float Ka = 273.15;





void ReadTemp(void *pmt){
    pmt = pmt;
    u16 Temp = 0;
    //通过使用状态位标识程序运行到第几段,如果每段延时不同，则调用Task_Delay_ms修改延时，一次有效
    if(tempflag == 0){
        Temp = getTemp(0);                        //PA0 通道接仓室温度传感器ADC-IN0
        set_data((Temp >> 8) & 0x00ff, 13);       //高位在前，低位在后
        set_data((Temp & 0x00ff), 14);
        tempflag = 1;
        Task_Delay_ms(THREAD2, 2000);               //线程休眠2秒    
    }else{
        Temp = getTemp(1);        //PA1 通道接室内温度传感器ADC-IN1
        set_data((Temp >> 8) & 0x00ff, 11);
        set_data((Temp & 0x00ff), 12); 
        tempflag = 0;
    }
    
}


RUN_Handle_Type TMP_Task_Handle;


void Task_ReadTemp(void)
{
    TMP_Task_Handle.R_CYCLE = 3000;      //3000ms读一次数据
    TMP_Task_Handle.NMS = 3000;          //装载延时计数值
    TMP_Task_Handle.R_STATUS = STOP;     //设置状态为停止态
    TMP_Task_Handle.LEVEL = THREAD2;     //设置该任务优先级为2
    TMP_Task_Handle.LOCK = false;       //0任务锁打开，可以执行该任务
    TMP_Task_Handle.pf = ReadTemp;       //任务回调函数
    Task_Add(&TMP_Task_Handle);    
}






















//根据采样通道获取电阻值
u16 getTemp(u8 ch0)
{
    u8 i = 0;
    u16 tmp = 0;
    u16  val = 0;
    float a = 0.0;
    
    val =  Get_Adc_Average(ch0, 16);    //获取采样值
    //查表获取温度值-20 ---- 102度
    for(i = 0; i < 123; i++){
        
        if(val > tb10K[i]){             //检测值大于或等于当前数据表值时终止
            tmp = abs(i - 20);          //求绝对值
            a = (tb10K[i - 1] - val) / ((tb10K[i - 1] - tb10K[i]) / 10.0);      //求小数点位
            tmp = tmp * 10 + a;     //放大10倍，加上小数位
            
            if(i < 20) tmp |= 0x8000;   //温度值小于0度，添加负号位
            return tmp;
            
        }else if(val == tb10K[i]){      //相等时不求小数位
            tmp = abs(i - 20);          //求绝对值
            tmp = tmp * 10;
            if(i < 20) tmp |= 0x8000;
            return tmp;
            
        }
    }
    return 102 * 10;     //如果温度值溢出给最大值102度
    
}




