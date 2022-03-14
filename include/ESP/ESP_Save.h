#ifndef __ESP_SAVE_H
#define __ESP_SAVE_H

#include "Preferences.h"
#include "stdint.h"

#define NAMESPACE   "s_clock_space"
#define KEYNAME     "s_clock_key"


typedef struct
{
    uint32_t timestamp;     // 时间撮-0
    uint8_t  alarm_num;     // 闹钟数量-1
    char  alarm[5][16];     // 闹钟-1
    char  ssid[32];         // wifi名称-2
    char  passwd[32];       // wifi密码
    bool  ble_adv;          // 蓝牙广播-3
    bool  sleep_mode;       // 贪睡模式-4
    uint8_t lightness;      // 亮度-5
    char  weather_city[16]; // 天气城市-6
    char  weather_key[20];  // 密钥-7
    uint8_t  xiu_mode;      // 休眠方式-8
    uint8_t  sleep_timer;   // 无操作时长-9
}ESPSave_Info;

enum
{
    SAVE_CMD_TIMESTAMP     = 0,
    SAVE_CMD_ALARM         = 1,
    SAVE_CMD_WIFI          = 2,
    SAVE_CMD_BLE           = 3,
    SAVE_CMD_SLEEP_MODE    = 4,
    SAVE_CMD_LIGHTNESS     = 5,
    SAVE_CMD_WEATHER_CITY  = 6,
    SAVE_CMD_WEATHER_KEY   = 7,
    SAVE_CMD_XIU_MODE      = 8,
    SAVE_CMD_SLEEP_TIMER   = 9
};

extern ESPSave_Info myconfig;

void ESPSave_Init(void);
bool ESPSave_loadConfig(void);
void ESPSave_resetConfig(void);
void ESPSave_setConfig(ESPSave_Info *myconfig);
void ESPSave_updateConfig(uint8_t cmd);

#endif // !__ESP_SAVE_H