/*
 * @Author: your name
 * @Date: 2021-10-09 17:57:25
 * @LastEditTime: 2021-10-15 15:54:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\clock.h
 */
#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "stdint.h"

struct _Clock_Info
{
    uint16_t year=2021;
    uint8_t month=12;
    uint8_t day=20;
    uint8_t week=0;
    char week_str[12];
    char week_str_short[4];
    uint8_t hour=0;
    uint8_t minute=0;
    uint8_t second=0;
    uint32_t timestamp=0;
};

const char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char daysOfTheWeek_Short[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char daysOfTheWeek_Zh[7][4] = {"日", "一", "二", "三", "四", "五", "六"};
extern struct _Clock_Info Clock_Info;


/**
  * @brief  初识化DS1307模块
  * @param  无
  * @retval 成功状态
  */
bool Clock_Init(void);


/**
  * @brief  更新时钟信息
  * @param  无
  * @retval 无
  */
void Clock_Update(void);


/**
  * @brief  设置时钟日期
  * @param  year:年份
  * @param  month:月份
  * @param  day:天数
  * @retval 无
  */
void Clock_setDate(uint16_t year, uint8_t month, uint8_t day);


/**
  * @brief  设置时钟时间
  * @param  hour:小时
  * @param  minute:分钟
  * @param  second:秒钟
  * @retval 无
  */
void Clock_setTime(uint8_t hour, uint8_t minute, uint8_t second);

/**
  * @brief  设置时钟小时
  * @param  hour:小时
  * @param  minute:分钟
  * @param  second:秒钟
  * @retval 无
  */
void Clock_setHour(uint8_t hour);

/**
  * @brief  设置时钟分钟
  * @param  hour:小时
  * @param  minute:分钟
  * @param  second:秒钟
  * @retval 无
  */
void Clock_setMinute(uint8_t minute);


/**
  * @brief  设置时钟日期时间
  * @param  时间撮(自1970-01-01)
  * @retval 无
  */
void Clock_setDateTime(uint32_t timestemp);


/**
  * @brief  设置时钟日期时间
  * @param  year:年份
  * @param  month:月份
  * @param  day:天数
  * @param  hour:小时
  * @param  minute:分钟
  * @param  second:秒钟
  * @retval 无
  */
void Clock_setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);


/**
  * @brief  格式化输出时间字符串（如："YY/MM/DD hh:mm:ss"->"21/12/22 12:00:00"）
  * @param  buffer:格式化字符串地址
  * @retval char*:字符串首地址
  */
char *Clock_toString(char *buffer);


/**
  * @brief  获取时间戳（自1970-01-01）
  * @param  无
  * @retval uint32_t:时间撮
  */
uint32_t Clock_getTimestemp(void);

/**
  * @brief  格式化运行时长
  * @param  uint32_t: 运行时长
  * @retval const char*:运行时长
  */
const char* Clock_getRuntime(uint32_t runtime);

#endif // !_CLOCK_H_