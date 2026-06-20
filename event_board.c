#include <lpc21xx.h>
#include "rtc.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "defines.h"
#include "kpm.h"
#include "delay.h"
#include "event.h"
#include <string.h>

s32 hour,min,sec,day,date,month,year,key,dow,msgno;^M
/* HOUR EDIT FUNCTION
--------------------------------------------------
Allows user to modify RTC hour value

A -> Increment hour (0-23)
B -> Decrement hour (23-0)
8 -> Exit from hour edit mode */
void Hour_edit()
{
  while(1)
  {
   CmdLCD(0x01);         // Clear LCD
   hour=HOUR;           // Read current hour
   CmdLCD(GOTO_LINE1_POS0);
   CharLCD(hour/10+48);
   CharLCD(hour%10+48);
   key = Keyscan();    //Read keypad input
   while(!colscan());  // Wait for key release
   if(key == 'A')    //increment hour
   {
      (hour >= 23)?(hour=0):( hour++);
       HOUR=hour;
   }
   else if(key == 'B')  //decrement hour
   {
     (hour == 0)?(hour = 23):(hour--);
      HOUR=hour;
   }
   else if(key=='8') //exit
   {
                 break;
   }
 }
}
/* MINUTE EDIT FUNCTION
--------------------------------------------------
Allows user to modify RTC minute value

A -> Increment minute (0-59)
B -> Decrement minute (59-0)
8 -> Exit */
void Min_edit()
{
  while(1)
  {
   CmdLCD(0x01);
   min=MIN;
   CmdLCD(GOTO_LINE1_POS0);
   CharLCD(min/10+48);
   CharLCD(min%10+48);
   key = Keyscan();
   while(!colscan());
   if(key == 'A')
   {
     (min >= 59)?(min=0):(min++);
      MIN=min;
   }
   else if(key == 'B')
   {
      (min == 0)?(min= 59):(min--);
       MIN=min;
   }
   else if(key=='8')
   {
                 break;
   }
 }
}
/* SECOND EDIT FUNCTION
--------------------------------------------------
Allows user to modify RTC seconds

A -> Increment seconds
B -> Decrement seconds
8 -> Exit  */
void Sec_edit()
{
  while(1)
  {
   CmdLCD(0x01);
   sec=SEC;
   CmdLCD(GOTO_LINE1_POS0);
   CharLCD(sec/10+48);
   CharLCD(sec%10+48);
   key = Keyscan();
   while(!colscan());
   if(key == 'A')
   {
      (sec >= 59)?(sec=0):(sec++);
       SEC=sec;
   }
   else if(key == 'B')
   {
     (sec== 0)?(sec= 59):(sec--);
      SEC=sec;
   }
   else if(key=='8')
   {
                 break;
   }
 }
}
/* DATE EDIT FUNCTION
--------------------------------------------------
Allows user to modify date (1-31)

A -> Increment date
B -> Decrement date
8 -> Exit */
void Date_edit()
{
        while(1)
        {
          CmdLCD(0x01);
          date=DOM;
          CmdLCD(GOTO_LINE1_POS0);
          CharLCD(date/10+48);
          CharLCD(date%10+48);
          key=Keyscan();^M
          while(!colscan());
          if(key == 'A')
      {
       (date >= 31)?(date=1):(date++);
        DOM=date;
      }
      else if(key == 'B')
      {
        (date<=1)?(date=31):(date--);
         DOM=date;
      }
          else if(key=='8')
          {
                 break;
          }
 }
}
/* DAY EDIT FUNCTION
--------------------------------------------------
Allows user to modify day of week (0-6)

A -> Next day
B -> Previous day
8 -> Exit */
void Day_edit()
{
        while(1)
        {
          CmdLCD(0x01);
          GetRTCDay(&dow);
          DisplayRTCDay(dow);
          key=Keyscan();^M
          while(!colscan());
          if(key == 'A')
      {
        (dow>=6)?(dow=0):(dow++);
        SetRTCDay(dow);
      }
      else if(key == 'B')
      {
        (dow==0)?(dow=6):(dow--);
        SetRTCDay(dow);
      }
          else if(key=='8')
          {
                 break;
          }
        }
}
/* MONTH EDIT FUNCTION
--------------------------------------------------
Allows user to modify month (1-12)

A -> Increment month
B -> Decrement month
8 -> Exit */
void Month_edit()
{
        while(1)
        {
           CmdLCD(0x01);
           month=MONTH;
           CmdLCD(GOTO_LINE1_POS0);
           CharLCD(month/10+48);
           CharLCD(month%10+48);
           key=Keyscan();^M
           while(!colscan());
           if(key == 'A')
       {
          (month>= 12)?(month=1):(month++);
           MONTH=month;
       }
       else if(key == 'B')
       {
          (month<=1)?(month=12):(month--);
           MONTH=month;
       }
           else if(key=='8')
           {
                 break;
           }
        }
}
/* YEAR EDIT FUNCTION
--------------------------------------------------
Allows user to modify year

A -> Increment year
B -> Decrement year
8 -> Exit */
void Year_edit()
{
        while(1)
        {
          CmdLCD(0x01);
          year=YEAR;
          CmdLCD(GOTO_LINE1_POS0);
          U32LCD(year);
          key=Keyscan();^M
          while(!colscan());
          if(key == 'A')
      {
         (year>=4095)?(year=1):(year++);
          YEAR=year;
      }
      else if(key == 'B')
      {
        (year<=1)?(year=4095):(year--);
        YEAR=year;
     }
         else if(key=='8')
         {
                 break;
         }
   }
}
/* READ NUMBER FUNCTION
--------------------------------------------------
Reads multi-digit number from keypad
Returns Entered integer value */
s32 ReadNum(void)
{
   u32 sum;
   s8 keyv;
        sum=0;
        while(1)
        {
                keyv=Keyscan();^M
                while(!colscan());
                if((keyv>='0') && (keyv<='9'))
                {
                        sum=(sum*10)+(keyv-'0');
                        while(colscan()==0);
                }
                else
                {
                    while(colscan()==0);
                        break;
                }
        }
        return sum;
}
//Enables selected event message
void Activate_msg(u32 num)
{
        messageList[num-1].enabled=1;
}
// Disables selected event message
void Deactivate_msg(u32 num)
{
        messageList[num-1].enabled=0;
}
/* EVENT MESSAGE INFO FUNCTION
--------------------------------------------------
Allows user to:
Enter message number
1. Activate message
2. Deactivate message 
3. exit */
void Event_msg_info()
{
        CmdLCD(0x01);
        while(1)
        {
                 CmdLCD(GOTO_LINE1_POS0);
                 StrLCD("--EVENT SETT--");
                 CmdLCD(GOTO_LINE2_POS0);
                 StrLCD("ENTER MSGNO:");
                 msgno=ReadNum();  //Read message number
                 CmdLCD(GOTO_LINE2_POS0+13);
                 U32LCD(msgno);
                 delay_ms(500);
                 if(msgno>=1 && msgno<=10) //checking valid range
                 {
                         CmdLCD(0x01);
                         while(1)
                         {
                                 CmdLCD(GOTO_LINE1_POS0);
                                 StrLCD("1.ACTIVATE 3.EXIT");
                                 CmdLCD(GOTO_LINE2_POS0);
                                 StrLCD("2.DEACTIVATE");
                                 key=Keyscan();
                                 while(!colscan());
                                 if(key=='1')
                                 {
                                            Activate_msg(msgno);
                                 }
                                 else if(key=='2')
                                 {
                                            Deactivate_msg(msgno);
                                 }
                                 else if(key=='3')
                                            return;
                         }
                 }
                 else
                 {
                        CmdLCD(0x01);
                        StrLCD("invalid range");
                        delay_s(1);
                 }
        }
}
