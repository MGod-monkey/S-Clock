#ifndef __MENU_APPS_H
#define __Menu_APPS_H

#include "View.h"

enum page_index
{
    TimeMenu_Page      = 0,
    DateMenu_Page      = 1,
    AlarmMenu_Page     = 2,
    LightnessMenu_Page = 3,
    WeatherMenu_Page   = 4,
    ToolboxMenu_Page   = 5,
    OptionMenu_Page    = 6
};

extern page_index NOW_PAGE;

void Load_AlarmMenu(void);

void Load_DateMenu(void);

void Load_LightnessMenu(void);

void Load_ToolboxMenu(void);

void Load_TimeMenu(void);

void Load_WeatherMenu(void);

void Load_OptionMenu(void);

void Load_ToolboxMenu_Network(void);

void Load_FlashlightMenu(void);

void AlarmMenu_Update(void);

#endif // !__MENU_APPS_H