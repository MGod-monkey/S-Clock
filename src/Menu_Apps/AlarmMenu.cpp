#include "Menu/Menu_Apps.h"
#include "ESP/ESP_Save.h"
#include "ESP/ESP_Key.h"


static void AlarmMenu_Choose_Weekday(void);
static void AlarmMenu_Check_Event(lv_event_t * e);
static void AlarmMenu_Roller_Event(lv_event_t* e);
static void AlarmMenu_DropDown_Event(lv_event_t* e);
static void AlarmMenu_Add_Item(lv_obj_t* list, uint8_t index);
static void AlarmMenu_Float_Check_Event(lv_event_t * e);
static void AlarmMenu_Choose_Weekday_Event(lv_event_t* e);
static void AlarmMenu_Setting_Page(void);
static uint8_t choose_days, select_index;
static lv_obj_t* list;

static void AlarmMenu_Float_Check_Event(lv_event_t * e)
{
    lv_obj_t* obj = (lv_obj_t*)lv_event_get_user_data(e);
    uint8_t child_cnt = lv_obj_get_child_cnt(obj);
    if (child_cnt <= 4)
    {
        AlarmMenu_Add_Item(obj, child_cnt);
        Alarm_addAlarmNum();
    }
}

static void AlarmMenu_Check_Event(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    uint8_t index = lv_obj_get_child_id(obj);
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        Alarm_Info_t[index].isOpen?Alarm_Close(index):Alarm_Open(index);
        lv_obj_t* sw = lv_obj_get_child(obj, 2);
        Alarm_Info_t[index].isOpen?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    } else if (code == LV_EVENT_LONG_PRESSED)
    {
        select_index = index;
        AlarmMenu_Setting_Page();
    }
}

static void AlarmMenu_Roller_Event(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    static int16_t mask_top_id = -1;
    static int16_t mask_bottom_id = -1;

    if (code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
        lv_coord_t font_h = lv_font_get_line_height(font);

        lv_area_t roller_coords;
        lv_obj_get_coords(obj, &roller_coords);

        lv_area_t rect_area;
        rect_area.x1 = roller_coords.x1;
        rect_area.x2 = roller_coords.x2;
        rect_area.y1 = roller_coords.y1;
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;

        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;
        rect_area.y2 = roller_coords.y2;

        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);

    } else if (code == LV_EVENT_DRAW_POST_END) {
        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)lv_draw_mask_remove_id(mask_top_id);
        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)lv_draw_mask_remove_id(mask_bottom_id);
        lv_draw_mask_free_param(fade_mask_top);
        lv_draw_mask_free_param(fade_mask_bottom);
        lv_mem_buf_release(fade_mask_top);
        lv_mem_buf_release(fade_mask_bottom);
        mask_top_id = -1;
        mask_bottom_id = -1;
    } else if (code == LV_EVENT_VALUE_CHANGED){
        uint8_t index = lv_obj_get_child_id(obj);
        uint8_t value = (uint8_t)lv_roller_get_selected(obj);
        if (index == 0)
            Alarm_setTime(select_index, value, 0);
        else 
            Alarm_setTime(select_index, 0, value);
    } else if (code == LV_EVENT_FOCUSED)
        lv_obj_scroll_to_view(lv_obj_get_parent(obj), LV_ANIM_ON);
}

static void AlarmMenu_Choose_Weekday_Event(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    uint8_t index = lv_btnmatrix_get_selected_btn(obj);
    if (index <= 6)
        if ((choose_days&(0x01<<index)) == (0x01<<index))
            choose_days &= ~(0x01<<index);
        else
            choose_days |= (0x01<<index);
    else
    {
        Alarm_setFreqMode(select_index, ALARM_FREQ_WEEKDAY, choose_days);
        lv_group_t* group = lv_group_get_default();
        lv_indev_set_group(indev_encoder, group);
        lv_obj_del_async(lv_obj_get_parent(obj));
    }
}

void AlarmMenu_Update(void)
{
    lv_obj_t* btn, *label, *sw;
    for (uint8_t i=0; i<Alarm_Info.alarm_num; i++)
    {
        btn = lv_obj_get_child(list, i);
        label = lv_obj_get_child(btn, 0);
        char buffer[] = "hh:mm";
        lv_label_set_text_fmt(label, "%s", Alarm_toString(i, buffer));
        label = lv_obj_get_child(btn, 1);
        lv_label_set_text_fmt(label, freqMode_Zh[Alarm_Info_t[i].freq_mode]);
        sw = lv_obj_get_child(btn, 2);
        Alarm_Info_t[i].isOpen?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
}

void AlarmMenu_Add_Item(lv_obj_t* list, uint8_t index)
{
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_width(&style_btn, LV_PCT(90));
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x262626));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_shadow_width(&style_btn, 0);

    lv_obj_t* btn = lv_btn_create(list);
    lv_obj_add_style(btn, &style_btn, 0);
    lv_group_add_obj(lv_group_get_default(), btn);
    lv_obj_add_event_cb(btn, AlarmMenu_Check_Event, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_event_cb(btn, AlarmMenu_Check_Event, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* label_time = lv_label_create(btn);
    lv_obj_t* label_freq = lv_label_create(btn);
    lv_obj_t* sw = lv_switch_create(btn);
    lv_obj_align(label_time, LV_ALIGN_TOP_LEFT, 0, -4);
    lv_obj_align(label_freq, LV_ALIGN_BOTTOM_LEFT, 0, 4);
    lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_color(label_time, lv_color_white(), 0);
    lv_obj_set_style_text_color(label_freq, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_set_style_text_font(label_freq, &zh_cn_jshaoer_12, 0);
    lv_obj_set_size(sw, 32, 20);
    lv_obj_add_state(sw, LV_STATE_DISABLED);
    Alarm_Info_t[index].isOpen?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    char buffer[] = "hh:mm";
    lv_label_set_text_fmt(label_time, "%s", Alarm_toString(index, buffer));
    lv_label_set_text_fmt(label_freq, freqMode_Zh[Alarm_Info_t[index].freq_mode]);
}

static void AlarmMenu_DropDown_Event(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    char buf[20];
    lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
    uint8_t freq_mode=0;
    if (!strcmp(buf, freqMode_Zh[0]))
        freq_mode = ALARM_FREQ_EVERYDAY;
    else if (!strcmp(buf, freqMode_Zh[1]))
        freq_mode = ALARM_FREQ_ONCE;
    else if (!strcmp(buf, freqMode_Zh[2]))
        freq_mode = ALARM_FREQ_WORKDAY;
    else if (!strcmp(buf, freqMode_Zh[3]))
    {
        freq_mode = ALARM_FREQ_WEEKDAY;
        AlarmMenu_Choose_Weekday();
    }
    Alarm_setFreqMode(select_index, freq_mode, 0);
}

// static void AlarmMenu_Switch_Event(lv_event_t* e)
// {
//     lv_obj_t* obj = (lv_obj_t*)lv_event_get_user_data(e);
//     uint8_t index = lv_obj_get_child_id(obj);
//     obj = lv_event_get_target(e);
//     // lv_obj_has_state(obj, LV_STATE_CHECKED)?Alarm_openSleepMode(index):Alarm_Close_SleepMode(index);
// }

static void AlarmMenu_Choose_Weekday(void)
{
    lv_obj_t* cont = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_PCT(90), LV_PCT(20));
    lv_obj_center(cont);
    choose_days = 0;

    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_clip_corner(&style_bg, true);
    lv_style_set_radius(&style_bg, LV_RADIUS_CIRCLE);
    lv_style_set_border_width(&style_bg, 0);

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 0);
    lv_style_set_border_width(&style_btn, 0);
    lv_style_set_border_opa(&style_btn, LV_OPA_50);
    lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_12);
    lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_INTERNAL);
    lv_style_set_radius(&style_btn, 0);

    static const char *map[] = {"日", "一", "二", "三", "四", "五", "六", ">", ""};

    lv_obj_t * btnm = lv_btnmatrix_create(cont);
    lv_btnmatrix_set_map(btnm, map);
    lv_obj_add_style(btnm, &style_bg, 0);
    lv_obj_add_style(btnm, &style_btn, LV_PART_ITEMS);
    lv_obj_add_event_cb(btnm, AlarmMenu_Choose_Weekday_Event, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(btnm, LV_PCT(100), LV_PCT(100));

    lv_btnmatrix_set_btn_ctrl_all(btnm, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_clear_btn_ctrl(btnm, 7, LV_BTNMATRIX_CTRL_CHECKABLE);

    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, btnm);
    lv_group_focus_obj(btnm);
    lv_indev_set_group(indev_encoder, group);
}

static void AlarmMenu_Back_Event(lv_event_t* e)
{
    Load_AlarmMenu();
}

void AlarmMenu_Setting_Page(void)
{
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(cont, LV_SCROLL_SNAP_START);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t* cont_page_1 = lv_obj_create(cont);
    lv_obj_t* cont_page_2 = lv_obj_create(cont);
    lv_obj_remove_style_all(cont_page_1);
    lv_obj_remove_style_all(cont_page_2);
    lv_obj_set_size(cont_page_1, LV_PCT(100), LV_PCT(100));
    lv_obj_set_size(cont_page_2, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(cont_page_2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont_page_2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    
    lv_obj_t* alarm_hour, * alarm_minute;
    // 小时列表
    alarm_hour = lv_roller_create(cont_page_1);
    lv_obj_set_size(alarm_hour, LV_PCT(30), LV_PCT(80));
    lv_obj_align(alarm_hour, LV_ALIGN_CENTER, -30, 0);
    lv_obj_set_style_bg_color(alarm_hour, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(alarm_hour, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(alarm_hour, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(alarm_hour, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(alarm_hour, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(alarm_hour, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(alarm_hour,
                        "0\n""1\n""2\n""3\n""4\n""5\n""6\n"
                        "7\n""8\n""9\n""10\n""11\n""12\n"
                        "13\n""14\n""15\n""16\n""17\n""18\n""19\n"
                        "20\n""21\n""22\n""23",
                        LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(alarm_hour, 3);
    lv_obj_add_event_cb(alarm_hour, AlarmMenu_Roller_Event, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(alarm_hour, Alarm_Info_t[select_index].hour, LV_ANIM_OFF);
    // 分钟列表
    alarm_minute = lv_roller_create(cont_page_1);
    lv_obj_set_size(alarm_minute, LV_PCT(30), LV_PCT(80));
    lv_obj_align(alarm_minute, LV_ALIGN_CENTER, 30, 0);
    lv_obj_set_style_bg_color(alarm_minute, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(alarm_minute, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(alarm_minute, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(alarm_minute, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(alarm_minute, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(alarm_minute, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(alarm_minute,
                        "0\n""1\n""2\n""3\n""4\n""5\n""6\n"
                        "7\n""8\n""9\n""10\n""11\n""12\n"
                        "13\n""14\n""15\n""16\n""17\n""18\n""19\n"
                        "20\n""21\n""22\n""23\n""24\n""25\n""26\n"
                        "28\n""29\n""30\n""31\n""32\n""33\n""34\n"
                        "35\n""36\n""37\n""38\n""39\n""40\n""41\n"
                        "42\n""43\n""44\n""45\n""46\n""47\n""48\n"
                        "49\n""50\n""51\n""52\n""53\n""54\n""55\n"
                        "56\n""57\n""58\n""59",
                        LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(alarm_minute, 3);
    lv_obj_add_event_cb(alarm_minute, AlarmMenu_Roller_Event, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(alarm_minute, Alarm_Info_t[select_index].minute, LV_ANIM_OFF);
    // 中间的冒号
    lv_obj_t* label_sign = lv_label_create(cont);
    lv_obj_set_style_text_color(label_sign, lv_color_white(), 0);
    lv_label_set_text(label_sign, ":");
    lv_obj_center(label_sign);
    
    lv_obj_t* cont1;
    lv_obj_t* label_tip;
    // 模式选择
    cont1 = lv_obj_create(cont_page_2);
    lv_obj_set_size(cont1, LV_PCT(100), LV_PCT(45));
    lv_obj_set_style_border_width(cont1, 0, 0);
    lv_obj_set_style_bg_opa(cont1, LV_OPA_COVER, 0);
    lv_obj_set_scrollbar_mode(cont1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cont1, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    label_tip = lv_label_create(cont1);
    lv_label_set_text(label_tip, "模式");
    lv_obj_align(label_tip, LV_ALIGN_LEFT_MID, -5, 0);
    lv_obj_set_style_text_font(label_tip, &zh_cn_jshaoer_14, 0);
    lv_obj_t* dropdown = lv_dropdown_create(cont1);
    lv_obj_set_size(dropdown, LV_PCT(70), LV_PCT(100));
    lv_obj_set_style_border_width(dropdown, 0, 0);
    lv_obj_align(dropdown, LV_ALIGN_RIGHT_MID, 5, 0);
    lv_obj_set_style_text_font(dropdown, &zh_cn_jshaoer_12, 0);
    lv_obj_t* list = lv_dropdown_get_list(dropdown);
    lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(list, &zh_cn_jshaoer_12, 0);
    lv_dropdown_set_options(dropdown, 
                        "每天\n""单次\n""工作日\n""选定星期");
    lv_dropdown_set_selected(dropdown, Alarm_Info_t[select_index].freq_mode);
    lv_obj_add_event_cb(dropdown, AlarmMenu_DropDown_Event, LV_EVENT_VALUE_CHANGED, NULL);
    // // 贪睡开关
    // cont1 = lv_obj_create(cont_page_2);
    // lv_obj_set_size(cont1, LV_PCT(100), LV_PCT(45));
    // lv_obj_set_style_border_width(cont1, 0, 0);
    // lv_obj_set_style_bg_opa(cont1, LV_OPA_COVER, 0);
    // lv_obj_set_scrollbar_mode(cont1, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_style_bg_color(cont1, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    // label_tip = lv_label_create(cont1);
    // lv_label_set_text(label_tip, "开启贪睡");
    // lv_obj_align(label_tip, LV_ALIGN_LEFT_MID, -5, 0);
    // lv_obj_set_style_text_font(label_tip, &zh_cn_jshaoer_14, 0);
    // lv_obj_t* sw = lv_switch_create(cont1);
    // lv_obj_set_size(sw, 40, 24);
    // lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 5, 0);
    // lv_obj_add_event_cb(sw, AlarmMenu_Switch_Event, LV_EVENT_CLICKED, NULL);
    // Alarm_Info_t[select_index].sleep_mode?lv_obj_add_state(sw, LV_STATE_CHECKED):lv_obj_clear_state(sw, LV_STATE_CHECKED);
    // 退出按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn_back, AlarmMenu_Back_Event, LV_EVENT_FOCUSED, NULL);

    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, alarm_hour);
    lv_group_add_obj(group, alarm_minute);
    lv_group_add_obj(group, dropdown);
    // lv_group_add_obj(group, sw);
    lv_group_add_obj(group, btn_back);
    lv_group_focus_obj(alarm_hour);

    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, true);
}

void Load_AlarmMenu(void)
{
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_center(cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    static lv_style_t style_list_main;
    lv_style_init(&style_list_main);
    lv_style_set_align(&style_list_main, LV_ALIGN_CENTER);
    lv_style_set_flex_flow(&style_list_main, LV_FLEX_FLOW_COLUMN);
    lv_style_set_bg_color(&style_list_main, lv_color_black());
    lv_style_set_bg_opa(&style_list_main, LV_OPA_COVER);
    lv_style_set_pad_row(&style_list_main, 5);
    
    list = lv_list_create(cont);
    lv_obj_remove_style_all(list);
    lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(list, 0, 0);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(list, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scroll_snap_y(list, LV_SCROLL_SNAP_CENTER);
    lv_obj_add_style(list, &style_list_main, 0);
    // 悬浮按钮
    lv_obj_t* btn_float = lv_btn_create(cont);
    lv_obj_set_size(btn_float, 20, 20);
    lv_obj_add_flag(btn_float, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(btn_float, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
    lv_obj_add_event_cb(btn_float, AlarmMenu_Float_Check_Event, LV_EVENT_CLICKED, list);
    lv_obj_set_style_radius(btn_float, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(btn_float, LV_SYMBOL_PLUS, 0);
    lv_obj_set_style_text_font(btn_float, lv_theme_get_font_large(btn_float), 0);
    lv_obj_set_style_text_color(btn_float, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 1), 0);
    // 退出按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, btn_float);
    lv_group_add_obj(group, btn_back);
    for (uint8_t i=0;i<Alarm_Info.alarm_num;i++)
        AlarmMenu_Add_Item(list, i);
    lv_group_focus_obj(btn_back);
    NOW_PAGE = AlarmMenu_Page;
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}