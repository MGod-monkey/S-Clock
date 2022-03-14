#include "Clock.h"
#include "Menu/Menu_Apps.h"

static void TimeMenu_Roller_Event(lv_event_t* e)
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
            Clock_setHour(value);
        else 
            Clock_setMinute(value);
    }
}

void Load_TimeMenu(void){
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, TFT_WIDTH);
    lv_obj_set_height(cont, TFT_HEIGHT);
    // lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_center(cont);
    lv_obj_t* time_hour, *time_minute;
    // 小时列表
    time_hour = lv_roller_create(cont);
    lv_obj_set_size(time_hour, LV_PCT(30), LV_PCT(80));
    lv_obj_align(time_hour, LV_ALIGN_CENTER, -30, 0);
    lv_obj_set_style_bg_color(time_hour, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(time_hour, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(time_hour, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(time_hour, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(time_hour, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(time_hour, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(time_hour,
                        "0\n""1\n""2\n""3\n""4\n""5\n""6\n"
                        "7\n""8\n""9\n""10\n""11\n""12\n"
                        "13\n""14\n""15\n""16\n""17\n""18\n""19\n"
                        "20\n""21\n""22\n""23",
                        LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(time_hour, 3);
    lv_obj_add_event_cb(time_hour, TimeMenu_Roller_Event, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(time_hour, Clock_Info.hour, LV_ANIM_OFF);
    // 分钟列表
    time_minute = lv_roller_create(cont);
    lv_obj_set_size(time_minute, LV_PCT(30), LV_PCT(80));
    lv_obj_align(time_minute, LV_ALIGN_CENTER, 30, 0);
    lv_obj_set_style_bg_color(time_minute, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(time_minute, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(time_minute, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(time_minute, LV_OPA_TRANSP, LV_PART_SELECTED);

    lv_obj_set_style_text_font(time_minute, &zh_cn_jshaoer_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(time_minute, &zh_cn_jshaoer_18, LV_PART_SELECTED);

    lv_roller_set_options(time_minute,
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
    lv_roller_set_visible_row_count(time_minute, 3);
    lv_obj_add_event_cb(time_minute, TimeMenu_Roller_Event, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(time_minute, Clock_Info.minute, LV_ANIM_OFF);
    // 中间的冒号
    lv_obj_t* label_sign = lv_label_create(cont);
    lv_obj_set_style_text_color(label_sign, lv_color_white(), 0);
    lv_label_set_text(label_sign, ":");
    lv_obj_center(label_sign);
    // 退出按钮
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);

    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, time_hour);
    lv_group_add_obj(group, time_minute);
    lv_group_add_obj(group, btn_back);
    lv_group_focus_obj(btn_back);
    NOW_PAGE = TimeMenu_Page;
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}