#ifndef  __NJSMSB_H
#define  __NJSMSB_H
#include "sys.h"


void  ReadSl(void *pmt);
void SLRecProcess(void);
u8  ModifySbAddr(u8 oldAddr, u8 newAddr);
void Task_ReadSl(void);


#endif

