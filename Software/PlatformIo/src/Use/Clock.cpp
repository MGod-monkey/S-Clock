#include "Clock.h"
#include "stdint.h"
#include "Wire.h"
#include "Debug.h"
#include "RTClib.h"
#include "View.h"

static RTC_DS1307 Rtc;
struct _Clock_Info Clock_Info;

bool Clock_Init(void)
{
    // Wire.setPins(RTC_SDA, RTC_SCL);
    if (!Rtc.begin()) {
        SCLOCK_LOGLN("[RTC ERROR] Couldn't find RTC!");
        Serial.flush();
        return false;
    }
    Wire.setClock(400000); //experimental I2C speed! 400KHz, default 100KHz
    if (!Rtc.isrunning()) {
        SCLOCK_LOGLN("[RTC NOTE] Not running!");
        Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    // DateTime now = Rtc.now();
    // Clock_Info.timestamp=now.unixtime();
    return true;
}

void Clock_Update(void)
{  
    DateTime now = Rtc.now();
    Clock_Info.year = now.year();
    Clock_Info.month = now.month();
    Clock_Info.day = now.day();
    Clock_Info.week = now.dayOfTheWeek();
    Clock_Info.hour = now.hour();
    Clock_Info.minute = now.minute();
    Clock_Info.second = now.second();
    strcpy(Clock_Info.week_str, daysOfTheWeek[Clock_Info.week]);
    strcpy(Clock_Info.week_str_short, daysOfTheWeek_Short[Clock_Info.week]);
}

uint32_t Clock_getTimestemp(void)
{
   return Rtc.now().unixtime();
}

void Clock_setDate(uint16_t year, uint8_t month, uint8_t day)
{
    // DateTime now = Rtc.now();
    // uint8_t hour = now.hour();
    // uint8_t minute = now.minute();
    // uint8_t second = now.second();
    // Clock_Info.year = year;
    // Clock_Info.month = month;
    // Clock_Info.day = day;
    // Clock_Info.hour = hour;
    // Clock_Info.minute = minute;
    // Clock_Info.second = second;
    DateTime settime = DateTime(year, month, day, Clock_Info.hour, Clock_Info.minute, Clock_Info.second);
    Rtc.adjust(settime);
}

void Clock_setTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    // DateTime now = Rtc.now();
    // uint16_t year = now.year();
    // uint8_t month = now.month();
    // uint8_t day = now.day();
    // Clock_Info.year = year;
    // Clock_Info.month = month;
    // Clock_Info.day = day;
    // Clock_Info.hour = hour;
    // Clock_Info.minute = minute;
    // Clock_Info.second = second;
    DateTime settime = DateTime(Clock_Info.year, Clock_Info.month, Clock_Info.day, hour, minute, second);
    Rtc.adjust(settime);
}

void Clock_setHour(uint8_t hour)
{
    // DateTime now = Rtc.now();
    // uint8_t minute = now.minute();
    // uint8_t second = now.second();
    // uint16_t year = now.year();
    // uint8_t month = now.month();
    // uint8_t day = now.day();
    // Clock_Info.year = year;
    // Clock_Info.month = month;
    // Clock_Info.day = day;
    // Clock_Info.hour = hour;
    // Clock_Info.minute = minute;
    // Clock_Info.second = second;
    DateTime settime = DateTime(Clock_Info.year, Clock_Info.month, Clock_Info.day, hour, Clock_Info.minute, Clock_Info.second);
    Rtc.adjust(settime);
}

void Clock_setMinute(uint8_t minute)
{
    // DateTime now = Rtc.now();
    // uint8_t hour = now.hour();
    // uint8_t second = now.second();
    // uint16_t year = now.year();
    // uint8_t month = now.month();
    // uint8_t day = now.day();
    // Clock_Info.year = year;
    // Clock_Info.month = month;
    // Clock_Info.day = day;
    // Clock_Info.hour = hour;
    // Clock_Info.minute = minute;
    // Clock_Info.second = second;
    DateTime settime = DateTime(Clock_Info.year, Clock_Info.month, Clock_Info.day, Clock_Info.hour, minute, Clock_Info.second);
    Rtc.adjust(settime);
}

void Clock_setDateTime(uint32_t timestemp)
{
    DateTime settime = DateTime(timestemp);
    Clock_Info.year = settime.year();
    Clock_Info.month = settime.month();
    Clock_Info.day = settime.day();
    Clock_Info.hour = settime.hour();
    Clock_Info.minute = settime.minute();
    Clock_Info.second = settime.second();
    Rtc.adjust(settime);
}

void Clock_setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    // DateTime now = Rtc.now();
    // if (!year)   year = now.year();
    // if (!month)  month = now.month();
    // if (!day)    day = now.day();
    // if (!hour)   hour = now.hour();
    // if (!minute)  minute = now.minute();
    // if (!second)    second = now.second();
    DateTime settime = DateTime(year, month, day, hour, minute, second);
    Rtc.adjust(settime);
}

char *Clock_toString(char *buffer)
{
  for (size_t i = 0; i < strlen(buffer) - 1; i++) {
        if (buffer[i] == 'h' && buffer[i + 1] == 'h') {
            buffer[i] = '0' + Clock_Info.hour / 10;
            buffer[i + 1] = '0' + Clock_Info.hour % 10;
        }
        if (buffer[i] == 'm' && buffer[i + 1] == 'm') {
        buffer[i] = '0' + Clock_Info.minute / 10;
        buffer[i + 1] = '0' + Clock_Info.minute % 10;
        }
        if (buffer[i] == 's' && buffer[i + 1] == 's') {
        buffer[i] = '0' + Clock_Info.second / 10;
        buffer[i + 1] = '0' + Clock_Info.second % 10;
        }
        if (buffer[i] == 'D' && buffer[i + 1] == 'D' && buffer[i + 2] == 'D') {
        static PROGMEM const char day_names[] = "SunMonTueWedThuFriSat";
        const char *p = &day_names[3 * Clock_Info.week];
        buffer[i] = pgm_read_byte(p);
        buffer[i + 1] = pgm_read_byte(p + 1);
        buffer[i + 2] = pgm_read_byte(p + 2);
        } else if (buffer[i] == 'D' && buffer[i + 1] == 'D') {
        buffer[i] = '0' + Clock_Info.day / 10;
        buffer[i + 1] = '0' + Clock_Info.day % 10;
        }
        if (buffer[i] == 'M' && buffer[i + 1] == 'M' && buffer[i + 2] == 'M') {
        static PROGMEM const char month_names[] =
            "JanFebMarAprMayJunJulAugSepOctNovDec";
        const char *p = &month_names[3 * (Clock_Info.month - 1)];
        buffer[i] = pgm_read_byte(p);
        buffer[i + 1] = pgm_read_byte(p + 1);
        buffer[i + 2] = pgm_read_byte(p + 2);
        } else if (buffer[i] == 'M' && buffer[i + 1] == 'M') {
        buffer[i] = '0' + Clock_Info.month / 10;
        buffer[i + 1] = '0' + Clock_Info.month % 10;
        }
        if (buffer[i] == 'Y' && buffer[i + 1] == 'Y' && buffer[i + 2] == 'Y' &&
            buffer[i + 3] == 'Y') {
        buffer[i] = '2';
        buffer[i + 1] = '0';
        buffer[i + 2] = '0' + (Clock_Info.year / 10) % 10;
        buffer[i + 3] = '0' + Clock_Info.year % 10;
        } else if (buffer[i] == 'Y' && buffer[i + 1] == 'Y') {
        buffer[i] = '0' + (Clock_Info.year / 10) % 10;
        buffer[i + 1] = '0' + Clock_Info.year % 10;
        }
    }
    return buffer;
}

const char* Clock_getRuntime(uint32_t runtime)
{
    runtime /= 1000;
    char* buffer = (char*)malloc(sizeof(char)*12);
    uint8_t hour = runtime / 3600;
    runtime -= (hour*3600);
    uint8_t min = runtime / 60;
    runtime -= (min*60);
    if (hour != 0)
        sprintf(buffer, "%2dh%2dm%2ds", hour, min, runtime);
    else
        sprintf(buffer, "%02dm%02ds", min, runtime);
    return buffer;
}