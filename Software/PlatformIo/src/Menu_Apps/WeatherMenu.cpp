#include "Menu/Menu_Apps.h"
#include "Weather.h"
#include "ESP/ESP_WiFi.h"
#include "ESP/ESP_Key.h"

struct _Weather_View
{
    lv_obj_t* cont;
    lv_obj_t* label_day_one_date;
    lv_obj_t* label_day_one_img;
    lv_obj_t* label_day_one_text;
    lv_obj_t* label_day_one_temp;
    lv_obj_t* label_day_one_hum;

    lv_obj_t* label_day_two_date;
    lv_obj_t* label_day_two_img;
    lv_obj_t* label_day_two_text;
    lv_obj_t* label_day_two_temp;
    lv_obj_t* label_day_two_hum;

    lv_obj_t* label_day_three_date;
    lv_obj_t* label_day_three_img;
    lv_obj_t* label_day_three_text;
    lv_obj_t* label_day_three_temp;
    lv_obj_t* label_day_three_hum;
}weatherView;

static void WeatherMenu_Show_Detail(uint8_t index);
static void WeatherMenu_Btn_Event(lv_event_t* e);
static void WeatherMenu_Btn_Event2(lv_event_t* e);
static void WeatherMenu_Btns_Event(lv_event_t* e);
static uint32_t start_time; 

void WeatherMenu_Update(lv_timer_t* timer)
{
    if (Wifi_Info.wifi_status != WF_CONNECTED)
    {
        lv_timer_del(timer);
        static const char *btns[] = {"去联网","退出", ""};
        View_Show_Messagebox("提示", "网络未连接!", btns, WeatherMenu_Btns_Event);
    } else if (!Weather_Update() && millis() - start_time >= WIFI_CONNECT_TIMEOUT)
    {
        lv_timer_del(timer);
        static const char *btns[] = {"重试","退出", ""};
        View_Show_Messagebox("提示", "更新天气信息失败,请检查网络...", btns, WeatherMenu_Btns_Event);
    } else 
    {
        switch (Weather_Info.day_one_code_day)
        {
        case 0 ... 3:
            lv_img_set_src(weatherView.label_day_one_img, &weather_sun);
            break;
        case 4 ... 9:
            lv_img_set_src(weatherView.label_day_one_img, &weather_cloudy);
            break;
        case 10: case 13 ... 20:
            lv_img_set_src(weatherView.label_day_one_img, &weather_rain);
            break;
        case 11: case 12:
            lv_img_set_src(weatherView.label_day_one_img, &weather_thundershower);
            break;
        case 21 ... 25:
            lv_img_set_src(weatherView.label_day_one_img, &weather_snow);
            break;
        default:
            lv_img_set_src(weatherView.label_day_one_img, &weather_sun);
            break;
        }

        switch (Weather_Info.day_two_code_day)
        {
        case 0 ... 3:
            lv_img_set_src(weatherView.label_day_two_img, &weather_sun);
            break;
        case 4 ... 9:
            lv_img_set_src(weatherView.label_day_two_img, &weather_cloudy);
            break;
        case 10: case 13 ... 20:
            lv_img_set_src(weatherView.label_day_two_img, &weather_rain);
            break;
        case 11: case 12:
            lv_img_set_src(weatherView.label_day_two_img, &weather_thundershower);
            break;
        case 21 ... 25:
            lv_img_set_src(weatherView.label_day_two_img, &weather_snow);
            break;
        default:
            lv_img_set_src(weatherView.label_day_two_img, &weather_sun);
            break;
        }

        switch (Weather_Info.day_three_code_day)
        {
        case 0 ... 3:
            lv_img_set_src(weatherView.label_day_three_img, &weather_sun);
            break;
        case 4 ... 9:
            lv_img_set_src(weatherView.label_day_three_img, &weather_cloudy);
            break;
        case 10: case 13 ... 20:
            lv_img_set_src(weatherView.label_day_three_img, &weather_rain);
            break;
        case 11: case 12:
            lv_img_set_src(weatherView.label_day_three_img, &weather_thundershower);
            break;
        case 21 ... 25:
            lv_img_set_src(weatherView.label_day_three_img, &weather_snow);
            break;
        default:
            lv_img_set_src(weatherView.label_day_three_img, &weather_sun);
            break;
        }
        
        lv_label_set_text(weatherView.label_day_one_date, Weather_Info.day_one_date);
        lv_label_set_text(weatherView.label_day_one_text, Weather_Info.day_one_text_day);
        lv_label_set_text_fmt(weatherView.label_day_one_temp, "%d~%d°", Weather_Info.day_one_temp_low, Weather_Info.day_one_temp_high);
        lv_label_set_text_fmt(weatherView.label_day_one_hum, "%d%%", Weather_Info.day_one_hum);

        lv_label_set_text(weatherView.label_day_two_date, Weather_Info.day_two_date);
        lv_label_set_text(weatherView.label_day_two_text, Weather_Info.day_two_text_day);
        lv_label_set_text_fmt(weatherView.label_day_two_temp, "%d~%d°", Weather_Info.day_two_temp_low, Weather_Info.day_two_temp_high);
        lv_label_set_text_fmt(weatherView.label_day_two_hum, "%d%%", Weather_Info.day_two_hum);

        lv_label_set_text(weatherView.label_day_three_date, Weather_Info.day_three_date);
        lv_label_set_text(weatherView.label_day_three_text, Weather_Info.day_three_text_day);
        lv_label_set_text_fmt(weatherView.label_day_three_temp, "%d~%d°", Weather_Info.day_three_temp_low, Weather_Info.day_three_temp_high);
        lv_label_set_text_fmt(weatherView.label_day_three_hum, "%d%%", Weather_Info.day_three_hum);
        lv_timer_del(timer);
    }
}

static void WeatherMenu_Btn_Event(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    lv_obj_t* tv = (lv_obj_t*)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_FOCUSED)
        lv_obj_set_tile(tv, lv_obj_get_parent(obj), LV_ANIM_ON);
    else if (code == LV_EVENT_CLICKED)
        WeatherMenu_Show_Detail(lv_obj_get_child_id(lv_obj_get_parent(obj)));
}

static void WeatherMenu_Btn_Event2(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    lv_obj_t* tv = (lv_obj_t*)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_FOCUSED)
        lv_obj_set_tile(tv, lv_obj_get_parent(obj), LV_ANIM_ON);
    else if (code == LV_EVENT_LONG_PRESSED || code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tv);
        lv_indev_set_group(indev_encoder, lv_group_get_default());;
    }
}

static void WeatherMenu_Btns_Event(lv_event_t* e)
{
    lv_obj_t * mbox = lv_event_get_current_target(e);
    const char* btn_text = lv_msgbox_get_active_btn_text(mbox);
    if (!strcmp(btn_text, "去联网"))
    {
        View_Close_All_Top_Objs();
        Load_ToolboxMenu();
    } else if (!strcmp(btn_text, "退出"))
    {
        View_Close_All_Top_Objs();
        Item_Back_Menu(nullptr);
    } else if (!strcmp(btn_text, "重试"))
    {
        View_Close_All_Top_Objs();
        Load_WeatherMenu();
    }
}


static void WeatherMenu_Show_Detail(uint8_t index)
{
    uint8_t day_wind_scale=0;
    const char* day_wind_dir="北";
    float day_rainfall=0,day_precip=0,day_wind_speed=0;
    switch (index)
    {
        case 0:
            day_rainfall = Weather_Info.day_one_rainfall;
            day_precip   = Weather_Info.day_one_precip;
            day_wind_dir = Weather_Info.day_one_wind_direction;
            day_wind_speed = Weather_Info.day_one_wind_speed;
            day_wind_scale = Weather_Info.day_one_wind_scale;
            break;
        case 1:
            day_rainfall = Weather_Info.day_two_rainfall;
            day_precip   = Weather_Info.day_two_precip;
            day_wind_dir = Weather_Info.day_two_wind_direction;
            day_wind_speed = Weather_Info.day_two_wind_speed;
            day_wind_scale = Weather_Info.day_two_wind_scale;
            break;
        case 2:
            day_rainfall = Weather_Info.day_three_rainfall;
            day_precip   = Weather_Info.day_three_precip;
            day_wind_dir = Weather_Info.day_three_wind_direction;
            day_wind_speed = Weather_Info.day_three_wind_speed;
            day_wind_scale = Weather_Info.day_three_wind_scale;
            break;
    }
    static lv_style_t style_font_12, style_font_14, style_bg_grey;
    lv_style_init(&style_font_12);
    lv_style_init(&style_font_14);
    lv_style_init(&style_bg_grey);
    lv_style_set_text_color(&style_font_12, lv_color_white());
    lv_style_set_text_font(&style_font_12, &zh_cn_jshaoer_12);
    lv_style_set_text_color(&style_font_14, lv_color_white());
    lv_style_set_text_font(&style_font_14, &zh_cn_jshaoer_14);
    lv_style_set_radius(&style_bg_grey, 5);
    lv_style_set_bg_opa(&style_bg_grey, LV_OPA_80);
    lv_style_set_bg_color(&style_bg_grey, lv_color_hex(0x4a4a4a));

    lv_obj_t* tv_detail = lv_tileview_create(lv_layer_top());
    lv_obj_set_style_bg_color(tv_detail, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(tv_detail, LV_OPA_COVER, 0);
    lv_obj_set_scrollbar_mode(tv_detail, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t* tile, * cont, * label, * img, * btn;
    // 降水量详情
    tile = lv_tileview_add_tile(tv_detail, 0, 0, LV_DIR_HOR);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(tile, LV_SCROLLBAR_MODE_OFF);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 90);
    lv_obj_set_align(cont, LV_ALIGN_TOP_MID);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text_fmt(label, "%.2f", day_rainfall);
    lv_obj_set_style_text_color(label, lv_color_white(),0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);
    img = lv_img_create(cont);
    lv_img_set_src(img, &weather_rainfall);
    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 2);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text_fmt(label, "降水概率:%.2f", day_precip);
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_center(label);

    lv_group_t* group = lv_group_create();
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_FOCUSED, tv_detail);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_CLICKED, tv_detail);
    // lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_LONG_PRESSED, tv_detail);
    lv_group_add_obj(group, btn);
    // 风向、风速详情
    tile = lv_tileview_add_tile(tv_detail, 1, 0, LV_DIR_HOR);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(tile, LV_SCROLLBAR_MODE_OFF);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 90);
    lv_obj_set_align(cont, LV_ALIGN_TOP_MID);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    img = lv_img_create(cont);
    lv_img_set_src(img, &weather_wind);
    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 2);
    label = lv_label_create(cont);
    lv_label_set_text_fmt(label, "%.1fkm/h", day_wind_speed);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);

    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 65, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 14, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text_fmt(label, "%s", day_wind_dir);
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_center(label);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 86, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text_fmt(label, "%d", day_wind_scale);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_center(label);

    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_FOCUSED, tv_detail);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_CLICKED, tv_detail);
    // lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event2, LV_EVENT_LONG_PRESSED, tv_detail);
    lv_group_add_obj(group, btn);
    lv_indev_set_group(indev_encoder, group);
}

void Load_WeatherMenu(void)
{
    static lv_style_t style_font_12, style_font_14, style_bg_grey;
    lv_style_init(&style_font_12);
    lv_style_init(&style_font_14);
    lv_style_init(&style_bg_grey);
    lv_style_set_text_color(&style_font_12, lv_color_white());
    lv_style_set_text_font(&style_font_12, &zh_cn_jshaoer_12);
    lv_style_set_text_color(&style_font_14, lv_color_white());
    lv_style_set_text_font(&style_font_14, &zh_cn_jshaoer_14);
    lv_style_set_radius(&style_bg_grey, 5);
    lv_style_set_bg_opa(&style_bg_grey, LV_OPA_80);
    lv_style_set_bg_color(&style_bg_grey, lv_color_hex(0x4a4a4a));

    lv_obj_t* tv = lv_tileview_create(NULL);
    lv_obj_set_scrollbar_mode(tv, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t* tile, *cont, * label, * img, * btn;
    // 今天天气磁贴
    tile = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(tile, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 90);
    lv_obj_set_align(cont, LV_ALIGN_TOP_MID);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "2022-02-01");
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 2);
    weatherView.label_day_one_date = label;
    img = lv_img_create(cont);
    lv_img_set_src(img, &weather_cloudy);
    lv_obj_center(img);
    label = lv_label_create(cont);
    lv_label_set_text(label, "多云");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);
    weatherView.label_day_one_img = img;
    weatherView.label_day_one_text = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 65, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 14, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "12~22°");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 5, 0);
    weatherView.label_day_one_temp = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 86, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "20%");
    lv_obj_add_style(label, &style_font_12, 0);
    lv_obj_center(label);
    weatherView.label_day_one_hum = label;
    
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_FOCUSED, tv);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_CLICKED, tv);
    lv_group_add_obj(group, btn);

   // 明天天气磁贴
    tile = lv_tileview_add_tile(tv, 0, 1, LV_DIR_VER);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(tile, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 90);
    lv_obj_set_align(cont, LV_ALIGN_TOP_MID);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "2022-02-02");
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 2);
    weatherView.label_day_two_date = label;
    img = lv_img_create(cont);
    lv_img_set_src(img, &weather_sun);
    lv_obj_center(img);
    label = lv_label_create(cont);
    lv_label_set_text(label, "晴");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);
    weatherView.label_day_two_img = img;
    weatherView.label_day_two_text = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 65, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 14, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "12~22°");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 5, 0);
    weatherView.label_day_two_temp = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 86, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "20%");
    lv_obj_add_style(label, &style_font_12, 0);
    lv_obj_center(label);
    weatherView.label_day_two_hum = label;
    
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_FOCUSED, tv);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_CLICKED, tv);
    lv_group_add_obj(group, btn);

    // 后天天气磁贴
    tile = lv_tileview_add_tile(tv, 0, 2, LV_DIR_TOP);
    lv_obj_set_size(tile, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(tile, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 100, 90);
    lv_obj_set_align(cont, LV_ALIGN_TOP_MID);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "2022-02-03");
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 2);
    weatherView.label_day_three_date = label;
    img = lv_img_create(cont);
    lv_img_set_src(img, &weather_rain);
    lv_obj_center(img);
    label = lv_label_create(cont);
    lv_label_set_text(label, "阵雨");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);
    weatherView.label_day_three_img = img;
    weatherView.label_day_three_text = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 65, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 14, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "12~22°");
    lv_obj_add_style(label, &style_font_14, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 5, 0);
    weatherView.label_day_three_temp = label;
    cont = lv_obj_create(tile);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 28, 20);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_LEFT, 86, -10);
    lv_obj_add_style(cont, &style_bg_grey, 0);
    label = lv_label_create(cont);
    lv_label_set_text(label, "20%");
    lv_obj_add_style(label, &style_font_12, 0);
    lv_obj_center(label);
    weatherView.label_day_three_hum = label;
    
    btn = lv_btn_create(tile);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 1, 1);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_FOCUSED, tv);
    lv_obj_add_event_cb(btn, WeatherMenu_Btn_Event, LV_EVENT_CLICKED, tv);
    lv_group_add_obj(group, btn);

    NOW_PAGE = WeatherMenu_Page;

    weatherView.cont = tv;
    lv_scr_load_anim(tv, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);


    // else
    // {
        start_time = millis();
        lv_timer_create(WeatherMenu_Update, 100, NULL);
    // }
}