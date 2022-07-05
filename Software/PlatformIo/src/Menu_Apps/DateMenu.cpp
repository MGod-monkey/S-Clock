#include "Clock.h"
#include "Menu/Menu_Apps.h"

static uint16_t choose_year, choose_month;

static void DateMenu_Roller_Event(lv_event_t* e);
static void DateMenu_Back_Event(lv_event_t* e);
static void DateMenu_Show_Dalender(lv_event_t* e);

static void DateMenu_Roller_Event(lv_event_t* e)
{
    // lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    static char buffer[16];
    uint8_t index = lv_obj_get_child_id(obj);
    lv_roller_get_selected_str(obj, buffer, sizeof(buffer));
    if (index == 0)
        choose_year=atoi(buffer);
    else
        choose_month=atoi(buffer);

    // static int16_t mask_top_id = -1;
    // static int16_t mask_bottom_id = -1;
    // if (code == LV_EVENT_COVER_CHECK) {
    //     lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
    // } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
    //     /* add mask */
    //     const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
    //     lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
    //     lv_coord_t font_h = lv_font_get_line_height(font);

    //     lv_area_t roller_coords;
    //     lv_obj_get_coords(obj, &roller_coords);

    //     lv_area_t rect_area;
    //     rect_area.x1 = roller_coords.x1;
    //     rect_area.x2 = roller_coords.x2;
    //     rect_area.y1 = roller_coords.y1;
    //     rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;

    //     lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    //     lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
    //     mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);

    //     rect_area.y1 = rect_area.y2 + font_h + line_space - 1;
    //     rect_area.y2 = roller_coords.y2;

    //     lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    //     lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
    //     mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);

    // } else if (code == LV_EVENT_DRAW_POST_END) {
    //     lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)lv_draw_mask_remove_id(mask_top_id);
    //     lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)lv_draw_mask_remove_id(mask_bottom_id);
    //     lv_draw_mask_free_param(fade_mask_top);
    //     lv_draw_mask_free_param(fade_mask_bottom);
    //     lv_mem_buf_release(fade_mask_top);
    //     lv_mem_buf_release(fade_mask_bottom);
    //     mask_top_id = -1;
    //     mask_bottom_id = -1;
    // } else if (code == LV_EVENT_VALUE_CHANGED){
    //     static char buffer[16];
    //     uint8_t index = lv_obj_get_child_id(obj);
    //     lv_roller_get_selected_str(obj, buffer, sizeof(buffer));
    //     if (index == 0)
    //         choose_year=atoi(buffer);
    //     else
    //         choose_month=atoi(buffer);
    // }
}

static void DateMenu_Back_Event(lv_event_t* e)
{
    // lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    // lv_indev_set_group(indev_encoder, lv_group_get_default());;
    // lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, true);
    Load_DateMenu();
}

static void DateMenu_Msgbox_Close_Event(lv_event_t* e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * mbox = lv_obj_get_parent(btn);
    // lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
    lv_obj_del_async(mbox);
    Load_DateMenu();
    // lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}

static void DateMenu_Calender_Event(lv_event_t * e)
{
    // lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_current_target(e);

    lv_calendar_date_t date;
    if(lv_calendar_get_pressed_date(obj, &date))
    {
        Clock_setDate(date.year, date.month, date.day);
        // lv_obj_t* cont = (lv_obj_t*)lv_event_get_user_data(e);
        // 消息提示框
        lv_obj_t * mbox = lv_msgbox_create(lv_layer_top(), "消息", "设置日期成功!", nullptr, true);
        lv_obj_t* label_title = lv_msgbox_get_title(mbox);
        lv_obj_t* label_text = lv_msgbox_get_text(mbox);
        lv_obj_t* btn_back = lv_msgbox_get_close_btn(mbox);
        lv_obj_set_style_text_font(label_title, &zh_cn_jshaoer_14, 0);
        lv_obj_set_style_text_font(label_text, &zh_cn_jshaoer_14, 0);
        lv_obj_remove_event_cb(btn_back, NULL);
        lv_obj_add_event_cb(btn_back, DateMenu_Msgbox_Close_Event, LV_EVENT_CLICKED, NULL);
        lv_obj_center(mbox);

        lv_group_t* group = lv_group_create();
        lv_group_add_obj(group, btn_back);
        lv_indev_set_group(indev_encoder, group);
    }
}

static void DateMenu_Show_Dalender(lv_event_t* e)
{
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_center(cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    // lv_obj_t* cont_back = (lv_obj_t*)lv_event_get_user_data(e);

    uint16_t year = Clock_Info.year;
    uint8_t month = Clock_Info.month;
    uint8_t day = Clock_Info.day;
    lv_obj_t* calendar = lv_calendar_create(cont);
    lv_obj_set_size(calendar, LV_PCT(95), LV_PCT(95));
    lv_obj_set_style_text_font(calendar, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_center(calendar);
    lv_obj_add_event_cb(calendar, DateMenu_Calender_Event, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_style_height(calendar, 10, LV_PART_CURSOR);

    lv_calendar_set_today_date(calendar, year, month, day);
    lv_calendar_set_showed_date(calendar, choose_year, choose_month);
    // 返回按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(btn_back, DateMenu_Back_Event, LV_EVENT_FOCUSED, NULL);

    lv_obj_t* btnm = lv_calendar_get_btnmatrix(calendar);
    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, btnm);
    lv_group_add_obj(group, btn_back);
    lv_group_focus_obj(btnm);
    lv_group_set_editing(group, true);
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, true);
}

void Load_DateMenu(void)
{
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, TFT_WIDTH);
    lv_obj_set_height(cont, TFT_HEIGHT);
    // lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_center(cont);
    choose_year = Clock_Info.year;
    choose_month = Clock_Info.month;

    lv_obj_t* date_year, * date_month;
    // 年份列表
    date_year = lv_roller_create(cont);
    lv_obj_set_size(date_year, LV_PCT(40), LV_PCT(80));
    lv_obj_align(date_year, LV_ALIGN_CENTER, -25, 0);
    lv_obj_set_style_bg_color(date_year, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(date_year, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_color(date_year, lv_color_hex(0x323130), 0);
    lv_obj_set_style_text_color(date_year, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(date_year, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(date_year, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(date_year, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(date_year,
                        "2010\n""2011\n""2012\n""2013\n""2014\n""2015\n""2016\n"
                        "2017\n""2018\n""2019\n""2020\n""2021\n""2022\n""2023\n"
                        "2024\n""2025\n""2026\n""2027\n""2028\n""2029\n""2030",
                        LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(date_year, 3);
    lv_obj_add_event_cb(date_year, DateMenu_Roller_Event, LV_EVENT_VALUE_CHANGED, NULL);
    lv_roller_set_selected(date_year, LV_ABS(Clock_Info.year-2010), LV_ANIM_OFF);
    // 月份列表
    date_month = lv_roller_create(cont);
    lv_obj_set_size(date_month, LV_PCT(25), LV_PCT(80));
    lv_obj_align(date_month, LV_ALIGN_CENTER, 25, 0);
    lv_obj_set_style_bg_color(date_month, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(date_month, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_color(date_month, lv_color_hex(0x323130), 0);
    lv_obj_set_style_text_color(date_month, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(date_month, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(date_month, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(date_month, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(date_month,
                        "01\n""02\n""03\n""04\n""05\n""06\n"
                        "07\n""08\n""09\n""10\n""11\n""12",
                        LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(date_month, 3);
    lv_obj_add_event_cb(date_month, DateMenu_Roller_Event, LV_EVENT_VALUE_CHANGED, NULL);
    lv_roller_set_selected(date_month, LV_ABS(Clock_Info.month-1), LV_ANIM_OFF);
    // 右键按钮
    lv_obj_t* btn_right = lv_btn_create(cont);
    lv_obj_set_style_bg_color(btn_right, lv_palette_main(LV_PALETTE_GREY),0);
    lv_obj_set_style_bg_opa(btn_right, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(btn_right, 0, 0);
    lv_obj_set_size(btn_right, LV_PCT(8), LV_PCT(95));
    lv_obj_set_align(btn_right, LV_ALIGN_RIGHT_MID);
    lv_obj_add_event_cb(btn_right, DateMenu_Show_Dalender, LV_EVENT_CLICKED, NULL);
    lv_obj_t* label_right = lv_label_create(btn_right);
    lv_obj_set_style_text_font(label_right, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_text_color(label_right, lv_color_white(), 0);
    lv_label_set_text(label_right, ">");
    lv_obj_center(label_right);
    // 退出按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);

    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, btn_back);
    lv_group_add_obj(group, date_year);
    lv_group_add_obj(group, date_month);
    lv_group_add_obj(group, btn_right);
    lv_group_focus_obj(btn_back);
    lv_indev_set_group(indev_encoder, group);
    NOW_PAGE = DateMenu_Page;
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}