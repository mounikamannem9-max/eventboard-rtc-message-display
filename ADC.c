#include <lpc214x.h>
#include "ADC_defines.h"
#include "types.h"
#include "delay.h"
#include "ADC.h"

void InitADC(void)
{
  //PINSEL1|=AIN2;  
  cfgportpinfun(0,28,FN2);
  AD0CR=PDN_BIT|CLKDIV;
}
void Read_ADC(u32 chno,f32 *eAR,u32 *Adcval)
{
  //clear channel bits
  AD0CR&=~(255<<0);
  //select chno & start conv
  AD0CR|=chno|START_CONV;
  //wait for conv
  delay_us(3);
  //wait for done bit
  while(((AD0GDR>>DONE_BIT)&1)==0);
  //stop conv
  AD0CR&=~(START_CONV);
  //extract digital value from data reg
  *Adcval=((AD0GDR>>RESULT)&1023);
  //equivalent analog reading
  *eAR=(3.3/1023)*(*Adcval);
}

