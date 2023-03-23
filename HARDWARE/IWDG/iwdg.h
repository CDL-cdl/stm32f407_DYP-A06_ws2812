#ifndef __IWDG_H
#define __IWDG_H
#include"sys.h"

extern void IWDG_init(u8 prer,u16 rlr);
extern void IWDG_Feed(void);
#endif
