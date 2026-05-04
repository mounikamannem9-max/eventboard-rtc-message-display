#include <lpc214x.h>^M

//include LCD header files^M

#include "lcd.h"^M

#include "lcd_defines.h"^M

#include "rtc.h"^M

// System clock and peripheral clock Macros^M

#define FOSC 12000000^M

#define CCLK (5*FOSC)    ^M

#define PCLK (CCLK/4)^M
^M
^M
// RTC Prescaler Calculation Macros^M

// RTC requires 32.768 kHz clock for 1-second increment.^M

// PREINT and PREFRAC registers divide PCLK to generate 32.768 kHz.^M
^M
^M
// PREINT = int (PCLK / 32768) - 1;^M

// PREFRAC = PCLK -((PREINT + 1) * 32768);^M

// Note: This information collected from LPC2129 Manual^M
^M
^M
#define PREINT_VAL (int) ((PCLK / 32768) - 1)^M

#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))^M
^M
^M
//RTC Control Register (CCR) Bit Definitions^M

// Bit 0 ? Clock Enable --> 1 = Enable RTC counters  0 = Disable RTC counters^M

#define RTC_ENABLE (1<<0)^M
^M
^M
// Bit 1 ? Clock Reset --> 1 = Reset RTC counters    0 = Normal operation^M

#define RTC_RESET (1<<1)^M

 ^M
^M
^M
//only for LPC2148^M

// Bit 4 ? Clock Source Select ^M

// 1 = Use external 32.768 kHz oscillator^M

// 0 = Use internal PCLK as RTC clock source^M

#define RTC_CLKSRC (1<<4)^M
^M
^M
^M

#define SUN 0^M

#define MON 1^M

#define TUE 2^M

#define WED 3^M

#define THU 4^M

#define FRI 5^M

#define SAT 6^M
^M
^M
//static s32 hour,min,sec,date,month,year,day;^M
^M
^M
// Array to hold names of days of the week^M

u8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};^M
^M
^M
#define _LPC2148^M
^M
^M
/*Initialize the Real-Time Clock (RTC)^M

This function disables the RTC, sets the prescaler values, ^M

and then enables the RTC.^M

*/^M

void RTC_Init(void) ^M
{^M

  // Disable and reset the RTC^M

        CCR = RTC_RESET;^M

        ^M

        #ifndef _LPC2148^M

  ^M

  // Set prescaler integer and fractional parts^M

        PREINT = PREINT_VAL;^M

        PREFRAC = PREFRAC_VAL;^M

  ^M

  // Enable the RTC^M

        CCR = RTC_ENABLE; ^M
^M
^M
        #else^M

  // Enable the RTC with external clock source^M

        CCR = RTC_ENABLE | RTC_CLKSRC;  ^M

        #endif^M

}^M
^M
^M
/*^M

Get the current RTC time^M

hour Pointer to store the current hour^M

minute Pointer to store the current minute^M

second Pointer to store the current second^M

*/^M

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)^M

{^M

        *hour = HOUR;^M

        *minute = MIN;^M

        *second = SEC;^M

}^M
^M
^M
/*^M

Display the RTC time on LCD^M

hour value (0-23)^M

minute value (0-59)^M

second value (0-59) seperated by ':'^M

*/^M

void DisplayRTCTime(u32 hour, u32 minute, u32 second)^M

{^M

        CmdLCD(GOTO_LINE1_POS0);^M

        CharLCD(hour/10+48);^M

        CharLCD(hour%10+48);^M

        CharLCD(':');^M

        CharLCD(minute/10+48);^M

        CharLCD(minute%10+48);^M

        CharLCD(':');^M

        CharLCD(second/10+48);          ^M

        CharLCD(second%10+48);  ^M

}^M
^M
^M
/*^M

Get the current RTC date^M

day Pointer to store the current date (1-31)^M

month Pointer to store the current month (1-12)^M

year Pointer to store the current year (four digits)^M

*/^M
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)^M

{^M

        *date = DOM;^M

        *month = MONTH;^M

        *year = YEAR;^M

}^M
^M
^M
/*^M

Display the RTC date on LCD^M

Day of month (1-31)^M

Month (1-12)^M

Year (four digits) and seperated by '/'^M

*/^M

void DisplayRTCDate(u32 date, u32 month, u32 year)^M

{^M

        CmdLCD(GOTO_LINE2_POS0);^M

        CharLCD(date/10+48);^M

        CharLCD(date%10+48);^M

        CharLCD('/');^M

        CharLCD(month/10+48);^M

        CharLCD(month%10+48);^M

        CharLCD('/');^M

        U32LCD(year);^M

}^M
^M
^M
/*^M

Set the RTC time^M

Hour to set (0-23)^M

Minute to set (0-59)^M

Second to set (0-59)^M

*/^M

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)^M

{^M

        HOUR = hour;^M

        MIN = minute;^M

        SEC = second;^M

}^M
^M
^M
/*^M

Set the RTC date^M

day of month to set (1-31)^M

month to set (1-12)^M

year to set (four digits)^M

*/^M

void SetRTCDateInfo(u32 date, u32 month, u32 year)^M

{^M

        DOM = date;^M

        MONTH = month;^M

        YEAR = year;^M

}^M
^M
^M
/*^M

Get the current day of the week^M

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)^M

*/^M
void SetRTCDay(u32 dow)^M

{^M

        DOW = dow;^M
}

