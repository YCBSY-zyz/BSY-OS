#include "led.h"
#include "bsy_os.h"

//定义任务优先级，值越小优先级越高，有效值0 --- 255
#define      THREAD0     0


uchar  ledFlag = 0;

//LED运行任务
void Led_Run(void)
{
	if(ledFlag != 0){       //如果标识为非0值
		   led0_on;         //点亮led0   PC2
		   led1_on;         //点亮led1   PC3
		   led2_on;         //点亮led2   PC4
	}else{
		   led0_off;        //关闭led0
		   led1_off;        //关闭led1
		   led2_off;        //关闭led2
	}
	ledFlag = ~ledFlag;     //标识取反
}

//定义LED任务结构体变量
RUN_Handle_Type  LED0_Task_Handle;

//创建LED运行任务函数
void Task_led0(void)
{
	LED0_Task_Handle.R_CYCLE = 500;       //500ms延时周期
    LED0_Task_Handle.NMS = 500;           //延时计数值，递减计数
    LED0_Task_Handle.R_STATUS = STOP;     //运行状态STOP
    LED0_Task_Handle.LEVEL = THREAD0;     //线程优先级0
    LED0_Task_Handle.LOCK = 0;       	  //0 不锁定，1 锁定
    LED0_Task_Handle.pf = Led_Run;    	  //线程调度函数
    Task_Add(&LED0_Task_Handle);		  //添加任务到任务列表
}



