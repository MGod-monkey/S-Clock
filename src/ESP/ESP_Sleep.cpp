#include "ESP/ESP_Sleep.h"
#include "globalConfig.h"
#include "Lightness.h"
#include "Debug.h"

static char sleep_mode_zh[][12] = {"睡眠", "息屏", "不息屏"};
struct _ESPSleep_Info ESPSleep_Info;

void ESPSleep_Init(void)
{
    ESPSleep_Info.on_sleep = false;
    ESPSleep_Info.last_activity_time = 0;
    esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKEUP_KEY, 0);
}

void ESPSleep_Start(void)
{
    ESPSleep_Info.on_sleep = true;
    switch (ESPSleep_Info.sleep_mode)
    {
        case 0:
            Lightness_Shutdown();
            esp_deep_sleep_start();
            break;
        case 1:
            Lightness_Shutdown();
            break;
    }        
}

void ESPSleep_Close(void)
{
    ESPSleep_Info.on_sleep = false;
    if (ESPSleep_Info.sleep_mode)
        Lightness_Open();
}

void ESPSleep_Update(void)
{
    ESPSleep_Info.last_activity_time = millis();
}

bool ESPSleep_Status(void)
{
    if (!ESPSleep_Info.last_activity_time || ESPSleep_Info.sleep_max_timer == 0)
    {
        ESPSleep_Info.last_activity_time = millis();
        return true;
    }
    if (millis() - ESPSleep_Info.last_activity_time < ESPSleep_Info.sleep_max_timer*1000)
        return true;

    return false;
}

void ESPSleep_setSleepTime(uint8_t delay_s)
{
    ESPSleep_Info.sleep_max_timer = delay_s;
}

void ESPSleep_setSleepMode(uint8_t sleepMode)
{
    sleepMode %= 2;
    ESPSleep_Info.sleep_mode = sleepMode;
    // if (ESPSleep_Info.sleep_mode == 2)
    //     ESPSleep_Info.sleep_max_timer = 0;      
}

void ESPSleep_changeSleepMode(void)
{
    ESPSleep_Info.sleep_mode =  (ESPSleep_Info.sleep_mode+1)%2;
    // if (ESPSleep_Info.sleep_mode == 2)
    //     ESPSleep_Info.sleep_max_timer = 0;      
}

const char* ESPSleep_getSleepMode(void)
{
    return sleep_mode_zh[ESPSleep_Info.sleep_mode];
}

void ESPSleep_Wakeup_Timer(uint32_t delay_ms)
{
    esp_sleep_enable_timer_wakeup(delay_ms*1000);
}