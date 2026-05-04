#include<lpc21xx.h>
#include "types.h"
void cfgportpinfun(u32 portNo,u32 pinNo,u32 pinfunc)
{
  if(portNo==0)
  {
     if(pinNo<16)
         {
            PINSEL0=(PINSEL0&~(3<<(pinNo*2)))|(pinfunc<<(pinNo*2));
         }
         else if(pinNo>=16 && pinNo<=31)
         {
             PINSEL1=(PINSEL1&~(3<<(pinNo-16)*2))|(pinfunc<<(pinNo-16)*2);
         }
  }
}
