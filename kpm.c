#include <lpc21xx.h>
#include "defines.h"
#include "types.h"
#include "kpm_defines.h"
#include "kpm.h"

u8 kpmLUT[4][4]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
void Initkpm()
{
   WRITENIBBLE(IODIR1,ROW0,15); //set rows as o/p pins
}
u8 colscan()
{
  if(READNIBBLE(IOPIN1,COL0)<15)
     return 0;
  else
         return 1;
}
u8 Rowcheck()
{
 u8 rno;
 for(rno=0;rno<4;rno++)
 {
   WRITENIBBLE(IOPIN1,ROW0,~(1<<rno));
   if(colscan()==0)
     break;
 }
 WRITENIBBLE(IOPIN1,ROW0,0X0);
 return rno;
}
u8 Colcheck()
{
  u8 cno;
  for(cno=0;cno<4;cno++)
  {
    if(STATUSBIT(IOPIN1,(COL0+cno))==0)
        {
           break;
        }
  }
  return cno;
}
u8 Keyscan()
{
  u8 keyv,rno,cno;
  while(colscan());
  rno=Rowcheck();
  cno=Colcheck();
  keyv=kpmLUT[rno][cno];
  return keyv;
}
