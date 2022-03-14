#include "Lightness.h"
#include "ESP/ESP_Save.h"
#include "Menu/Menu_Apps.h"

static void LightnessMenu_Slider_Event(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t* slider = lv_event_get_target(e);
        lv_obj_t* slider_label = (lv_obj_t*)lv_event_get_user_data(e);
        uint8_t lightness_percent = (uint8_t)lv_slider_get_value(slider);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", lightness_percent*20);
        lv_label_set_text(slider_label, buf);
        lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        Lightness_setPercent(lightness_percent*20);
        ESPSave_updateConfig(SAVE_CMD_LIGHTNESS);
    }
}

void Load_LightnessMenu(void){
    static lv_obj_t* slider_label;

    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_center(cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    //返回键
    lv_obj_t* btn_back = lv_btn_create(cont);
    lv_obj_remove_style_all(btn_back);
    lv_obj_set_size(btn_back, 1, 1);
    lv_obj_set_align(btn_back, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_back, Item_Back_Menu, LV_EVENT_LONG_PRESSED, NULL);
    // 柯南贱表情
    LV_IMG_DECLARE(kenan_0)
    LV_IMG_DECLARE(kenan_1)
    LV_IMG_DECLARE(kenan_2)
    LV_IMG_DECLARE(kenan_3)
    LV_IMG_DECLARE(kenan_4)
    static const lv_img_dsc_t* kenan_anim_img[5] = {
        &kenan_0,
        &kenan_1,
        &kenan_2,
        &kenan_3,
        &kenan_4
    };
    lv_obj_t* anim_img = lv_animimg_create(cont); 
    lv_obj_align(anim_img, LV_ALIGN_TOP_MID, 0, 20);
    lv_animimg_set_src(anim_img, (lv_img_dsc_t**)kenan_anim_img, 5);
    lv_animimg_set_duration(anim_img, 1000);
    lv_animimg_set_repeat_count(anim_img, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(anim_img);
    // 滑动条
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_color(&style_indic, lv_palette_lighten(LV_PALETTE_RED, 3));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    static lv_style_t style_indic_pr;
    lv_style_init(&style_indic_pr);
    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_shadow_width(&style_indic_pr, 10);
    lv_style_set_shadow_spread(&style_indic_pr, 3);

    lv_obj_t* slider = lv_slider_create(cont);
    lv_obj_set_size(slider, 100, 10);
    lv_slider_set_range(slider, 0, 5);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 20);
    lv_slider_set_value(slider, Lightness_Info.lightness_percent/10, LV_ANIM_OFF);
    lv_obj_add_style(slider, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_style(slider, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
    
    slider_label = lv_label_create(cont);
    lv_label_set_text_fmt(slider_label, "%d%%",Lightness_Info.lightness_percent);
    lv_obj_set_style_text_color(slider_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_obj_add_event_cb(slider, LightnessMenu_Slider_Event, LV_EVENT_VALUE_CHANGED, slider_label);

    lv_group_t* group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_group_add_obj(group, slider);
    lv_group_add_obj(group, btn_back);
    lv_group_focus_obj(btn_back);
    NOW_PAGE = LightnessMenu_Page;
    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}