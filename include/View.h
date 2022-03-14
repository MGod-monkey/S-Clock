#ifndef __VIEW_H
#define __VIEW_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "Debug.h"
#include "Alarm.h"
#include "Beep.h"
#include "Arduino.h"
#include "UiSource.h"
// #include "ESP/ESP_Key.h"

typedef void(*lv_app_load_fp)(void);

extern bool show_alarmWin;
extern uint8_t sleep_count;
extern lv_indev_t * indev_encoder;

void Load_SetupView(void);

void SetupView_Delete(void);

void ClockView_Create(void);

void Load_ClockView(uint32_t delay_ms);

void Load_MenuView(bool isDel);

void Load_AlarmMenu(void);

void Load_DateMenu(void);

void Load_LightnessMenu(void);

void Load_TimeMenu(void);

void Item_Back_Menu(lv_event_t* e);

void Menu_Back_Home(lv_event_t* e);

void Home_To_Menu(lv_event_t* e);

void View_Show_Messagebox(const char* title, const char* txt);

void View_Show_Messagebox(const char* title, const char* txt, uint32_t delay_ms);

void View_Show_Messagebox(const char* title, const char* txt, const char **btn_txts, lv_event_cb_t btn_event_cb);

void View_Show_Messagebox(const char* title, const char* txt, const char **btn_txts, lv_event_cb_t btn_event_cb, void* user_data);

void View_Close_Top_Objs(void);

void View_Close_All_Top_Objs(void);

void View_Alarm_Click_Event(lv_event_t* e);

void View_Show_AlarmWin(void);

void View_Close_AlarmWin(void);

#endif