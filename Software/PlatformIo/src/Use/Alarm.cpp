#include "Alarm.h"
#include "Clock.h"
#include "Beep.h"
#include "RTClib.h"
#include "EEPROM.h"
#include "Debug.h"
#include "ESP/ESP_Save.h"

struct _Alarm_Info Alarm_Info;
struct _Alarm_Info_t Alarm_Info_t[6];

void Alarm_updateRecentIndex(void)
{
    uint8_t min_hour=99,min_minute=99;Alarm_Info.isToday=false;
    for (int i=0; i < Alarm_Info.alarm_num; i++)
    {
        if (!Alarm_Info_t[i].isOpen || i == Alarm_Info.last_index)
            continue;
        if ((Alarm_Info_t[i].week_days&(0x01<<Clock_Info.week))==(0x01<<Clock_Info.week))
        {
            if ((Alarm_Info_t[i].hour-Clock_Info.hour)<=min_hour && Alarm_Info_t[i].hour-Clock_Info.hour>=0)
            {
                min_hour=Alarm_Info_t[i].hour-Clock_Info.hour;
                if (Alarm_Info_t[i].minute-Clock_Info.minute<min_minute && Alarm_Info_t[i].minute-Clock_Info.minute>0)
                {
                    min_minute=Alarm_Info_t[i].minute-Clock_Info.minute;
                    Alarm_Info.recent_index=i;
                    Alarm_Info.isToday=true;
                }
            }
        }
    }
}

bool Alarm_Status(void)
{
    if (!Alarm_Info.isToday)
        return false;
    if (Clock_Info.hour == Alarm_Info_t[Alarm_Info.recent_index].hour && Clock_Info.minute == Alarm_Info_t[Alarm_Info.recent_index].minute && Alarm_Info.last_index != Alarm_Info.recent_index)
        return true;
    // Alarm_Info.last_index = Alarm_Info.recent_index;
    return false;
}

char* Alarm_toString(char* buffer)
{
    for (size_t i = 0; i < strlen(buffer) - 1; i++) {
        if (buffer[i] == 'h' && buffer[i + 1] == 'h') {
            buffer[i] = '0' + Alarm_Info_t[Alarm_Info.recent_index].hour / 10;
            buffer[i + 1] = '0' + Alarm_Info_t[Alarm_Info.recent_index].hour % 10;
        }
        if (buffer[i] == 'm' && buffer[i + 1] == 'm') {
        buffer[i] = '0' + Alarm_Info_t[Alarm_Info.recent_index].minute / 10;
        buffer[i + 1] = '0' + Alarm_Info_t[Alarm_Info.recent_index].minute % 10;
        }
    }
    return buffer;
}

char* Alarm_toString(uint8_t index, char* buffer)
{
    for (size_t i = 0; i < strlen(buffer) - 1; i++) {
        if (buffer[i] == 'h' && buffer[i + 1] == 'h') {
            buffer[i] = '0' + Alarm_Info_t[index].hour / 10;
            buffer[i + 1] = '0' + Alarm_Info_t[index].hour % 10;
        }
        if (buffer[i] == 'm' && buffer[i + 1] == 'm') {
        buffer[i] = '0' + Alarm_Info_t[index].minute / 10;
        buffer[i + 1] = '0' + Alarm_Info_t[index].minute % 10;
        }
    }
    return buffer;
}

void Alarm_setTime(uint8_t index, uint8_t hour, uint8_t minute)
{
    if(hour) Alarm_Info_t[index].hour=hour;
    if(minute) Alarm_Info_t[index].minute=minute;
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_addNum()
{
    Alarm_Info.alarm_num++;
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setNum(uint8_t alarm_num)
{
    Alarm_Info.alarm_num = alarm_num;
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setFullAlarm(uint8_t index, uint8_t hour, uint8_t minute, uint8_t freq_mode, uint8_t choose_days)
{
    Alarm_Info_t[index].hour = hour;
    Alarm_Info_t[index].minute = minute;
    Alarm_Info_t[index].freq_mode = freq_mode;
    switch (freq_mode)
    {
    case ALARM_FREQ_EVERYDAY:
        Alarm_Info_t[index].week_days=0x7f;break;
    case ALARM_FREQ_WORKDAY:
        Alarm_Info_t[index].week_days=0x3e;break;
    case ALARM_FREQ_ONCE:
        if (hour <= Clock_Info.hour && minute < Clock_Info.minute)
            Alarm_Info_t[index].week_days = 0x01<<(Clock_Info.week==0?6:Clock_Info.week-1);
        else
            Alarm_Info_t[index].week_days = 0x01<<Clock_Info.week;
        break;
    case ALARM_FREQ_WEEKDAY:
        Alarm_Info_t[index].week_days = choose_days;break;
    }
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setFullAlarm(std::string alarm_str)
{
    uint8_t index = (uint8_t)String_Sub_To_Int(alarm_str, 0, 1)-1;
    String_Sub_To_Int(alarm_str, 1, 1)==1?Alarm_Open(index):Alarm_Close(index);
    uint8_t hour = (uint8_t)String_Sub_To_Int(alarm_str, 2, 2);
    uint8_t minute = (uint8_t)String_Sub_To_Int(alarm_str, 4, 2);
    uint8_t freq_mode = (uint8_t)String_Sub_To_Int(alarm_str, 6, 1)-1;
    const char *choose_days = String_Sub_To_Str(alarm_str, 7, 7);
    char *p=(char*)choose_days;uint8_t n=0;uint8_t _choose_days=0;
    while (*p != '\0')
    {
        if (*p++ == 49)
            _choose_days |= (0x01<<n);
        n++;
    }
    Alarm_Info_t[index].hour = hour;
    Alarm_Info_t[index].minute = minute;
    Alarm_Info_t[index].freq_mode = freq_mode;
    switch (freq_mode)
    {
    case ALARM_FREQ_EVERYDAY:
        Alarm_Info_t[index].week_days=0x7f;break;
    case ALARM_FREQ_WORKDAY:
        Alarm_Info_t[index].week_days=0x3e;break;
    case ALARM_FREQ_ONCE:
        if (hour <= Clock_Info.hour && minute < Clock_Info.minute)
            Alarm_Info_t[index].week_days = 0x01<<(Clock_Info.week==0?6:Clock_Info.week-1);
        else
            Alarm_Info_t[index].week_days = 0x01<<Clock_Info.week;
        break;
    case ALARM_FREQ_WEEKDAY:
        Alarm_Info_t[index].week_days = _choose_days;break;
    }
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setFullAlarmWithIndex(uint8_t index, std::string alarm_str)
{
    String_Sub_To_Int(alarm_str, 0, 1)?Alarm_Open(index):Alarm_Close(index);
    uint8_t hour = (uint8_t)String_Sub_To_Int(alarm_str, 1, 2);
    uint8_t minute = (uint8_t)String_Sub_To_Int(alarm_str, 3, 2);
    uint8_t freq_mode = (uint8_t)String_Sub_To_Int(alarm_str, 5, 1);
    const char *choose_days = String_Sub_To_Str(alarm_str, 6, 7);
    char *p=(char*)choose_days;uint8_t n=0;uint8_t _choose_days=0;
    while (*p != '\0')
    {
        if (*p++ == 49)
            _choose_days |= (0x01<<n);
        n++;
    }
    Alarm_Info_t[index].hour = hour;
    Alarm_Info_t[index].minute = minute;
    Alarm_Info_t[index].freq_mode = freq_mode;
    switch (freq_mode)
    {
    case ALARM_FREQ_EVERYDAY:
        Alarm_Info_t[index].week_days=0x7f;break;
    case ALARM_FREQ_WORKDAY:
        Alarm_Info_t[index].week_days=0x3e;break;
    case ALARM_FREQ_ONCE:
        if (hour <= Clock_Info.hour && minute < Clock_Info.minute)
            Alarm_Info_t[index].week_days = 0x01<<(Clock_Info.week==0?6:Clock_Info.week-1);
        else
            Alarm_Info_t[index].week_days = 0x01<<Clock_Info.week;
        break;
    case ALARM_FREQ_WEEKDAY:
        Alarm_Info_t[index].week_days = _choose_days;break;
    }
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setRecentTime(uint8_t hour, uint8_t minute)
{
    Alarm_Info_t[Alarm_Info.recent_index].hour=hour;
    Alarm_Info_t[Alarm_Info.recent_index].minute=minute;
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_setRecentFullAlarm(uint8_t hour, uint8_t minute, uint8_t freq_mode, uint8_t choose_days)
{
    Alarm_Info_t[Alarm_Info.recent_index].hour = hour;
    Alarm_Info_t[Alarm_Info.recent_index].minute = minute;
    Alarm_Info_t[Alarm_Info.recent_index].freq_mode = freq_mode;
    switch (freq_mode)
    {
    case ALARM_FREQ_EVERYDAY:
        Alarm_Info_t[Alarm_Info.recent_index].week_days=0x7f;break;
    case ALARM_FREQ_WORKDAY:
        Alarm_Info_t[Alarm_Info.recent_index].week_days=0x3e;break;
    case ALARM_FREQ_ONCE:
        if (hour <= Clock_Info.hour && minute < Clock_Info.minute)
            Alarm_Info_t[Alarm_Info.recent_index].week_days = 0x01<<(Clock_Info.week==0?Clock_Info.week-1:6);
        else
            Alarm_Info_t[Alarm_Info.recent_index].week_days = 0x01<<Clock_Info.week;
        break;
    case ALARM_FREQ_WEEKDAY:
        Alarm_Info_t[Alarm_Info.recent_index].week_days = choose_days;break;
    }
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_addFiveMinute(void)
{
    uint8_t hour = Alarm_Info_t[Alarm_Info.recent_index].hour;
    uint8_t minute = Alarm_Info_t[Alarm_Info.recent_index].minute;
    Alarm_Info_t[5].hour = hour;
    if (minute+SLEEP_TIME >= 60)
    {
        if (hour+1 >= 24)
            Alarm_Info_t[5].hour = 0;
        Alarm_Info_t[5].minute = minute+SLEEP_TIME-60;
    }
    else
        Alarm_Info_t[5].minute = minute+SLEEP_TIME;
    
    Alarm_Info.recent_index = 5;
    SCLOCK_LOGLN("[Alarm Notice] The Alarm will ring again in 5m!");
}

void Alarm_endRecentAlarm()
{
    Alarm_Info.last_index = Alarm_Info.recent_index;
    Alarm_updateRecentIndex();
    SCLOCK_LOGLN("[Alarm Notice] Oh~ You closed this alarm! Nice day~");
}

const char* Alarm_toSaveStr(uint8_t index)
{
    char* buffer = (char *)malloc(sizeof(char)*16);
    sprintf(buffer, "%1d%2d%2d%1d%s",
                Alarm_Info_t[index].isOpen?1:0,
                Alarm_Info_t[index].hour,
                Alarm_Info_t[index].minute,
                Alarm_Info_t[index].freq_mode,
                Alarm_getWeekdays(index));
    return buffer;
}

const char* Alarm_toCSVStr()
{
    char* buffer = (char *)malloc(sizeof(char)*16*Alarm_Info.alarm_num);
    char* _buffer = (char *)malloc(sizeof(char)*16);
    for (uint8_t i=0; i<Alarm_Info.alarm_num; i++)
    {
        sprintf(_buffer, "\"%1d%02d%02d%1d%s\"",
                    Alarm_Info_t[i].isOpen?1:0,
                    Alarm_Info_t[i].hour,
                    Alarm_Info_t[i].minute,
                    Alarm_Info_t[i].freq_mode+1,
                    Alarm_getWeekdays(i));
        strcat(buffer, _buffer);
        if (i < Alarm_Info.alarm_num-1)
            strcat(buffer, ",");
    }

    return buffer;
}

void Alarm_setAlarmNum(uint8_t alarm_num)
{
    Alarm_Info.alarm_num = alarm_num;
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_addAlarmNum()
{
    Alarm_Info.alarm_num++;
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_Close(uint8_t index)
{
    Alarm_Info_t[index].isOpen = false;
    Alarm_updateRecentIndex();
}

void Alarm_Open(uint8_t index)
{
    Alarm_Info_t[index].isOpen = true;
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

void Alarm_closeSleepMode()
{
    Alarm_Info.sleep_mode = false;
}

void Alarm_openSleepMode()
{
    Alarm_Info.sleep_mode = true;
}

void Alarm_setFreqMode(uint8_t index, uint8_t freq_mode, uint8_t choose_days)
{
    Alarm_Info_t[index].freq_mode = freq_mode;
    switch (freq_mode)
    {
    case ALARM_FREQ_EVERYDAY:
        Alarm_Info_t[index].week_days = 0x7f;break;
    case ALARM_FREQ_ONCE:
        if (Clock_Info.hour-Alarm_Info_t[index].hour>0 && Clock_Info.minute-Alarm_Info_t[index].minute>0)
            Alarm_Info_t[index].week_days = 0x01<<(Clock_Info.week==6?0:Clock_Info.week+1);
        else
            Alarm_Info_t[index].week_days = 0x01<<Clock_Info.week;
        break;
    case ALARM_FREQ_WORKDAY:
        Alarm_Info_t[index].week_days = 0x3e;break;
    case ALARM_FREQ_WEEKDAY:
        Alarm_Info_t[index].week_days = choose_days;break;
    }
    Alarm_updateRecentIndex();
    ESPSave_updateConfig(SAVE_CMD_ALARM);
}

const char *Alarm_getWeekdays(uint8_t index)
{
	char *p = (char*)malloc(sizeof(char)*7+1);
	char *buffer = p;
	uint _week_days = Alarm_Info_t[index].week_days;
	for (uint8_t i=0; i<7; i++)
		*p++ = _week_days&(0x40>>i)?'1':'0';
	*p = '\0';
    return buffer;
}