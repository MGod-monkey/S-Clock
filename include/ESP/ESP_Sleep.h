#ifndef __ESP_SLEEP_H
#define __ESP_SLEEP_H

#include "Arduino.h"

#define WAKEUP_KEY ClickedPin

struct _ESPSleep_Info
{
    uint8_t sleep_max_timer;
    unsigned long last_activity_time;
    bool on_sleep;
    uint8_t sleep_mode;      // 睡眠方式：深度睡眠/息屏
};

extern struct _ESPSleep_Info ESPSleep_Info;

void ESPSleep_Init(void);

void ESPSleep_Start(void);

void ESPSleep_Close(void);

void ESPSleep_Update(void);

bool ESPSleep_Status(void);

void ESPSleep_setSleepTime(uint8_t delay_s);

void ESPSleep_setSleepMode(uint8_t sleepMode);

void ESPSleep_changeSleepMode(void);

const char* ESPSleep_getSleepMode(void);

void ESPSleep_Wakeup_Timer(uint32_t delay_ms);

#endif // !__ESP_SLEEP_H
