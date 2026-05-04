#include <lpc21xx.h>
#include "defines.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "types.h"

void WriteLCD(u8 data)
{
        SCLRBIT(IOCLR0,RW);       //to select write logic
          WRITEBYTE(IOPIN0,LCD_DATA,data); //to write data in the LCD
          SSETBIT(IOSET0,EN);
          delay_us(1);
          SCLRBIT(IOCLR0,EN);
          delay_ms(2);  //giving delay for internal process
}
void CmdLCD(u8 cmd)
{
   SCLRBIT(IOCLR0,RS);  //to select command reg=0
   WriteLCD(cmd);
}
void CharLCD(u8 ascii)
{
  SSETBIT(IOSET0,RS);  //to select data reg=1
  WriteLCD(ascii);
}
void InitLCD(void)         //intialization of lcd
{
  WRITEBYTE(IODIR0,LCD_DATA,0XFF);
  SETBIT(IODIR0,RS);
  SETBIT(IODIR0,RW);
  SETBIT(IODIR0,EN);
  delay_ms(15);
  CmdLCD(MODE_8BIT_1LINE);
  delay_ms(5);
  CmdLCD(MODE_8BIT_1LINE);
  delay_us(100);
  CmdLCD(MODE_8BIT_1LINE);
  CmdLCD(MODE_8BIT_2LINE);
  CmdLCD(DISP_ON_CUR_BLINK);
  CmdLCD(CLEAR_LCD);
  CmdLCD(SHIFT_CUR_RIGHT);
}
void StrLCD(u8 *str)    //to display strings
{
     while(*str)
         {
            CharLCD(*str++);
         }
}
void U32LCD(u32 n)              //to display integer values
{
  u8 arr[10];
  s32 i=0;
  if(n==0)
    CharLCD('0');
  else
  {
    while(n)
        {
           arr[i++]=(n%10)+'0';
           n/=10;
        }
        for(--i;i>=0;i--)
           CharLCD(arr[i]);
  }
}
void S32LCD(s32 n)      //to display signed integers
{
   if(n<0)
   {
     n=-n;
         CharLCD('-');
         U32LCD(n);
   }
}
 void BinLCD(u32 n,u8 nbd)  //to disp binary 
{
   s32 i;
   for(i=(nbd-1);i>=0;i--)
   {
     CharLCD(((n>>i)&1)+48);
   }
}
void BuildCGRAM(u8 *p,u8 nbytes) //to display custumized characters
{
   s32 i;
   CmdLCD(GOTO_CGRAM);
   for(i=0;i<nbytes;i++)
   {
     CharLCD(p[i]);
   }
   CmdLCD(GOTO_LINE2_POS0);      //go to DDRAM
}
void F32LCD(f32 fn,u32 ndp)      //to disp float values
{
   u32 n,i;
   if(fn<0.0)
   {
      CharLCD('-');
          fn=-fn;
   }
   n=fn;
   U32LCD(n);
   CharLCD('.');
   for(i=0;i<ndp;i++)
   {
      fn=(fn-n)*10;
          n=fn;
          CharLCD(n+48);
   }
}
void HexLCD(u32 n)      //to display hexadecimal value
{
   u8 a[8],rem;
   s32 i=0;
   if(n==0)
   CharLCD('0');
   else
   {
      while(n)
      {
              rem=n%16;
              (rem<10)?(rem+=48):(rem+=55);
                a[i++]=rem;
                n/=16;
          }
   }
   for(--i;i>=0;i--)
   {
      CharLCD(a[i]);
   }
}
void OctLCD(u32 n)   //to display octal value
{
   u8 a[12];
   s32 i=0;
   if(n==0)
   CharLCD('0');
   else
   {
     while(n)
         {
           a[i++]=(n%8)+48;
           n/=8;
         }
   }
   for(--i;i>=0;i--)
   CharLCD(a[i]);
}
