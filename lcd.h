#include "types.h"
#ifndef LCD_H
#define LCD_H

void WriteLCD(u8 data);
void CmdLCD(u8 cmd);
void InitLCD(void);
void CharLCD(u8 ascii);
void StrLCD(u8 *str);
void U32LCD(u32 n);
void S32LCD(s32 n);
void BinLCD(u32 n,u8 nbd);
void BuildCGRAM(u8 *p,u8 nbytes);

#endif
