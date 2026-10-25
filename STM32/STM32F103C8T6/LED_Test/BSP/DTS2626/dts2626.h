#ifndef  __DTS2626_H
#define  __DTS2626_H
#include "sys.h"


void ReadDl(void *pmt);
void Task_ReadDl(void);
void DLRecProcess(void);
void  ModifyAddr(u8 oldAddr, u8 newAddr);

#endif

