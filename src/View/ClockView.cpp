#include "View.h"
#include "Clock.h"
#include "Alarm.h"
#include "HTSensor.h"
#include "ESP/ESP_BLE.h"

#define BIAOPAN_NUM 2   // 表盘样式数量

struct _Clock_View
{
    lv_obj_t* cont;
    lv_obj_t* img_ble;
    lv_obj_t* img_wifi;
    lv_obj_t* handle_sec;
    lv_obj_t* handle_min;
    lv_obj_t* handle_hour;
    lv_obj_t* label_clock;
    lv_obj_t* label_hour;
    lv_obj_t* label_week;
    lv_obj_t* label_minute;
    lv_obj_t* label_temp;
    lv_obj_t* label_hum;
    lv_obj_t* label_alarm;
    lv_obj_t* label_date;
    lv_obj_t* label_sleep_mode;
    lv_obj_t* btn_hidden;
    lv_obj_t* btn_hidden2;

    lv_timer_t* update_timer;   
    lv_timer_t* update_timer2;  
} clockView;

static uint8_t aht_count=0;
static uint8_t page_index=0;

static void ClockView_Btn_Event(lv_event_t* e)
{
    // lv_obj_t* obj = lv_event_get_target(e);
    // lv_obj_t* tile = lv_obj_get_parent(obj);
    // uint8_t index = (uint8_t)lv_obj_get_child_id(tile);
    // lv_event_code_t code = lv_event_get_code(e);
    page_index = (page_index+1)%2;
    if (page_index != 0)
    {
        lv_timer_pause(clockView.update_timer);
        lv_timer_resume(clockView.update_timer2);
    }
    else
    {
        lv_timer_resume(clockView.update_timer);
        lv_timer_pause(clockView.update_timer2);
    }
    lv_obj_set_tile_id(clockView.cont, page_index, 0, LV_ANIM_ON);
}

static void ClockView_Update(lv_timer_t* timer)
{
    Clock_Update();
    if ((aht_count++) % 10 == 0)
        HTSensor_Update();
    aht_count %= 10;
    BLE_Notify();
    if (show_alarmWin)
    {
        if (BLE_Info.ble_status == BLE_CONNECTED)
            lv_obj_clear_flag(clockView.img_ble, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(clockView.img_ble, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text_fmt(clockView.label_hour, "%02d", Clock_Info.hour);
        lv_label_set_text_fmt(clockView.label_minute, "%02d", Clock_Info.minute);
        lv_label_set_text_fmt(clockView.label_week, "%s", daysOfTheWeek_Zh[Clock_Info.week]);
        char datetime_str[] = "YY/MM/DD";
        lv_label_set_text_fmt(clockView.label_date, "%s", Clock_toString(datetime_str));
        lv_label_set_text_fmt(clockView.label_sleep_mode, "%s", Alarm_Info.sleep_mode?"on":"off");
        lv_label_set_text_fmt(clockView.label_hum, "%02.1f", HTSensor_Info.hum);
        lv_label_set_text_fmt(clockView.label_temp, "%02.1f", HTSensor_Info.temp);
        lv_obj_set_align(clockView.label_temp, LV_ALIGN_TOP_MID);
        lv_obj_set_align(clockView.label_hum, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_align(clockView.label_alarm, LV_ALIGN_TOP_MID);
        lv_obj_set_align(clockView.label_sleep_mode, LV_ALIGN_BOTTOM_MID);
        char alarm_str[] = "hh:mm";
        lv_label_set_text_fmt(clockView.label_alarm, "%s", Alarm_Info.isToday?Alarm_toString(alarm_str):"-:-");
    }


    if (Alarm_Status())
    {
        if (show_alarmWin) 
        { 
            View_Show_AlarmWin();
            // View_Show_Messagebox("消息", "闹钟响了!", 10*1000);
            show_alarmWin = false;
        }
        else 
        {
            if (!Beep_isPlaying())
                Beep_Play();
        }
    } else if (!show_alarmWin)
    {
        Beep_Shutdown();
        View_Close_AlarmWin();
        // if (Alarm_Info.sleep_mode)
        // {
        //     ++sleep_count;
        //     Alarm_addFiveMinute();
        // }
        show_alarmWin = true; 
    }
}

static void ClockView_Update2(lv_timer_t* timer)
{
    Clock_Update();
    if ((aht_count++) % 10 == 0) // 2s读取一次温湿度
        HTSensor_Update();
    aht_count %= 10;
    BLE_Notify();

    if (show_alarmWin)
    {
        lv_img_set_angle(clockView.handle_sec, 60*Clock_Info.second);   //sec * 3600/60
        lv_img_set_angle(clockView.handle_min, 60*Clock_Info.minute);   //min * 3600/60
        lv_img_set_angle(clockView.handle_hour, 300*Clock_Info.hour+Clock_Info.minute*5); //hour * 3600/12 + ((min * 3600/60)/12)
        char clock_str[] = "hh:mm:ss";
        lv_label_set_text_fmt(clockView.label_clock, "%s", Clock_toString(clock_str));
    }

    if (Alarm_Status())
    {
        if (show_alarmWin) 
        { 
            View_Show_AlarmWin();
            show_alarmWin = false;
        }else
        {
            if (!Beep_isPlaying())
                Beep_Play();
        }
    } else if (!show_alarmWin)
    {
        Beep_Shutdown();
        View_Close_AlarmWin();
        // if (Alarm_Info.sleep_mode)
        // {
        //     ++sleep_count;
        //     Alarm_addFiveMinute();
        // }
        show_alarmWin = true; 
    }
}

void ClockView_Create(void){
    lv_obj_t* tv = lv_tileview_create(NULL);
    lv_obj_set_scrollbar_mode(tv, LV_SCROLLBAR_MODE_OFF);
    
    lv_obj_t* tile, *btn, *cont;
    // 数字表盘
    tile = lv_tileview_add_tile(tv, 0, 0, LV_DIR_HOR);
    lv_obj_remove_style_all(tile);
    lv_obj_set_style_bg_color(tile, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_img_src(tile, &bg_biaopan, 0);
    // 时钟标签
    lv_obj_t* label_hour = lv_label_create(tile);
    lv_obj_t* label_minute = lv_label_create(tile);
    lv_obj_set_style_text_font(label_hour, &zh_cn_jshaonv_55, 0);
    lv_obj_set_style_text_font(label_minute, &zh_cn_jshaonv_55, 0);
    lv_obj_set_style_text_color(label_hour, lv_color_white(), 0);
    lv_obj_set_style_text_color(label_minute, lv_color_hex(0x9fd300), 0);
    lv_obj_align(label_hour, LV_ALIGN_CENTER, 0, -20);
    lv_obj_align(label_minute, LV_ALIGN_CENTER, 0, 20);
    lv_label_set_text_fmt(label_hour, "%02d", Clock_Info.hour);
    lv_label_set_text_fmt(label_minute, "%02d", Clock_Info.minute);
    // 星期标签
    lv_obj_t* label_week = lv_label_create(tile);
    lv_obj_set_style_text_font(label_week, &zh_cn_jshaoer_16, 0);
    lv_obj_set_style_text_color(label_week, lv_color_hex(0x9fd300), 0);
    lv_obj_align(label_week, LV_ALIGN_TOP_MID, 0, 10);
    lv_label_set_text(label_week, "日");
    // 温湿度
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 36);
    lv_obj_align(cont, LV_ALIGN_LEFT_MID, 6, 0);
    lv_obj_t* label_temp = lv_label_create(cont);
    lv_obj_set_style_text_font(label_temp, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label_temp, lv_color_white(), 0);
    lv_label_set_text(label_temp, "0.0");
    lv_obj_set_align(label_temp, LV_ALIGN_TOP_MID);
    lv_obj_t* label_hum = lv_label_create(cont);
    lv_obj_set_style_text_font(label_hum, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label_hum, lv_color_white(), 0);
    lv_label_set_text(label_hum, "0.0");
    lv_obj_set_align(label_hum, LV_ALIGN_BOTTOM_MID);
    // 闹钟/贪睡模式
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 36);
    lv_obj_align(cont, LV_ALIGN_RIGHT_MID, -6, 0);
    lv_obj_t* label_alarm = lv_label_create(cont);
    lv_obj_set_style_text_font(label_alarm, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label_alarm, lv_color_white(), 0);
    lv_label_set_text(label_alarm, "-:-");
    lv_obj_set_align(label_alarm, LV_ALIGN_TOP_MID);
    lv_obj_t* label_sleep_mode = lv_label_create(cont);
    lv_obj_set_style_text_font(label_sleep_mode, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label_sleep_mode, lv_color_white(), 0);
    lv_label_set_text(label_sleep_mode, "off");
    lv_obj_set_align(label_sleep_mode, LV_ALIGN_BOTTOM_MID);
    // 日期
    lv_obj_t* label_date = lv_label_create(tile);
    lv_obj_set_style_text_font(label_date, &zh_cn_jshaoer_18, 0);
    lv_obj_set_style_text_color(label_date, lv_color_white(), 0);
    lv_obj_align(label_date, LV_ALIGN_BOTTOM_MID, 0, -4);
    lv_label_set_text(label_date, "22/02/01");
    // 蓝牙
    lv_obj_t* img_ble = lv_img_create(tile);
    lv_img_set_src(img_ble, &icon_ble_on);
    lv_obj_align_to(img_ble, label_week, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_flag(img_ble, LV_OBJ_FLAG_HIDDEN);
    // wifi
    lv_obj_t* img_wifi = lv_img_create(tile);
    lv_img_set_src(img_wifi, &icon_wifi_on);
    lv_obj_align_to(img_wifi, label_week, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_flag(img_wifi, LV_OBJ_FLAG_HIDDEN);
    // 隐藏按钮
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, Home_To_Menu, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_event_cb(btn, ClockView_Btn_Event, LV_EVENT_FOCUSED, NULL);
    clockView.btn_hidden = btn;

    // 指针表盘
    tile = lv_tileview_add_tile(tv, 1, 0, LV_DIR_HOR);
    lv_obj_remove_style_all(tile);
    lv_obj_set_x(tile, TFT_WIDTH);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_img_src(tile, &bg_clock, 0);
    // 时间
    lv_obj_t* cont_label = lv_obj_create(tile);
    lv_obj_remove_style_all(cont_label);
    lv_obj_set_size(cont_label, 45, 12);
    lv_obj_align(cont_label, LV_ALIGN_BOTTOM_MID, 0, -34);
    // lv_obj_set_style_bg_color(cont_label, lv_color_black(), 0);
    // lv_obj_set_style_bg_opa(cont_label, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(cont_label, 3, 0);
    lv_obj_set_style_text_font(cont_label, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_shadow_color(cont_label, lv_color_hex(0x9b9b9b), 0);
    lv_obj_set_style_shadow_width(cont_label, 12, 0);
    lv_obj_set_style_shadow_spread(cont_label, 1, 0);
    lv_obj_t* label = lv_label_create(cont_label);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "12:00:00");
    lv_obj_center(label);
    clockView.label_clock = label;
    // 指针
    lv_obj_t* handle;
    handle = lv_img_create(tile);
    lv_img_set_src(handle, &handle_hour);
    lv_img_set_pivot(handle, 3, 29);
    lv_obj_align(handle, LV_ALIGN_CENTER, 0, -13);
    clockView.handle_hour = handle;
    handle = lv_img_create(tile);
    lv_img_set_src(handle, &handle_min);
    lv_img_set_pivot(handle, 2, 33);
    lv_obj_align(handle, LV_ALIGN_CENTER, 0, -15);
    clockView.handle_min = handle;
    handle = lv_img_create(tile);
    lv_img_set_src(handle, &handle_sec);
    lv_img_set_pivot(handle, 5, 39);
    lv_obj_align(handle, LV_ALIGN_CENTER, 0, -14);
    clockView.handle_sec = handle;
    // 隐藏按钮
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, Home_To_Menu, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_event_cb(btn, ClockView_Btn_Event, LV_EVENT_FOCUSED, NULL);
    clockView.btn_hidden2 = btn;

    clockView.cont = tv;
    clockView.label_hour = label_hour;
    clockView.label_week = label_week;
    clockView.label_minute = label_minute;
    clockView.label_temp = label_temp;
    clockView.label_hum = label_hum;
    clockView.label_alarm = label_alarm;
    clockView.label_date = label_date;
    clockView.img_ble = img_ble;
    clockView.img_wifi = img_wifi;
    clockView.label_sleep_mode = label_sleep_mode;

    lv_timer_t* update_timer = lv_timer_create(ClockView_Update, 200, NULL);
    clockView.update_timer = update_timer;
    lv_timer_t* update_timer2 = lv_timer_create(ClockView_Update2, 200, NULL);
    clockView.update_timer2 = update_timer2;
    lv_timer_pause(update_timer);
    lv_timer_pause(update_timer2);
	lv_obj_set_tile_id(tv, page_index, 0, LV_ANIM_OFF);
}

void Load_ClockView(uint32_t delay_ms)
{
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, clockView.btn_hidden);
    lv_group_add_obj(group, clockView.btn_hidden2);

    if(page_index == 0)
        lv_group_focus_obj(clockView.btn_hidden);
    else
        lv_group_focus_obj(clockView.btn_hidden2);

    if (delay_ms != 0)
        lv_scr_load_anim(clockView.cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, delay_ms, true);
    else
        lv_scr_load_anim(clockView.cont, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 500, 0, true);
}