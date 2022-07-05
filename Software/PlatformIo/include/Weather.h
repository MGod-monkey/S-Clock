#ifndef __WEATHER_H
#define __WEATHER_H

#include "WiFi.h"
#include "iostream"
#include "globalConfig.h"
#include "ArduinoJson.h"
#include "Debug.h"

struct _Weather_Info{
    char day_one_date[20];                  //  当天天数：如"2022-01-22"
    char day_one_text_day[20];              //  白天天气现象文字：如"多云"
    uint8_t day_one_code_day;               //  白天天气现象代码：见https://seniverse.yuque.com/books/share/e52aa43f-8fe9-4ffa-860d-96c0f3cf1c49/yev2c3
    // char day_one_text_night[20];            //  夜间天气现象文字：如"多云"
    // uint8_t day_one_code_night;             //  夜间天气现象代码：见https://seniverse.yuque.com/books/share/e52aa43f-8fe9-4ffa-860d-96c0f3cf1c49/yev2c3
    int day_one_temp_high;                  //  当天最高温度
    int day_one_temp_low;                   //  当天最低温度
    float day_one_rainfall;                 //  当天降水量
    float day_one_precip;                   //  当天降水概率（0~1）
    char day_one_wind_direction[10];         //  风向文字
    uint16_t day_one_wind_direction_degree; //  风向角度（0~360）
    float day_one_wind_speed;               //  风速，单位km/h
    uint8_t day_one_wind_scale;             //  风力等级
    uint8_t day_one_hum;                    //  相对湿度：0~100，单位百分比
    
    char day_two_date[20];
    char day_two_text_day[20];
    uint8_t day_two_code_day;
    // char day_two_text_night[20];
    // uint8_t day_two_code_night;
    int day_two_temp_high;
    int day_two_temp_low;
    float day_two_rainfall;
    float day_two_precip;
    char day_two_wind_direction[10];
    uint16_t day_two_wind_direction_degree;
    float day_two_wind_speed;
    uint8_t day_two_wind_scale;
    uint8_t day_two_hum;

    char day_three_date[20];                  
    char day_three_text_day[20];
    uint8_t day_three_code_day;
    // char day_three_text_night[20];
    // uint8_t day_three_code_night;
    int day_three_temp_high;
    int day_three_temp_low;
    float day_three_rainfall;
    float day_three_precip;
    char day_three_wind_direction[10];
    uint16_t day_three_wind_direction_degree;
    float day_three_wind_speed;
    uint8_t day_three_wind_scale;
    uint8_t day_three_hum;
};

struct _Weather_Self_Info
{
    char host[20] = HOST;
    char city[20];
    char private_key[20];
};

extern struct _Weather_Info Weather_Info;
extern struct _Weather_Self_Info Weather_Self_Info;

/**
  * @brief  设置天气城市
  * @param  const char*:城市拼音，如"beijing"
  * @retval 无
  */
void Weather_setCity(const char* city);


/**
  * @brief  设置天气API秘钥
  * @param  const char*:秘钥
  * @retval 无
  */
void Weather_setPrivateKey(const char* private_key);


/**
  * @brief  更新天气信息
  * @param  无
  * @retval bool:服务器状态
  */
bool Weather_Update(void);

#endif // !__WEATHER_H