#ifndef __MENU_VIEW_H
#define __MENU_VIEW_H

#include "View.h"

void MenuView_Btn_Event(lv_event_t* e);

void MenuView_Additem(lv_obj_t* par,lv_event_cb_t event_cb,const void* img_src,const char* text,lv_app_load_fp lv_app_scr_load);

void ClockView_Scroll_Event(lv_event_t* e);

void Load_MenuView(bool isDel);

#endif
