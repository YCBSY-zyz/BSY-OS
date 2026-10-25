#ifndef __TEMP_H
#define __TEMP_H

#include  "sys.h"
#include <math.h>


//根据采用通道采样结果获取温度值
u16 getTemp(u8 ch0);
void Task_ReadTemp(void);

#endif

