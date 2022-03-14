#include "Menu/Menu_Apps.h"
#include "ESP/ESP_WiFi.h"
#include "ESP/ESP_Save.h"
#include "Lightness.h"

static void ToolboxMenu_Network_Btn_Event(lv_event_t* e);
static void ToolboxMenu_Network_Update(lv_timer_t* timer);
static void ToolboxMenu_Network_Btn_Event2(lv_event_t* e);
static uint32_t start_time;
static uint8_t last_lightness;

static void ToolboxMenu_Network_Btn_Event(lv_event_t* e)
{
    lv_obj_t * mbox = lv_event_get_current_target(e);
    const char* btn_text = lv_msgbox_get_active_btn_text(mbox);
    // lv_timer_t* timer = (lv_timer_t*)lv_event_get_user_data(e);
    if (!strcmp(btn_text, "重试"))
    {
        start_time = millis();
        View_Close_Top_Objs();
    } else if (!strcmp(btn_text, "退出"))
    {
        // lv_timer_del(timer);
        View_Close_All_Top_Objs();
    }
}

static void ToolboxMenu_Network_Btn_Event2(lv_event_t* e)
{

    lv_timer_t* timer = (lv_timer_t*)lv_event_get_user_data(e);
    lv_timer_del(timer);
    View_Close_All_Top_Objs();
}

static void ToolboxMenu_Flashlight_Btn_Event(lv_event_t* e)
{
    View_Close_All_Top_Objs();
    Lightness_setNum(last_lightness);
}

static void ToolboxMenu_NTPTime_Btn_Event(lv_event_t* e)
{
    lv_obj_t * mbox = lv_event_get_current_target(e);
    const char* btn_text = lv_msgbox_get_active_btn_text(mbox);
    if (!strcmp(btn_text, "去联网"))
    {
        View_Close_All_Top_Objs();
        Load_ToolboxMenu_Network();
    } else if (!strcmp(btn_text, "返回"))
        View_Close_All_Top_Objs();
}

static void ToolboxMenu_Network_Update(lv_timer_t* timer)
{
    if (ESPWifi_smartConfigStatus() && Wifi_Info.smartconfig_status != WF_CONNECTED)
    {
        Wifi_Info.smartconfig_status = WF_CONNECTED;
        Wifi_Info.wifi_status = WF_CONNECTING;
        View_Show_Messagebox("消息", "接收到配置信息,正在连接...");
        start_time = millis();
    }
    else if (ESPWifi_Status())
    {
        lv_timer_del(timer);
        ESPSave_updateConfig(SAVE_CMD_WIFI);
        static const char *btns[] = {"退出", ""};
        View_Show_Messagebox("消息", "成功连接上Wifi!", btns, ToolboxMenu_Network_Btn_Event);
    }
    else if (millis() - start_time >= WIFI_CONNECT_TIMEOUT && Wifi_Info.smartconfig_status == WF_CONNECTED)
    {
        lv_timer_del(timer);
        ESPWifi_stopSmartConfig();
        static const char *btns[] = {"重试","退出", ""};
        View_Show_Messagebox("提示", "Wifi连接超时...", btns, ToolboxMenu_Network_Btn_Event);
    }
    else if (millis() - start_time >= WIFI_SMARTCONFIG_TIMEOUT)
    {
        lv_timer_del(timer);
        ESPWifi_stopSmartConfig();
        static const char *btns[] = {"重试","退出", ""};
        View_Show_Messagebox("提示", "接收配置超时...", btns, ToolboxMenu_Network_Btn_Event);
    }
}


void Load_ToolboxMenu_Flashlight(void)
{
    lv_obj_t* cont = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_center(cont);

    //返回键
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn_back, ToolboxMenu_Flashlight_Btn_Event, LV_EVENT_LONG_PRESSED, NULL);
    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, btn_back);
    lv_indev_set_group(indev_encoder, group);

    last_lightness = Lightness_getNum();
    Lightness_setMax();
}

void Load_ToolboxMenu_Network(void)
{
    lv_timer_t* update_timer = lv_timer_create(ToolboxMenu_Network_Update, 100, NULL);
    lv_obj_t *cont = lv_obj_create(lv_layer_top());
    lv_obj_t *btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn_back, ToolboxMenu_Network_Btn_Event2, LV_EVENT_LONG_PRESSED, update_timer);

    lv_obj_t *img = lv_img_create(cont);
    lv_img_set_src(img, &qrcode);
    lv_obj_center(img);

    lv_group_t* group = lv_group_create();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, btn_back);
    lv_indev_set_group(indev_encoder, group);

    ESPWifi_startSmartConfig();
    start_time = millis();
}

void ToolboxMenu_NTPTime(void)
{
    View_Close_All_Top_Objs();
    if (Wifi_Info.wifi_status != WF_CONNECTED)
    {
        static const char *btns[] = {"去联网","返回", ""};
        View_Show_Messagebox("提示", "网络未连接!", btns, ToolboxMenu_NTPTime_Btn_Event);
    }
    else 
    {
        if (ESPWifi_setNTPTime())
            View_Show_Messagebox("消息", "成功同步网络时间!", 1500);
        else
            View_Show_Messagebox("消息", "同步失败,请检查网络后再试!", 2000);
    }
}


static void ToolboxMenu_addItem(lv_obj_t* list, lv_event_cb_t event_cb,const void* img_src, const char* text)
{
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    //lv_style_set_flex_main_place(&style_btn, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_cross_place(&style_btn, LV_FLEX_ALIGN_CENTER);
    lv_style_set_width(&style_btn, LV_PCT(100));
    lv_style_set_border_width(&style_btn, 0);
    lv_style_set_pad_ver(&style_btn, 2);
    lv_style_set_pad_hor(&style_btn, 10);
    lv_style_set_text_color(&style_btn, lv_color_white());
    lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_14);
    lv_style_set_text_align(&style_btn, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x252526));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);

    static lv_style_t style_btn_focus;
    lv_style_init(&style_btn_focus);
    lv_style_set_bg_color(&style_btn_focus, lv_color_hex(0x3e3e42));
    lv_style_set_bg_opa(&style_btn_focus, LV_OPA_COVER);

    lv_obj_t *btn = lv_btn_create(list);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(btn, LV_FLEX_FLOW_ROW);
    lv_obj_t * img = lv_img_create(btn);
    lv_img_set_src(img, img_src);
    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_flex_grow(label, 1);

    // lv_obj_t* btn = lv_list_add_btn(list, (const char*)img_src, text);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_set_content_width(btn, LV_PCT(100));
    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_style(btn, &style_btn_focus, LV_STATE_FOCUSED);
    lv_group_t* group = lv_group_get_default();
    lv_group_add_obj(group, btn);
}

void Load_ToolboxMenu(void)
{
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);

    lv_obj_t* cont_header = lv_obj_create(cont);
    lv_obj_remove_style_all(cont_header);
    lv_obj_set_size(cont_header, 116, 20);
    lv_obj_set_style_radius(cont_header, 4, 0);
    lv_obj_set_style_align(cont_header, LV_ALIGN_TOP_MID, 0);
    lv_obj_set_style_text_color(cont, lv_color_white(), 0);
    lv_obj_set_style_text_font(cont, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_bg_color(cont_header, lv_color_hex(0x3e3e42), 0);
    lv_obj_set_style_bg_opa(cont_header, LV_OPA_COVER, 0);
    lv_obj_t* label = lv_label_create(cont_header);
    lv_label_set_text(label, "工具箱");
    lv_obj_center(label);

    lv_obj_t* list = lv_list_create(cont);
    lv_obj_set_style_border_width(list, 0, 0);
    lv_obj_set_style_radius(list, 4, 0);
    lv_obj_set_size(list, 116, 108);
    lv_obj_set_style_bg_color(list, lv_color_hex(0x252526), 0);
    lv_obj_set_style_bg_opa(list, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_ver(list, 10, 0);
    lv_obj_set_style_pad_hor(list, 0, 0);
    // lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_align_to(list, cont_header, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    static const lv_style_prop_t props[] = { LV_STYLE_BG_OPA, LV_STYLE_WIDTH, LV_STYLE_PROP_INV };
    static lv_style_transition_dsc_t trans;
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 200, 0, NULL);
    static lv_style_t style_scroll;
    lv_style_init(&style_scroll);
    lv_style_set_width(&style_scroll, 4);      
    lv_style_set_pad_right(&style_scroll, 2);
    lv_style_set_pad_top(&style_scroll, 22);
    lv_style_set_radius(&style_scroll, 2);
    lv_style_set_bg_opa(&style_scroll, LV_OPA_80);
    lv_style_set_bg_color(&style_scroll, lv_color_hex(0x3e3e42));
    lv_style_set_shadow_width(&style_scroll, 8);
    lv_style_set_shadow_spread(&style_scroll, 2);
    lv_style_set_shadow_color(&style_scroll, lv_color_hex(0x686868));
    lv_style_set_transition(&style_scroll, &trans);

    static lv_style_t style_scrolled;
    lv_style_init(&style_scrolled);
    lv_style_set_width(&style_scrolled, 6);
    lv_style_set_bg_opa(&style_scrolled, LV_OPA_COVER);
    lv_obj_add_style(list, &style_scroll, LV_PART_SCROLLBAR);
    lv_obj_add_style(list, &style_scrolled, LV_PART_SCROLLBAR | LV_STATE_SCROLLED);
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    ToolboxMenu_addItem(list, (lv_event_cb_t)Load_ToolboxMenu_Network, &icon_network, "配网");
    ToolboxMenu_addItem(list, (lv_event_cb_t)Load_ToolboxMenu_Flashlight, &icon_flashLED, "手电筒");
    ToolboxMenu_addItem(list, (lv_event_cb_t)ToolboxMenu_NTPTime, &icon_ntptime, "NTP校时");

    // 退出按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    lv_group_add_obj(group, btn_back);
    lv_group_focus_obj(btn_back);

    NOW_PAGE = ToolboxMenu_Page;
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 500, true);
}