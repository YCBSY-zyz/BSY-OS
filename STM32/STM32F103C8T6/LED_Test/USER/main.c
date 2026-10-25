/**********************************************************************************  
*   BSY-OS 实时操作系统测试代码
*   STM32F103C8T6  	 
*   硬件连接说明
*   串口1 调试接口
*	PA9(TXD1)--->调试信息端口
*	PA10(RXD1)-->调试信息端口
*   LED0  -->    PB5  
*   设计：8M晶振，72M时钟频率  BSY-OS使用Systick作为时基定时器
**********************************************************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "bsy_os.h"
#include "sys.h"
#include <stdio.h>
#include "wdg.h"
#include "led.h"
#include "stdlib.h"



/*******************************************************************************
* 函数名 : main 
* 描述   : 主函数
*******************************************************************************/
int main(void)
{
    
    Bsy_Os_Init();                  //BSY_OS系统及滴答时钟初始化，systick频率1000Hz

    Led_Config();                   //LED初始化
	USART1_Init_Config(115200);		//UART1用作串口调试信息
    
    delay_ms(100);
    
    
    //创建运行任务
    Task_Led();                     //任务0     LED闪烁任务  
    Task_Wdg();                     //任务1     喂狗任务, 1S喂一次
    Task_Uart();                    //任务2     USART1串口接收任务, 5MS执行一次
        
    IWDG_Init(4, 1250);              //初始化看门狗, 64分频，重装载值1250， 溢出时间约2S
    
    printf("BSY_OS system is running! \r\n");
    
	while(1)
	{ 
		Task_Schedule();	        //开始运行调度程序
        
	}		
	
}








