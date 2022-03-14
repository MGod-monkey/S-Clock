#ifndef __ALARM_H
#define __ALARM_H

#include "Arduino.h"

#define SLEEP_TIME            5     // 贪睡时间（m）

enum {
    ALARM_FREQ_EVERYDAY = 0,    // 每天闹铃
    ALARM_FREQ_ONCE     = 1,    // 单次闹铃
    ALARM_FREQ_WORKDAY  = 2,    // 工作日闹铃
    ALARM_FREQ_WEEKDAY  = 3     // 选定星期闹铃
};

enum {
    ALARM_SLEEP_OFF     = false,    // 关闭贪睡
    ALARM_SLEEP_ON      = true     // 开启贪睡
};

struct _Alarm_Info_t
{
    uint8_t hour=12;

    uint8_t minute=0;

    uint8_t week_days=0x7f;

    uint8_t freq_mode=0;

    bool isOpen=false;
};

struct _Alarm_Info
{
    uint8_t alarm_num;
    int recent_index;
    int last_index=-1;
    bool isToday;
    bool sleep_mode;
};

const char freqMode_Zh[4][16] = {"每天", "单次", "工作日", "选定星期"};
extern struct _Alarm_Info Alarm_Info;
extern struct _Alarm_Info_t Alarm_Info_t[6];

/**
  * @brief  更新最近闹铃索引
  * @param  无
  * @retval 无
  */
void Alarm_updateRecentIndex(void);


/**
  * @brief  判断闹铃状态
  * @param  无
  * @retval bool:闹铃状态
  */
bool Alarm_Status(void);


/**
  * @brief  格式化输出闹铃时间
  * @param  buffer:格式化字符串；如“hh:mm”
  * @retval 格式化后的时间字符串，如“12:00”
  */
char* Alarm_toString(char* buffer);


/**
  * @brief  格式化输出闹铃时间
  * @param  buffer:格式化字符串；如“hh:mm”
  * @param  index:闹铃索引
  * @retval 格式化后的时间字符串，如“12:00”
  */
char* Alarm_toString(uint8_t index, char* buffer);


/**
  * @brief  设置指定闹铃时间
  * @param  hour:小时
  * @param  minute:分钟
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_setTime(uint8_t index, uint8_t hour, uint8_t minute);


/**
  * @brief  设置完整的指定闹铃
  * @param  hour:小时
  * @param  minute:分钟
  * @param  freq_mode:闹铃频率模式，如ALARM_FREQ_ONCE等
  * @param  choose_days:选定的星期数
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_setFullAlarm(uint8_t index, uint8_t hour, uint8_t minute, uint8_t freq_mode, uint8_t choose_days);


/**
  * @brief  设置完整的闹铃
  * @param  std::string alarm_str
  *     // alarm格式:  如11120010000000
        // 第1个数：闹钟索引 index(1~5)
        // 第2个数：开启或关闭 on:1/off:0
        // 第3~6个数：闹钟时间 1200->12:00
        // 第7个数：闹钟频率格式 freq_mode(1~4)
        // 第8~14个数：选择的星期 choose_days(0000000)分别对应星期日~星期六
  * @retval 无
  */
void Alarm_setFullAlarm(std::string alarm_str);


/**
  * @brief  设置完整的闹铃(索引模式)
  * @param  uint8_t index:闹铃索引
  * @param  std::string alarm_str
  *     // alarm格式:  如1120010000000
        // 第1个数：开启或关闭 on:1/off:0
        // 第2~5个数：闹钟时间 1200->12:00
        // 第6个数：闹钟频率格式 freq_mode(1~4)
        // 第7~13个数：选择的星期 choose_days(0000000)分别对应星期日~星期六
  * @retval 无
  */
void Alarm_setFullAlarmWithIndex(uint8_t index, std::string alarm_str);


/**
  * @brief  设置最近的闹铃时间
  * @param  hour:小时
  * @param  minute:分钟
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_setRecentTime(uint8_t hour, uint8_t minute);


/**
  * @brief  设置完整的最近闹铃
  * @param  hour:小时
  * @param  minute:分钟
  * @param  freq_mode:闹铃频率模式，如ALARM_FREQ_ONCE等
  * @param  choose_days:选定的星期数
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_setRecentFullAlarm(uint8_t hour, uint8_t minute, uint8_t freq_mode, uint8_t choose_days);


/**
  * @brief  闹铃延后5*n分钟（用于贪睡模式）
  * @param  无
  * @retval 无
  */
void Alarm_addFiveMinute(void);


/**
  * @brief  结束当前闹钟
  * @param  无
  * @retval 无
  */
void Alarm_endRecentAlarm();


/**
  * @brief  闹铃转换为保存字符串格式
  * @param  index：闹铃索引
  * @retval const char*:字符串
  */
const char* Alarm_toSaveStr(uint8_t index);


/**
  * @brief  闹铃转换为CSV格式
  * @param  无
  * @retval const char*:字符串
  */
const char* Alarm_toCSVStr();


/**
  * @brief  设置开启的闹铃数
  * @param  alarm_num:闹铃数
  * @retval 无
  */
void Alarm_setAlarmNum(uint8_t alarm_num);

/**
  * @brief  添加闹铃数
  * @retval 无
  */
void Alarm_addAlarmNum();


/**
  * @brief  关闭闹铃
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_Close(uint8_t index);


/**
  * @brief  开启闹铃
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_Open(uint8_t index);


/**
  * @brief  关闭闹铃贪睡模式
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_closeSleepMode();


/**
  * @brief  开启闹铃贪睡模式
  * @param  index:闹铃索引
  * @retval 无
  */
void Alarm_openSleepMode();


/**
  * @brief  设置闹铃频率模式
  * @param  index:闹铃索引
  * @param  freq_mode:频率模式
  * @param  choose_days:选定星期（只有freq_mode=ALARM_FREQ_WEEKDAY有效）
  * @retval 无
  */
void Alarm_setFreqMode(uint8_t index, uint8_t freq_mode, uint8_t choose_days);


/**
  * @brief  获取闹铃选定星期
  * @param  index:闹铃索引
  * @retval const char*:闹铃选定星期二进制字符串，如"1101101"
  */
const char *Alarm_getWeekdays(uint8_t index);


#endif