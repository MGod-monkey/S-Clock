#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "Beep.h"
#include "Clock.h"
#include "Debug.h"
#include "HTSensor.h"
#include "Lightness.h"
#include "ESP/ESP_BLE.h"
#include "ESP/ESP_Init.h"
#include "ESP/ESP_WiFi.h"
#include "ESP/ESP_Sleep.h"
#include "ESP/ESP_Save.h"


void ESP_Init()
{
    Lightness_Init();
    Beep_Init();
    // OTA_Init();
    Clock_Init();
    HTSensor_Init();
    BLE_Init();
    ESPWifi_Init();
    ESPSleep_Init();
    ESPSave_Init();
}

void ESP_Loop()
{
    if(!ESPSleep_Status() && !ESPSleep_Info.on_sleep && lv_anim_count_running()==0)
        ESPSleep_Start();
    lv_task_handler();
}

long String_Sub_To_Int(std::string str, uint16_t start_pos, size_t size)
{
    if (start_pos < 0)
        start_pos = 0;
    if (start_pos+size > str.length())
        size = str.length()-start_pos;
    return atol(str.substr(start_pos, size).c_str());
}

const char* String_Sub_To_Str(std::string str, uint16_t start_pos)
{
    if (start_pos < 0)
        start_pos = 0;
    size_t size = str.length()-start_pos;
    return str.substr(start_pos, size).c_str();
}

const char* String_Sub_To_Str(std::string str, uint16_t start_pos, size_t size)
{
    if (start_pos < 0)
        start_pos = 0;
    if (start_pos+size > str.length())
        size = str.length()-start_pos;
    return str.substr(start_pos, size).c_str();
}

// void lv_focus_group(lv_group_t* group)
// {
//     lv_indev_set_group(lv_indev_get_act(), group);
// }