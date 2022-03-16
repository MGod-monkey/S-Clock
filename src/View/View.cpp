#include "View.h"

bool show_alarmWin = true;
uint8_t sleep_count = 0;
lv_indev_t *indev_encoder;

void Item_Back_Menu(lv_event_t* e)
{
    // lv_timer_t* timer = (lv_timer_t*)lv_event_get_user_data(e);
    // if (timer)
    //     lv_timer_del(timer);
    Load_MenuView(true);
}

void Menu_Back_Home(lv_event_t* e)
{
    Load_ClockView(0);
}

void Home_To_Menu(lv_event_t* e)
{
    // lv_timer_t* timer = (lv_timer_t*)lv_event_get_user_data(e);
    // if (timer)
    //     lv_timer_del(timer);
    Load_MenuView(false);
}

static void View_Del_Obj(lv_anim_t* a)
{
    lv_obj_del((lv_obj_t*)a->var);
}

void View_Show_Topbox(const char* mess_txt, uint32_t continue_time)
{
    lv_obj_t* cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 100, LV_SIZE_CONTENT);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x605e5c), 0);
    lv_obj_set_style_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_t* txt = lv_label_create(cont);
    lv_label_set_text(txt, mess_txt);
    lv_obj_set_style_text_font(txt, &zh_cn_jshaoer_14, 0);
    lv_label_set_long_mode(txt, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_center(txt);
    uint32_t start_y = lv_obj_get_height(cont);
    lv_obj_set_x(cont, 14);
    lv_obj_set_y(cont, -start_y);

    // 自上向下显示动画
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cont);
    lv_anim_set_values(&a, -start_y, 0);
    lv_anim_set_time(&a, 800);
    lv_anim_set_delay(&a, 0);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    // lv_anim_set_ready_cb(&a, ready_cb);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
    lv_anim_start(&a);
    // 自下向上显示动画
    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, cont);
    lv_anim_set_values(&b, 0, -start_y);
    lv_anim_set_time(&b, 800);
    lv_anim_set_delay(&b, continue_time);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_ready_cb(&b, View_Del_Obj);
    lv_anim_set_path_cb(&b, lv_anim_path_ease_out);
    lv_anim_start(&b);
}

void View_Show_Messagebox(const char* title, const char* txt)
{
    lv_obj_t* mbox = lv_msgbox_create(lv_layer_top(), title, txt, NULL, true);
    lv_obj_set_style_bg_color(mbox, lv_color_hex(0x686868), 0);
    lv_obj_set_style_bg_opa(mbox, LV_OPA_COVER, 0);
    lv_obj_center(mbox);
    lv_obj_t* mbox_title = lv_msgbox_get_title(mbox);
    lv_obj_set_style_text_font(mbox_title, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(mbox_title, lv_color_white(), 0);
    lv_obj_t* mbox_text = lv_msgbox_get_text(mbox);
    lv_obj_set_style_text_font(mbox_text, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_text_color(mbox_text, lv_color_white(), 0);
    lv_obj_t* mbox_close_btn = lv_msgbox_get_close_btn(mbox);
    lv_obj_set_size(mbox_close_btn, 1, 1);
    lv_obj_set_style_bg_color(mbox_close_btn, lv_color_hex(0x686868), 0);
    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, mbox_close_btn);
    lv_indev_set_group(indev_encoder, group);
}

void View_Show_Messagebox(const char* title, const char* txt, uint32_t delay_ms)
{
    lv_obj_t* mbox = lv_msgbox_create(lv_layer_top(), title, txt, NULL, false);
    lv_obj_set_style_bg_color(mbox, lv_color_hex(0x686868), 0);
    lv_obj_set_style_bg_opa(mbox, LV_OPA_COVER, 0);
    lv_obj_center(mbox);
    lv_obj_t* mbox_title = lv_msgbox_get_title(mbox);
    lv_obj_set_style_text_font(mbox_title, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(mbox_title, lv_color_white(), 0);
    lv_obj_t* mbox_text = lv_msgbox_get_text(mbox);
    lv_obj_set_style_text_font(mbox_text, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_text_color(mbox_text, lv_color_white(), 0);
    lv_obj_del_delayed(mbox, delay_ms);
}

void View_Show_Messagebox(const char* title, const char* txt, const char **btn_txts, lv_event_cb_t btn_event_cb)
{
    lv_obj_t* mbox = lv_msgbox_create(lv_layer_top(), title, txt, btn_txts, false);
    lv_obj_set_style_bg_color(mbox, lv_color_hex(0x686868), 0);
    lv_obj_set_style_bg_opa(mbox, LV_OPA_COVER, 0);
    lv_obj_center(mbox);
    lv_obj_add_event_cb(mbox, btn_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_t* mbox_title = lv_msgbox_get_title(mbox);
    lv_obj_set_style_text_font(mbox_title, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(mbox_title, lv_color_white(), 0);
    lv_obj_t* mbox_text = lv_msgbox_get_text(mbox);
    lv_obj_set_style_text_font(mbox_text, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_text_color(mbox_text, lv_color_white(), 0);
    lv_obj_t* mbox_btns = lv_msgbox_get_btns(mbox);
    lv_obj_set_width(mbox_btns, LV_PCT(100));
    // lv_obj_set_height(mbox_btns, LV_PCT(35));

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x4a4a4a));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_12);
    lv_style_set_text_color(&style_btn, lv_color_white());
    lv_obj_add_style(mbox_btns, &style_btn, LV_PART_ITEMS);

    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, mbox_btns);
    lv_group_set_editing(group, true);
    lv_indev_set_group(indev_encoder, group);
}

void View_Show_Messagebox(const char* title, const char* txt, const char **btn_txts, lv_event_cb_t btn_event_cb, void* user_data)
{
    lv_obj_t* mbox = lv_msgbox_create(lv_layer_top(), title, txt, btn_txts, false);
    lv_obj_set_style_bg_color(mbox, lv_color_hex(0x686868), 0);
    lv_obj_set_style_bg_opa(mbox, LV_OPA_COVER, 0);
    lv_obj_center(mbox);
    lv_obj_add_event_cb(mbox, btn_event_cb, LV_EVENT_VALUE_CHANGED, user_data);
    lv_obj_t* mbox_title = lv_msgbox_get_title(mbox);
    lv_obj_set_style_text_font(mbox_title, &zh_cn_jshaoer_14, 0);
    lv_obj_set_style_text_color(mbox_title, lv_color_white(), 0);
    lv_obj_t* mbox_text = lv_msgbox_get_text(mbox);
    lv_obj_set_style_text_font(mbox_text, &zh_cn_jshaoer_12, 0);
    lv_obj_set_style_text_color(mbox_text, lv_color_white(), 0);
    lv_obj_t* mbox_btns = lv_msgbox_get_btns(mbox);
    lv_obj_set_width(mbox_btns, LV_PCT(100));
    // lv_obj_set_height(mbox_btns, LV_PCT(35));

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x4a4a4a));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_12);
    lv_style_set_text_color(&style_btn, lv_color_white());
    lv_obj_add_style(mbox_btns, &style_btn, LV_PART_ITEMS);

    lv_group_t* group = lv_group_create();
    lv_group_add_obj(group, mbox_btns);
    lv_group_set_editing(group, true);
    lv_indev_set_group(indev_encoder, group);
}

void View_Close_Top_Objs(void)
{
    // uint8_t cnt = lv_obj_get_child_cnt(lv_layer_top());
    // for (int i=0; i<cnt-1; i++)
    // {
    //     lv_obj_t* obj = lv_obj_get_child(lv_layer_top(), 0);
    //     lv_obj_del(obj);
    // }
    lv_obj_clean(lv_layer_top());
    lv_group_t *group = lv_group_get_default();
    lv_group_set_editing(group, false);
    lv_indev_set_group(indev_encoder, group);
}

void View_Close_All_Top_Objs(void)
{
    uint8_t cnt = lv_obj_get_child_cnt(lv_layer_top());
    for (int i=0; i<cnt; i++)
    {
        lv_obj_t* obj = lv_obj_get_child(lv_layer_top(), 0);
        lv_obj_del(obj);
    }
    lv_indev_set_group(indev_encoder, lv_group_get_default());
}

void View_Alarm_Click_Event(lv_event_t* e)
{
    // lv_obj_t * mbox = lv_event_get_current_target(e);
    // const char* btn_text = lv_msgbox_get_active_btn_text(mbox);
    // if (!strcmp(btn_text, "继续"))
    // {
    //     ++sleep_count;
    //     Alarm_addFiveMinute();
    // } else
    // {
    //     sleep_count = 0;
    //     Alarm_endRecentAlarm();    
    // }
    lv_obj_t* obj = lv_event_get_target(e);
    char* txt = lv_label_get_text(lv_obj_get_child(obj, 0));
    if (!strcmp(txt, "继续"))
    {
        ++sleep_count;
        Alarm_addFiveMinute();
    }
    else
    {
        sleep_count = 0;
        Alarm_endRecentAlarm();    
    }
    Beep_Shutdown();
    View_Close_Top_Objs();
}

// lv_obj_t* lv_alarmbox_create(lv_obj_t * parent, const lv_img_dsc_t** anim_imgs, const char **btn_txts)
// {
//     lv_obj_t * obj = lv_obj_class_create_obj(&lv_msgbox_class, parent);
//     LV_ASSERT_MALLOC(obj);
//     lv_obj_class_init_obj(obj);
//     if(obj == NULL) return NULL;
//     lv_msgbox_t * alarmbox = (lv_msgbox_t *)obj;
//     lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
//     lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//     alarmbox->content = lv_obj_class_create_obj(&lv_msgbox_content_class, obj);

//     alarmbox->text = lv_animimg_create(alarmbox->content);
//     lv_animimg_set_src(alarmbox->text, (lv_img_dsc_t**)anim_imgs, 4);
//     lv_animimg_set_duration(alarmbox->text, 1000);
//     lv_animimg_set_repeat_count(alarmbox->text, LV_ANIM_REPEAT_INFINITE);
//     lv_animimg_start(alarmbox->text);
//     // lv_obj_align(animimg_alarm, LV_ALIGN_TOP_MID, 0, 2);
//     // alarmbox->text = lv_img_create(alarmbox->content);
//     // lv_img_set_src(alarmbox->text, img);
//     // lv_obj_set_width(alarmbox->text, lv_pct(100));
//     // lv_obj_align(alarmbox->text, LV_ALIGN_TOP_MID, 0, 2);

//     if(btn_txts) {
//         alarmbox->btns = lv_btnmatrix_create(obj);
//         lv_btnmatrix_set_map(alarmbox->btns, btn_txts);
//         lv_btnmatrix_set_btn_ctrl_all(alarmbox->btns, LV_BTNMATRIX_CTRL_CLICK_TRIG | LV_BTNMATRIX_CTRL_NO_REPEAT);

//         uint32_t btn_cnt = 0;
//         while(btn_txts[btn_cnt] && btn_txts[btn_cnt][0] != '\0') {
//             btn_cnt++;
//         }

//         const lv_font_t * font = lv_obj_get_style_text_font(alarmbox->btns, LV_PART_ITEMS);
//         lv_coord_t btn_h = lv_font_get_line_height(font) + LV_DPI_DEF / 10;
//         lv_obj_set_size(alarmbox->btns, btn_cnt * (2 * LV_DPI_DEF / 3), btn_h);
//         lv_obj_set_style_max_width(alarmbox->btns, lv_pct(100), 0);
//         lv_obj_add_flag(alarmbox->btns, LV_OBJ_FLAG_EVENT_BUBBLE);
//     }
//     return obj;
// }

void View_Show_AlarmWin(void)
{
    View_Close_All_Top_Objs();
    SCLOCK_LOGLN("[Alarm Notice] Alarm Ring~ Ring~ Ring~");
    // LV_IMG_DECLARE(Alarm_6);
    //     LV_IMG_DECLARE(Alarm_0);
    // // LV_IMG_DECLARE(Alarm_1);
    // LV_IMG_DECLARE(Alarm_2);
    // // LV_IMG_DECLARE(Alarm_3);
    // LV_IMG_DECLARE(Alarm_4);
    // // LV_IMG_DECLARE(Alarm_5);
    // LV_IMG_DECLARE(Alarm_6);
    // static const lv_img_dsc_t* anim_imgs[4] = {
    //     &Alarm_0,
    //     // &Alarm_1,
    //     &Alarm_2,
    //     // &Alarm_3,
    //     &Alarm_4,
    //     // &Alarm_5,
    //     &Alarm_6,
    // };
    // static const char *btns[] = {"", "", ""};
    // if (Alarm_Info.sleep_mode)
    // {
    //     btns[0] = "继续";
    //     btns[1] = "退出";
    // }
    // else
    //     btns[0] = "退出";

    // lv_obj_t* alarmbox = lv_alarmbox_create(lv_layer_top(), anim_imgs, btns);
    // lv_obj_set_style_bg_color(alarmbox, lv_color_hex(0x686868), 0);
    // lv_obj_set_style_bg_opa(alarmbox, LV_OPA_80, 0);
    // lv_obj_center(alarmbox);
    // lv_obj_add_event_cb(alarmbox, View_Alarm_Click_Event, LV_EVENT_VALUE_CHANGED, NULL);
    // lv_obj_t* alarmbox_btns = lv_msgbox_get_btns(alarmbox);
    // lv_obj_set_width(alarmbox_btns, LV_PCT(100));
    // // lv_obj_set_height(mbox_btns, LV_PCT(35));

    // static lv_style_t style_btn;
    // lv_style_init(&style_btn);
    // lv_style_set_bg_color(&style_btn, lv_color_hex(0x4a4a4a));
    // lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    // lv_style_set_text_font(&style_btn, &zh_cn_jshaoer_12);
    // lv_style_set_text_color(&style_btn, lv_color_white());
    // lv_obj_add_style(alarmbox_btns, &style_btn, LV_PART_ITEMS);

    // lv_group_t* group = lv_group_create();
    // lv_group_add_obj(group, alarmbox_btns);
    // lv_group_set_editing(group, true);
    // lv_indev_set_group(indev_encoder, group);

    lv_obj_t* cont = lv_obj_create(lv_layer_top());
    LV_ASSERT_MALLOC(cont);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_bg_color(cont, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_90, 0);
    lv_obj_set_style_radius(cont, 10, 0);
    lv_obj_set_size(cont, 100, 100);
    lv_obj_center(cont);

    // 动态IMG会照成闹钟弹窗卡顿，在没有更好办法前，就此舍弃
    // LV_IMG_DECLARE(Alarm_0);
    // // LV_IMG_DECLARE(Alarm_1);
    // LV_IMG_DECLARE(Alarm_2);
    // // LV_IMG_DECLARE(Alarm_3);
    // LV_IMG_DECLARE(Alarm_4);
    // // LV_IMG_DECLARE(Alarm_5);
    // LV_IMG_DECLARE(Alarm_6);
    // static const lv_img_dsc_t* anim_imgs[4] = {
    //     &Alarm_0,
    //     // &Alarm_1,
    //     &Alarm_2,
    //     // &Alarm_3,
    //     &Alarm_4,
    //     // &Alarm_5,
    //     &Alarm_6,
    // };
    // lv_obj_t * animimg_alarm = lv_animimg_create(cont);
    // lv_obj_center(animimg_alarm);
    // lv_animimg_set_src(animimg_alarm, (lv_img_dsc_t**)anim_imgs, 4);
    // lv_animimg_set_duration(animimg_alarm, 1000);
    // lv_animimg_set_repeat_count(animimg_alarm, LV_ANIM_REPEAT_INFINITE);
    // lv_animimg_start(animimg_alarm);
    // lv_obj_align(animimg_alarm, LV_ALIGN_TOP_MID, 0, 2);

    LV_IMG_DECLARE(Alarm_6);
    lv_obj_t* img = lv_img_create(cont);
    lv_img_set_src(img, &Alarm_6);
    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 2);

    lv_obj_t* btn, * label;
    lv_group_t* group = lv_group_create();

    if (Alarm_Info.sleep_mode)
    {
        btn = lv_btn_create(cont);
        lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_add_event_cb(btn, View_Alarm_Click_Event, LV_EVENT_CLICKED, NULL);
        lv_obj_set_style_text_color(btn, lv_color_hex(0xadb5bd), 0);
        lv_group_add_obj(group, btn);
        label = lv_label_create(btn);
        lv_label_set_text(label, "继续");
        lv_label_set_recolor(label, true);
        lv_obj_set_style_text_font(label, &zh_cn_jshaoer_12, 0);
        lv_obj_center(label);
        lv_obj_set_size(btn, 30, 20);
        lv_obj_set_style_shadow_width(btn, 0, 0);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, -20, -5);

        btn = lv_btn_create(cont);
        lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_set_style_text_color(btn, lv_color_hex(0xff6b6b), 0);
        lv_obj_add_event_cb(btn, View_Alarm_Click_Event, LV_EVENT_CLICKED, NULL);
        lv_obj_set_size(btn, 30, 20);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 20, -5);
        lv_group_add_obj(group, btn);
        label = lv_label_create(btn);
        lv_label_set_text(label, "结束");
        lv_obj_set_style_shadow_width(btn, 0, 0);
        lv_obj_set_style_text_font(label, &zh_cn_jshaoer_12, 0);
        lv_obj_center(label);
    }
    else
    {
        btn = lv_btn_create(cont);
        lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_set_style_text_color(btn, lv_color_hex(0xff6b6b), 0);
        lv_obj_add_event_cb(btn, View_Alarm_Click_Event, LV_EVENT_CLICKED, NULL);
        lv_obj_set_size(btn, 80, 20);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -5);
        lv_group_add_obj(group, btn);
        label = lv_label_create(btn);
        lv_label_set_text(label, "结束");
        lv_obj_set_style_shadow_width(btn, 0, 0);
        lv_obj_set_style_text_font(label, &zh_cn_jshaoer_12, 0);
        lv_obj_center(label);
    }

    lv_indev_set_group(indev_encoder, group);
}

void View_Close_AlarmWin(void)
{
    uint8_t cnt = lv_obj_get_child_cnt(lv_layer_top());
    for (int i=0; i<cnt; i++)
    {
        lv_obj_t* cont = lv_obj_get_child(lv_layer_top(), 0);
        lv_obj_del_async(cont);
    }
    lv_indev_set_group(indev_encoder, lv_group_get_default());
}