#include "lvgl.h"
#include "View/SetupView.h"

#define LV_ANIM_EXEC(attr)      (lv_anim_exec_xcb_t)lv_obj_set_##attr
#define LV_ANIM_TIMELINE_WRAPPER_END {0, NULL}

typedef struct {
    uint32_t start_time;
    lv_obj_t* obj;
    lv_anim_exec_xcb_t exec_cb;
    int32_t start;
    int32_t end;
    uint16_t duration;
    lv_anim_path_cb_t path_cb;
    bool early_apply;
} lv_anim_timeline_wrapper_t;
static lv_anim_timeline_t* anim_timeline;

void lv_anim_timeline_add_wrapper(lv_anim_timeline_t* at, const lv_anim_timeline_wrapper_t* wrapper)
{
    for(uint32_t i = 0; wrapper[i].obj != NULL; i++)
    {
        const lv_anim_timeline_wrapper_t* atw = &wrapper[i];

        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, atw->obj);
        lv_anim_set_values(&a, atw->start, atw->end);
        lv_anim_set_exec_cb(&a, atw->exec_cb);
        lv_anim_set_time(&a, atw->duration);
        lv_anim_set_path_cb(&a, atw->path_cb);
        lv_anim_set_early_apply(&a, atw->early_apply);

        lv_anim_timeline_add(at, atw->start_time, &a);
    }
}

void Load_SetupView(void)
{
    lv_obj_t* bg = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(bg);
    lv_obj_set_size(bg, TFT_WIDTH, TFT_HEIGHT);
    lv_obj_set_style_bg_color(bg, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_t* cont = lv_obj_create(bg);
    lv_obj_remove_style_all(cont);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(cont, 110, 50);
    lv_obj_set_style_border_color(cont, lv_color_hex(0xff931e), 0);
    lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(cont, 3, 0);
    lv_obj_set_style_border_post(cont, true, 0);
    lv_obj_center(cont);

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_label_set_text(label, "S-CLOCK");
    lv_obj_center(label);
    // setupView.label_logo = label;

    anim_timeline = lv_anim_timeline_create();

    #define ANIM_DEF(start_time, obj, attr, start, end) \
     {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}
    
    lv_anim_timeline_wrapper_t wrapper[] =
    {
        ANIM_DEF(0, cont, width, 0, lv_obj_get_style_width(cont, 0)),
        ANIM_DEF(500, label, y, lv_obj_get_style_height(cont, 0), lv_obj_get_y(label)),
        LV_ANIM_TIMELINE_WRAPPER_END
    };

    lv_anim_timeline_add_wrapper(anim_timeline, wrapper);
    lv_anim_timeline_start(anim_timeline);
}

void SetupView_Delete(void)
{
    if(anim_timeline)
        lv_anim_timeline_del(anim_timeline);
}