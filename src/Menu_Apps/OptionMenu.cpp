#include "View.h"
#include "Alarm.h"
#include "Weather.h"
#include "Debug.h"
#include "Clock.h"
#include "globalConfig.h"
#include "Menu/Menu_Apps.h"
#include "ESP/ESP_BLE.h"
#include "ESP/ESP_WiFi.h"
#include "ESP/ESP_Save.h"
#include "ESP/ESP_Sleep.h"

#define VERSION    "1.5"

static void OptionMenu_Btns_Event(lv_event_t* e);
static void OptionMenu_CLICKE_Event(lv_event_t* e);
static void OptionMenu_CLICKE_Event2(lv_event_t* e);
static void OptionMenu_Show_AboutInfo(lv_event_t* e);
static void OptionMenu_Show_NetworkInfo(lv_event_t* e);

static void OptionMenu_CLICKE_Event(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    // lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    uint8_t index = lv_obj_get_child_id(obj);
    switch (index)
    {
        case 0:
            BLE_Info.ble_adv?BLE_closeAdvert():BLE_openAdvert();
            BLE_Info.ble_adv?lv_obj_add_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED):lv_obj_clear_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED);
            ESPSave_updateConfig(SAVE_CMD_BLE);
            break;
        // case 1:
        //     Wifi_Info.wifi_status==WF_CLOSE?ESPWifi_Open():ESPWifi_Close();
        //     Wifi_Info.wifi_status!=WF_CLOSE?lv_obj_add_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED):lv_obj_clear_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED);
        //     break;
        case 1:
            Alarm_Info.sleep_mode?Alarm_closeSleepMode():Alarm_openSleepMode();
            Alarm_Info.sleep_mode?lv_obj_add_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED):lv_obj_clear_state(lv_obj_get_child(obj, 1), LV_STATE_CHECKED);
            ESPSave_updateConfig(SAVE_CMD_SLEEP_MODE);
            break;
        case 2:            
            View_Show_Messagebox("消息", "天气服务来自于心知天气免费接口", 2000);
            break;
        case 3:
            ESPSleep_changeSleepMode();
            lv_label_set_text(lv_obj_get_child(obj, 1), ESPSleep_getSleepMode());
            ESPSave_updateConfig(SAVE_CMD_XIU_MODE);
            break;
        case 4:
            ESPSleep_setSleepTime((ESPSleep_Info.sleep_max_timer+10)%70);
            if (ESPSleep_Info.sleep_max_timer!=0)
                lv_label_set_text_fmt(lv_obj_get_child(obj, 1), "%ds", ESPSleep_Info.sleep_max_timer);
            else  
                lv_label_set_text(lv_obj_get_child(obj, 1), "不息屏");
            ESPSave_updateConfig(SAVE_CMD_SLEEP_TIMER);         
            break;
        // case 5:
        //     if (Wifi_Info.wifi_status != WF_CONNECTED)
        //     {
        //         static const char *btns[] = {"去联网","返回", ""};
        //         View_Show_Messagebox("提示", "网络未连接!", btns, OptionMenu_Btns_Event);
        //     }
        //     else 
        //     {
        //         if (ESPWifi_setNTPTime())
        //             View_Show_Messagebox("消息", "成功同步网络时间!", 1500);
        //         else
        //             View_Show_Messagebox("消息", "同步失败,请检查网络后再试!", 2000);
        //     }
        //     break;
        case 5:
            View_Show_Messagebox("提示", "OTA更新仅支持内存大小超过4M版本!", 2000);
            break;
        case 8:
            static const char *btns[] = {"是","否", ""};
            View_Show_Messagebox("提示", "是否恢复出厂设置?", btns, OptionMenu_Btns_Event);
            break;
        case 9:
            ESP.restart();
            break;
        default:
            Item_Back_Menu(nullptr);
            break;
    }
}

static void OptionMenu_CLICKE_Event2(lv_event_t* e)
{
    lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cont);
    lv_anim_set_values(&a, lv_obj_get_x(cont), 0);
    lv_anim_set_time(&a, 800);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_start(&a);
    lv_obj_t* cont_info = lv_obj_get_parent(lv_obj_get_parent(lv_event_get_target(e)));

    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, cont_info);
    lv_anim_set_values(&b, 0, TFT_WIDTH);
    lv_anim_set_time(&b, 800);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&b, lv_anim_path_ease_in);
    lv_anim_start(&b);
    lv_obj_del_delayed(cont_info, 800);
    lv_indev_set_group(indev_encoder, lv_group_get_default());;
}

static void OptionMenu_Btns_Event(lv_event_t* e)
{
    lv_obj_t * mbox = lv_event_get_current_target(e);
    const char* btn_text = lv_msgbox_get_active_btn_text(mbox);
    if (!strcmp(btn_text, "去联网"))
    {
        View_Close_All_Top_Objs();
        Load_ToolboxMenu_Network();
    } else if (!strcmp(btn_text, "返回"))
    {
        View_Close_All_Top_Objs();
    } else if (!strcmp(btn_text, "是"))
    {
        ESPSave_resetConfig();
        ESP.restart();
    }
}

static void OptionMenu_Show_AboutInfo(lv_event_t* e)
{
    lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cont);
    lv_anim_set_values(&a, lv_obj_get_x(cont), -TFT_WIDTH);
    lv_anim_set_time(&a, 800);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_start(&a);

    lv_obj_t* cont_info = lv_obj_create(lv_obj_get_parent(cont));
    lv_obj_remove_style_all(cont_info);
    lv_obj_set_x(cont_info, TFT_WIDTH);
    lv_obj_set_size(cont_info, LV_PCT(100), LV_PCT(100));
    lv_obj_t* header, * body, * img, * label;
    header = lv_obj_create(cont_info);
    lv_obj_remove_style_all(header);
    lv_obj_set_size(header, LV_PCT(100), LV_PCT(16));
    lv_obj_set_style_bg_color(header, lv_color_hex(0x9B9B9B), 0);
    lv_obj_set_style_bg_opa(header, LV_OPA_50, 0);
    lv_obj_set_align(header, LV_ALIGN_TOP_MID);
    img = lv_img_create(header);
    lv_img_set_src(img, &icon_back);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 4, 0);
    lv_obj_add_event_cb(img, OptionMenu_CLICKE_Event2, LV_EVENT_SHORT_CLICKED, cont);
    lv_obj_set_style_radius(img, LV_RADIUS_CIRCLE, LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(img, 2, LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(img, lv_color_hex(0x9B9B9B), LV_STATE_FOCUSED);
    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, img);
    lv_group_focus_obj(img);
    lv_group_set_editing(group, true);
    lv_indev_set_group(indev_encoder, group);
    label = lv_label_create(header);
    lv_obj_set_style_text_font(label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "关  于");
    lv_obj_center(label);
    body = lv_obj_create(cont_info);
    lv_obj_remove_style_all(body);
    lv_obj_set_style_text_font(body, &zh_cn_jshaoer_14, 0);
    lv_obj_set_flex_flow(body, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(body, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(body, LV_PCT(100), LV_PCT(84));
    lv_obj_set_align(body, LV_ALIGN_BOTTOM_MID);
    label = lv_label_create(body);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text_fmt(label, "Runtime: %s", Clock_getRuntime(lv_tick_get()));
    label = lv_label_create(body);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text_fmt(label, "Version: %s", VERSION);
    // lv_obj_center(label);

    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, cont_info);
    lv_anim_set_values(&b, TFT_WIDTH, 0);
    lv_anim_set_time(&b, 800);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&b, lv_anim_path_ease_in);
    lv_anim_start(&b);
}

void OptionMenu_Show_NetworkInfo(lv_event_t* e)
{
    lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cont);
    lv_anim_set_values(&a, lv_obj_get_x(cont), -TFT_WIDTH);
    lv_anim_set_time(&a, 800);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_start(&a);

    lv_obj_t* cont_info = lv_obj_create(lv_obj_get_parent(cont));
    lv_obj_remove_style_all(cont_info);
    lv_obj_set_x(cont_info, TFT_WIDTH);
    lv_obj_set_size(cont_info, LV_PCT(100), LV_PCT(100));
    lv_obj_t* header, * body, * img, * cont_label, * label;
    header = lv_obj_create(cont_info);
    lv_obj_remove_style_all(header);
    lv_obj_set_size(header, LV_PCT(100), LV_PCT(16));
    lv_obj_set_style_bg_color(header, lv_color_hex(0x9B9B9B), 0);
    lv_obj_set_style_bg_opa(header, LV_OPA_50, 0);
    lv_obj_set_align(header, LV_ALIGN_TOP_MID);
    img = lv_img_create(header);
    lv_img_set_src(img, &icon_back);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 4, 0);
    lv_obj_add_event_cb(img, OptionMenu_CLICKE_Event2, LV_EVENT_CLICKED, cont);
    lv_obj_set_style_radius(img, LV_RADIUS_CIRCLE, LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(img, 2, LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(img, lv_color_hex(0x9B9B9B), LV_STATE_FOCUSED);
    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, img);
    lv_group_focus_obj(img);
    lv_group_set_editing(group, true);
    lv_indev_set_group(indev_encoder, group);
    label = lv_label_create(header);
    lv_obj_set_style_text_font(label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "联网信息");
    lv_obj_center(label);
    body = lv_obj_create(cont_info);
    lv_obj_remove_style_all(body);
    lv_obj_set_size(body, LV_PCT(100), LV_PCT(84));
    lv_obj_set_style_pad_all(body, 2, 0);
    lv_obj_set_align(body, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(body, LV_FLEX_FLOW_COLUMN);
    
    cont_label = lv_obj_create(body);
    lv_obj_remove_style_all(cont_label);
    lv_obj_set_size(cont_label, LV_PCT(100), LV_PCT(25));
    lv_obj_set_style_pad_hor(cont_label, 3, 0);
    lv_obj_set_style_pad_ver(cont_label, 2, 0);
    lv_obj_set_style_text_font(cont_label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(cont_label, lv_color_white(), 0);
    lv_obj_set_flex_flow(cont_label, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_cross_place(cont_label, LV_FLEX_ALIGN_CENTER, 0);
    label = lv_label_create(cont_label);
    lv_label_set_text(label, "LOCAL IP:");
    label = lv_label_create(cont_label);
    lv_label_set_text(label, ESPWifi_localIP());
    lv_obj_set_flex_grow(label, 1);

    cont_label = lv_obj_create(body);
    lv_obj_remove_style_all(cont_label);
    lv_obj_set_size(cont_label, LV_PCT(100), LV_PCT(25));
    lv_obj_set_style_pad_hor(cont_label, 3, 0);
    lv_obj_set_style_pad_ver(cont_label, 2, 0);
    lv_obj_set_style_text_font(cont_label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(cont_label, lv_color_white(), 0);
    lv_obj_set_flex_flow(cont_label, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_cross_place(cont_label, LV_FLEX_ALIGN_CENTER, 0);
    label = lv_label_create(cont_label);
    lv_label_set_text(label, "WIFI RSSI:");
    label = lv_label_create(cont_label);
    lv_label_set_text_fmt(label, "#ff0000 %d##ffffff dm#", ESPWifi_RSSI());
    lv_label_set_recolor(label, true);
    lv_obj_set_flex_grow(label, 1);

    cont_label = lv_obj_create(body);
    lv_obj_remove_style_all(cont_label);
    lv_obj_set_size(cont_label, LV_PCT(100), LV_PCT(25));
    lv_obj_set_style_pad_hor(cont_label, 3, 0);
    lv_obj_set_style_pad_ver(cont_label, 2, 0);
    lv_obj_set_style_text_font(cont_label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(cont_label, lv_color_white(), 0);
    lv_obj_set_flex_flow(cont_label, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_cross_place(cont_label, LV_FLEX_ALIGN_CENTER, 0);
    label = lv_label_create(cont_label);
    lv_label_set_text(label, "BLE NAME:");
    label = lv_label_create(cont_label);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(label, BLE_getDeviceName());
    lv_obj_set_flex_grow(label, 1);

    cont_label = lv_obj_create(body);
    lv_obj_remove_style_all(cont_label);
    lv_obj_set_size(cont_label, LV_PCT(100), LV_PCT(25));
    lv_obj_set_style_pad_hor(cont_label, 3, 0);
    lv_obj_set_style_pad_ver(cont_label, 2, 0);
    lv_obj_set_style_text_font(cont_label, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(cont_label, lv_color_white(), 0);
    lv_obj_set_flex_flow(cont_label, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_cross_place(cont_label, LV_FLEX_ALIGN_CENTER, 0);
    label = lv_label_create(cont_label);
    lv_label_set_text(label, "BLE ADDR:");
    label = lv_label_create(cont_label);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(label, BLE_getAddress());
    lv_obj_set_flex_grow(label, 1);

    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, cont_info);
    lv_anim_set_values(&b, TFT_WIDTH, 0);
    lv_anim_set_time(&b, 800);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&b, lv_anim_path_ease_in);
    lv_anim_start(&b);
}

static void OptionMenu_Scroll_Event(lv_event_t* e)
{
    lv_obj_t* cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++) {
        lv_obj_t* child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r) {
            x = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

void Load_OptionMenu(void)
{
    lv_obj_t* main_cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(main_cont);
    lv_obj_set_style_bg_img_src(main_cont, &bg_sky, 0);
    lv_obj_t* cont = lv_obj_create(main_cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(cont, LV_OPA_0, 0);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_event_cb(cont, OptionMenu_Scroll_Event, LV_EVENT_SCROLL, NULL);

    static lv_style_t style_btn, style_sw;
    lv_style_init(&style_btn);
    lv_style_init(&style_sw);
    lv_style_set_border_width(&style_btn, 0);
    lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_12);
    lv_style_set_text_color(&style_btn, lv_color_white());
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x495057));
    lv_style_set_bg_opa(&style_btn, LV_OPA_40);
    lv_style_set_width(&style_btn, LV_PCT(100));
    lv_style_set_shadow_width(&style_btn, 20);
    lv_style_set_shadow_ofs_y(&style_btn, 0);
    lv_style_set_shadow_color(&style_btn, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_bg_color(&style_sw, lv_palette_lighten(LV_PALETTE_GREEN, 1));
    lv_style_set_bg_opa(&style_sw, LV_OPA_50);


    lv_obj_t* btn, * label, * sw;
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    // 蓝牙广播设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "蓝牙广播");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -5, 0);
    sw = lv_switch_create(btn);
    lv_obj_set_size(sw, 30, 20);
    lv_obj_add_state(sw, LV_STATE_DISABLED);
    lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 5, 0);
    lv_obj_add_style(sw, &style_sw, LV_PART_INDICATOR);
    BLE_Info.ble_status!=BLE_CLOSE?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    // // Wifi设置
    // btn = lv_btn_create(cont);
    // lv_obj_add_style(btn, &style_btn, 0);
    // lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    // lv_group_add_obj(group, btn);
    // label = lv_label_create(btn);
    // lv_label_set_text(label, "WIFI");
    // lv_obj_set_style_text_font(label, &zh_cn_jshaoer_14, 0);
    // lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
    // sw = lv_switch_create(btn);
    // lv_obj_set_size(sw, 30, 20);
    // lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 5, 0);
    // lv_obj_add_state(sw, LV_STATE_DISABLED);
    // lv_obj_add_style(sw, &style_sw, LV_PART_INDICATOR);
    // Wifi_Info.wifi_status!=WF_CLOSE?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    // 贪睡模式设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "贪睡模式");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -5, 0);
    sw = lv_switch_create(btn);
    lv_obj_set_size(sw, 30, 20);
    lv_obj_add_state(sw, LV_STATE_DISABLED);
    lv_obj_add_style(sw, &style_sw, LV_PART_INDICATOR);
    lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 5, 0);
    Alarm_Info.sleep_mode?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    // 天气城市设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "天气城市");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -5, 0);
    label = lv_label_create(btn);
    lv_obj_set_width(label, LV_PCT(45));
    lv_label_set_text(label, Weather_Self_Info.city);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_font(label, &zh_cn_jshaoer_14, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 5, 0);
    // 休眠方式设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "休眠方式");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, -5, 0);
    label = lv_label_create(btn);
    lv_label_set_text(label, ESPSleep_getSleepMode());
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 5, 0); 
    lv_obj_set_style_bg_color(label, lv_color_hex(0x495057), 0);
    lv_obj_set_style_bg_opa(label, LV_OPA_60, 0);
    // 息屏时间设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_set_flex_flow(btn, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(btn, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "息屏时间");
    label = lv_label_create(btn);
    if (ESPSleep_Info.sleep_max_timer!=0)
        lv_label_set_text_fmt(label, "%ds", ESPSleep_Info.sleep_max_timer);
    else  
        lv_label_set_text(label, "不息屏");   
    lv_obj_set_style_text_font(label, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_bg_color(label, lv_color_hex(0x495057), 0);
    lv_obj_set_style_bg_opa(label, LV_OPA_60, 0);
    // OTA更新
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, cont);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "OTA更新");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 联网信息展示
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_Show_NetworkInfo, LV_EVENT_CLICKED, cont);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "联网信息");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 关于详情展示
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_Show_AboutInfo, LV_EVENT_CLICKED, cont);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "关 于");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 恢复出厂设置
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "恢复出厂");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 重启
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "重  启");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 返回
    btn = lv_btn_create(cont);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_event_cb(btn, OptionMenu_CLICKE_Event, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, btn);
    label = lv_label_create(btn);
    lv_label_set_text(label, "返  回");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_event_send(cont, LV_EVENT_SCROLL, NULL);
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
    lv_group_focus_obj(lv_obj_get_child(cont, 0));

    NOW_PAGE = OptionMenu_Page;
    lv_scr_load_anim(main_cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}