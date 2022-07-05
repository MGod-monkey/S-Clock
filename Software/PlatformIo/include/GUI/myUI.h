#ifndef _MYUI_H_
#define _MYUI_H_

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "TFT_eSPI.h"
// #include "UiSource.h"
#include "View.h"
#include "ESP/ESP_Key.h"
#include "Menu/Menu_Apps.h"
                
TFT_eSPI tft = TFT_eSPI();

static void deloadMainPage(lv_timer_t* timer)
{
    SetupView_Delete();
    ClockView_Create();
    Load_ClockView(800);
    // Load_OptionMenu();
    // View_Show_AlarmWin();
}

class UI
{
    public:
        int16_t width, height;
        lv_disp_t *disp;
        lv_group_t* group;
        lv_indev_drv_t indev_drv;
        UI(uint16_t width, uint16_t height) : width(width), height(height){
            static lv_disp_draw_buf_t draw_buf;
            static lv_color_t buf[ TFT_WIDTH * 10 ];

            lv_init();
            tft.begin(); /* TFT 初识化 */
            tft.setRotation(TFT_ROTATION_D);
            lv_disp_draw_buf_init( &draw_buf, buf, NULL, TFT_WIDTH * 10 );

            /*初识化显示屏*/
            static lv_disp_drv_t disp_drv;
            lv_disp_drv_init( &disp_drv );
            disp_drv.hor_res = TFT_WIDTH;
            disp_drv.ver_res = TFT_HEIGHT;
            disp_drv.flush_cb = my_disp_flush;
            disp_drv.draw_buf = &draw_buf;
            disp = lv_disp_drv_register( &disp_drv );
            lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

            /*初识化键盘*/
            Key_Init();
            lv_indev_drv_init(&indev_drv);
            indev_drv.type = LV_INDEV_TYPE_ENCODER;
            indev_drv.read_cb = my_key_read;
            indev_encoder = lv_indev_drv_register(&indev_drv);
            group = lv_group_create();
            lv_group_set_default(group);
            lv_indev_set_group(indev_encoder, group);

            #if LV_USE_LOG != 0
                lv_log_register_print_cb( my_print );
            #endif
        };
        // static void my_print( lv_log_level_t level, const char * file, uint32_t line, const char * fn_name, const char * dsc )
        // {
        //     Serial.printf( "%s(%s)@%d->%s\r\n", file, fn_name, line, dsc );
        //     Serial.flush();
        // }
        /* 日志输出 */
        static void my_print( const char * buf )
        {
            #if DEBUG_FLAG
                Serial.printf( "%s\r\n", buf );
            #endif
                Serial.flush();
        }
        /* 屏幕刷新 */
        static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
        {            
            uint32_t w = (area->x2 - area->x1 + 1);
            uint32_t h = (area->y2 - area->y1 + 1);
            
            tft.startWrite();
            tft.setAddrWindow(area->x1, area->y1, w, h);
            tft.pushColors(&color_p->full, w * h, true);
            tft.endWrite();

            lv_disp_flush_ready(disp);
        }
        /* 识别键盘 */
        static void my_key_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
        {
            static uint32_t last_key = 0;
            uint8_t act_enc = Key_Scan();

            if(act_enc != 0) {
                switch(act_enc) {
                    case KEY_OK_PRES:
                        act_enc = LV_KEY_ENTER;
                        data->state = LV_INDEV_STATE_PRESSED;	
                        break;
                    case KEY_NEXT_PRES:
                        act_enc = LV_KEY_RIGHT;
                        data->state = LV_INDEV_STATE_RELEASED;
                        data->enc_diff++;
                        break;
                    case KEY_PREV_PRES:
                        act_enc = LV_KEY_LEFT;
                        data->state = LV_INDEV_STATE_RELEASED;
                        data->enc_diff--;
                        break;
                }
                last_key = (uint32_t)act_enc;
            }
            data->key = last_key;
        }
        void initUI(){
            // Load_LightnessMenu();
            // Load_OptionMenu();
            // Load_ToolboxMenu();
            // Load_MenuView(true);
            Load_SetupView();
            lv_timer_t * timer = lv_timer_create(deloadMainPage, 1000, NULL);
            lv_timer_set_repeat_count(timer, 1);
        }
        /* 翻转屏幕 */
        void setRotation(TFT_ROTATION_MODE mode){
            tft.setRotation(mode);
        }
};

#endif