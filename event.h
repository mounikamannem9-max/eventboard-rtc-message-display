#include "types.h"
#ifndef _EVENT_H
#define _EVENT_H

#define TOTAL_MESSAGES 10
typedef struct {
    u8 hour;
    u8 minute;
    char text[80];
    u8 enabled;         // 1 = show, 0 = skip (user controlled)
} Message;

extern Message messageList[TOTAL_MESSAGES];

void Admin_mode(void);
void RTC_EDIT(void);
void Sec_edit(void);
void Min_edit(void);
void Hour_edit(void);
void EVENT_MSG_EDIT(void);
void Date_edit(void);
void Day_edit(void);
void Month_edit(void);
void Year_edit(void);
void Event_msg_info(void);
s32 ReadNum(void);
void Activate_msg(u32 num);
void Deactivate_msg(u32 num);

#endif
