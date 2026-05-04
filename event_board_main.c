#include <lpc21xx.h>
#include <string.h>
//include LCD header files
#include "lcd_defines.h"
#include "lcd.h"
#include "defines.h"^M
//include RTC and KPM headerfiles^M
#include "rtc.h"
#include "kpm.h"
#include "delay.h"
#include "event.h"^M
//include ADC headerfiles
#include "ADC.h"
#include "ADC_defines.h"

/*day of week macros used 
  to represent days(0-6)*/
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

#define SW    0    //cfg p0.0 pin as gpio input^M
#define LED1  1    //cfg p0.1 pin as gpio input^M
#define LED2  2    //cfg p0.2 pin as gpio input^M

//external RTC variables these variables are updated by RTC functions
extern s32 hour,min,sec,day,date,month,year,dow,key;^M

/*minutes and seconds for countdown
 prev_sec-->to track previous second
 prev_sec_display-->to update sensor value every one second
 eAR-->analog value
 Adcval-->adc raw value
 */
s32 mm,ss,prev_sec=-1,prev_sec_display=-1;
f32 eAR;
u32 Adcval;
u32 k,j,len;
char buf[200]; //buffer for message scroll

// Array to hold names of the messages
Message messageList[TOTAL_MESSAGES] = {
    {7, 45, "Good Morning! Classes Start Soon", 1},
    {13, 45, "C Programming Session in Classroom number 2", 1},
    {10, 15, "C module theory exam in 4th floor lab1", 1},
    {10, 45, "C module lab exam in 4th floor lab2 and middle lab at 10:30AM", 1},
    {12, 45, "Lunch Break from 1PM-2PM", 1},
    {9, 45, "ARM Workshop on external interrupts in LAB1 at 10AM", 1},
    {10, 17, "ARM kit issue time from 10AM-10:30AM in middle lab", 1},
    {15, 15, "Only 15 mins break time for next ARM session", 1},
    {17, 00, " Revise today's Class programs at home!", 1},
    {17, 45, " End of Day-See You Tomorrow!", 1}
};
/* MAIN FUNCTION
--------------------------------------------------
Initializes peripherals and continuously:
1. Checks RTC time
2. Displays scheduled messages
3. Shows time/date/temperature
4. Detects switch for admin mode */
int main()
{
        int i=0;
        RTC_Init();         //intialization of RTC
        InitLCD();          //intialization of LCD
      Initkpm();            //intialization of KPM
        InitADC();          //intialization of ADC^M

        IODIR0|=3<<LED1;   //cfg p0.1,p0.2 as gpio output

        //set intial RTC value
        SetRTCDateInfo(11,03,2026);
        SetRTCTimeInfo(10,44,0);
        SetRTCDay(MON);
     while(1)
        {
                IOSET0=1<<LED2; //turn off LED2
                  IOCLR0=1<<LED1;        //turn on LED1

                  GetRTCTimeInfo(&hour,&min,&sec);  //get current RTC time

                for(i=0;i<TOTAL_MESSAGES;i++)
                {
                    s32 countdown=60; //60 seconds of display time
                    //check if current time matches event time
                    if((hour==messageList[i].hour)&& (min==messageList[i].minute) &&
                                        (messageList[i].enabled==1) && sec==0)
                    {
                                       strcpy(buf,"                ");
                           strcat(buf,messageList[i].text);
                           strcat(buf,"                ");
                           len=strlen(buf)-16;
                                 CmdLCD(0x01); //clear LCD
                                 //count down loop 
                                  while(countdown>0)
                            {
                              for(k=0;k<len;k++)
                              {
                                  CmdLCD(GOTO_LINE1_POS0);
                                    for(j=k;j<16+k;j++)
                                         CharLCD(buf[j]); //scroll text
                                            delay_ms(300);
                                   if(countdown==0)
                                   {
                                         CmdLCD(0x01);
                                         break;
                                   }
                                   sec=SEC;//upadate countdown for every second
                                   if(sec != prev_sec)
                           {
                                      prev_sec = sec;
                                                mm = (countdown%3600)/60;
                                      ss = countdown%60;
                                        if(countdown>0)
                                                countdown--;
                            }
                                    CmdLCD(GOTO_LINE2_POS0);
                                  StrLCD("TIME LEFT:");
                                 //display countdown timer                                                                   
                                       CharLCD(mm/10+48);
                                 CharLCD(mm%10+48);
                                 CharLCD(':');
                                 CharLCD(ss/10+48);
                                 CharLCD(ss%10+48);
                               }
                        }
                   }
          }
          if(i==TOTAL_MESSAGES)
          {
                         GetRTCTimeInfo(&hour,&min,&sec); //get current RTC time 
                         if(sec!=prev_sec_display)
                         {
                           prev_sec_display=sec;
                           GetRTCDateInfo(&date,&month,&year);  //get current RTC date
                           GetRTCDay(&dow);                         //get current day
                     //display time,date,day
                           DisplayRTCTime(hour,min,sec);
                           DisplayRTCDay(dow);
                           DisplayRTCDate(date,month,year);
                     //display temperature using ADC
                           CmdLCD(GOTO_LINE2_POS0+10);
                           StrLCD("T:");
                           Read_ADC(CH1,&eAR,&Adcval);
                           U32LCD(eAR*100);
                     CharLCD(0xDF);  //degree symbol
                     CharLCD('C');
                         }
          }
          if(STATUSBIT(IOPIN0,SW)==0)
          {
                delay_ms(500);
                while(STATUSBIT(IOPIN0,SW)==0)  //switch long press detected
                Admin_mode();
                CmdLCD(0x01);
          }
        }
}
/* ---Admin mode function---
   provides menu
   1.RTC Edit
   2.Event Edit
   3.Exit */
void Admin_mode()
{
        CmdLCD(0x01);^M
        IOSET0=1<<LED1;^M
        IOCLR0=1<<LED2;
        while(1)
        {
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("---ADMIN MENU---");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("1.RTC 2.EVT 3.EXI");
                key=Keyscan();^M
                while(!colscan());      //switch release condition
                if(key=='1')
                {
                        RTC_EDIT();
                }
                else if(key=='2')
                {
                        EVENT_MSG_EDIT();
                }
                else if(key=='3')
                {
                        break;
                }
        }

}
/*RTC EDIT MENU */
void RTC_EDIT(void)
{
       CmdLCD(0x01);
       while(1)
      {
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("1.H 2.M 3.S 4.D");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("5.DY 6.M 7.Y 8.E");
            key=Keyscan();^M
            while(!colscan());
            switch(key)
            {
                  case '1':Hour_edit();
                             break;
                  case '2':Min_edit();
                             break;
                  case '3':Sec_edit();
                             break;
                  case '4':Date_edit();
                             break;
                  case '5':Day_edit();
                             break;
                  case '6':Month_edit();
                             break;
                  case '7':Year_edit();
                             break;
                  case '8':return;
                }
        }
}
/*EVENT MESSAGE EDIT MENU */
void EVENT_MSG_EDIT()
{
        CmdLCD(0x01);
        while(1)
        {
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("1.EVENT MSG INFO");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("2.EXIT");
                key=Keyscan();^M
                while(!colscan());
                if(key=='1')
                {
                        Event_msg_info();
                        CmdLCD(0x01);
                }
                else if(key=='2')
                {
                        break;
                }
        }
}
