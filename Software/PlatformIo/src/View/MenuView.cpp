#include "View/MenuView.h"
#include "Menu/Menu_Apps.h"

page_index NOW_PAGE;

void MenuView_Btn_Event(lv_event_t* e)
{
    lv_app_load_fp fp;
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_LONG_PRESSED)
        Menu_Back_Home(NULL);
    else if (code == LV_EVENT_SHORT_CLICKED)
    {
        fp = (lv_app_load_fp)lv_event_get_user_data(e);
        if (fp != NULL)
        {
            (*fp)();
        }
    }
}

void MenuView_Additem(lv_obj_t* par,lv_event_cb_t event_cb,const void* img_src,const char* text,lv_app_load_fp lv_app_scr_load)
{
    lv_obj_t* btn = lv_btn_create(par);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(btn, lv_color_black(), 0);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_SHORT_CLICKED, (void *)lv_app_scr_load);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_LONG_PRESSED, NULL);
    lv_group_add_obj(lv_group_get_default(), btn);

    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &zh_cn_jshaoer_14);

    lv_obj_t* img = lv_img_create(btn);
    lv_img_set_src(img, img_src);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t* label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_label_set_recolor(label, true);
    lv_obj_add_style(label, &label_style, 0);
    lv_label_set_text(label, text);
}

void ClockView_Scroll_Event(lv_event_t* e)
{
    
    lv_obj_t* cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_width(cont) * 5 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++) {
        lv_obj_t* child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

        lv_coord_t diff_x = child_x_center - cont_x_center;
        diff_x = LV_ABS(diff_x);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t y;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_x >= r) {
            y = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            lv_coord_t y_sqr = r * r - diff_x * diff_x;
            lv_sqrt_res_t res;
            lv_sqrt(y_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            y = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_y(child, y, 0);
    }
}

void Load_MenuView(bool isDel)
{
    // 菜单主体
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);

    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_add_event_cb(cont, ClockView_Scroll_Event, LV_EVENT_SCROLL, NULL);
    //lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_time, "#666666 时 间#", Load_TimeMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_date, "#666666 日 期#", Load_DateMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_alarm, "#666666 闹 钟#", Load_AlarmMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_lightness, "#666666 亮 度#", Load_LightnessMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_weather, "#666666 天 气#", Load_WeatherMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_toolbox, "#666666 工具箱#", Load_ToolboxMenu);
    MenuView_Additem(cont, MenuView_Btn_Event, &icon_setting, "#666666 设 置#", Load_OptionMenu);
    lv_obj_scroll_to_view(lv_obj_get_child(cont, NOW_PAGE), LV_ANIM_OFF);
    lv_group_focus_obj(lv_obj_get_child(cont, NOW_PAGE));

    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_MOVE_TOP, 500, 0, isDel);
}