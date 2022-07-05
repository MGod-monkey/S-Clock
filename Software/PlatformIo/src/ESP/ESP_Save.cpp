#include "ESP/ESP_Save.h"
#include "ESP/ESP_BLE.h"
#include "ESP/ESP_WiFi.h"
#include "ESP/ESP_Sleep.h"
#include "Debug.h"
#include "Clock.h"
#include "Alarm.h"
#include "Lightness.h"
#include "Weather.h"

ESPSave_Info myconfig;
static Preferences pref;

void ESPSave_Init(void)
{
    if (!pref.begin(NAMESPACE))
    {
        SCLOCK_LOGLN("[Preferences Error] init failed!");
        return;
    }
    if (pref.isKey(KEYNAME))
        if (ESPSave_loadConfig())
            SCLOCK_LOGLN("[Preferences Success] load config successed!");
        else
        {
            SCLOCK_LOGLN("[Preferences Error] load config failed!"); 
            return;
        }
    // 第一次开启则加载默认配置
    else
        ESPSave_resetConfig();
    pref.end();
}

bool ESPSave_loadConfig(void)
{
    size_t schLen = pref.getBytesLength(KEYNAME);
    if (schLen % sizeof(ESPSave_Info))
        return false;
    char buffer[schLen];
    pref.getBytes(KEYNAME, buffer, schLen);
    ESPSave_Info *config = (ESPSave_Info*)buffer;
    myconfig = *config;
    ESPSave_setConfig(config);
    return true;
}

void ESPSave_setConfig(ESPSave_Info *myconfig)
{
    Alarm_setAlarmNum(myconfig->alarm_num);
    for (uint8_t i=0; i<myconfig->alarm_num; i++)
    {
        Alarm_setFullAlarmWithIndex(i, std::string(myconfig->alarm[i]));
    }
    if (!myconfig->ble_adv)
        BLE_closeAdvert();
    // if (myconfig->ssid && myconfig->passwd)
    //     ESPWifi_connectToWifi(myconfig->ssid, myconfig->passwd);
    Weather_setCity(myconfig->weather_city);
    Weather_setPrivateKey(myconfig->weather_key);
    Lightness_setNum(myconfig->lightness);
    myconfig->sleep_mode?Alarm_openSleepMode():Alarm_closeSleepMode();
    ESPSleep_setSleepMode(myconfig->xiu_mode);
    ESPSleep_setSleepTime(myconfig->sleep_timer);
}

void ESPSave_resetConfig(void)
{
    if (pref.isKey(KEYNAME))
        pref.remove(KEYNAME);
    // myconfig.timestamp=Clock_getTimestemp();
    myconfig.alarm_num=DEFAULT_ALARM_NUM;
    for (uint8_t i=0; i<myconfig.alarm_num; i++)
        strcpy(myconfig.alarm[i], DEFAULT_ALARM);
    #ifdef WIFI_SSID
        strcpy(myconfig.ssid, WIFI_SSID);
    #endif
    #ifdef WIFI_PASSWD
        strcpy(myconfig.passwd, WIFI_PASSWD);
    #endif
    strcpy(myconfig.weather_city, DEFAULT_CITY);
    strcpy(myconfig.weather_key, DEFAULT_PRIVATE_KEY);
    myconfig.ble_adv = DEFAULT_BLE_OPEN;
    myconfig.lightness = DEFAULT_LIGHTNESS;
    myconfig.sleep_mode = DEFALUT_SLEEP_OPEN;
    myconfig.xiu_mode = DEFALUT_SLEEP_MODE;
    myconfig.sleep_timer = DEFAULT_SLEEP_MAX_TIMER;
    pref.putBytes(KEYNAME, &myconfig, sizeof(ESPSave_Info));
    ESPSave_setConfig(&myconfig);
    SCLOCK_LOGLN("[Preferences Success] load default config successed!");
}

void ESPSave_updateConfig(uint8_t cmd)
{
    switch (cmd)
    {
    case 0:
        myconfig.timestamp=Clock_Info.timestamp;
    case 1:
        myconfig.alarm_num=Alarm_Info.alarm_num;
        for (uint8_t i=0;i<Alarm_Info.alarm_num; i++)
            strcpy(myconfig.alarm[i], Alarm_toSaveStr(i));
        break;
    case 2:
        strcpy(myconfig.ssid, Wifi_Info.ssid);
        strcpy(myconfig.passwd, Wifi_Info.passwd);
        break;
    case 3:
        myconfig.ble_adv = BLE_Info.ble_adv;
        break;
    case 4:
        myconfig.sleep_mode = Alarm_Info.sleep_mode;
        break;
    case 5:
        myconfig.lightness = Lightness_Info.lightness;
        break;
    case 6:
        strcpy(myconfig.weather_city, Weather_Self_Info.city);
        break;
    case 7:
        strcpy(myconfig.weather_key, Weather_Self_Info.private_key);
        break;
    case 8:
        myconfig.xiu_mode = ESPSleep_Info.sleep_mode;
        break;
    case 9:
        myconfig.sleep_timer = ESPSleep_Info.sleep_max_timer;
        break;        
    default:
        SCLOCK_LOGLN("[Preferences Error] cannot know command!");
        break;
    }
    pref.begin(NAMESPACE);
    pref.putBytes(KEYNAME, &myconfig, sizeof(ESPSave_Info));
    pref.end();
}