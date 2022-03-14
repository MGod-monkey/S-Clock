#include "Weather.h"
#include "ESP/ESP_Save.h"

struct _Weather_Info Weather_Info;
struct _Weather_Self_Info Weather_Self_Info;

static WiFiClient client;
static DynamicJsonDocument Weather_Json(1400);
// https://api.seniverse.com/v3/weather/daily.json?key=SdZjOV5WU3kXzlQkD&location=guigang&language=zh-Hans&unit=c&start=0&days=3

void Weather_setCity(const char* city)
{
    strcpy(Weather_Self_Info.city, city);
    ESPSave_updateConfig(SAVE_CMD_WEATHER_CITY);
}

void Weather_setPrivateKey(const char* private_key)
{
    strcpy(Weather_Self_Info.private_key, private_key);
    ESPSave_updateConfig(SAVE_CMD_WEATHER_KEY);
}

bool Weather_Update(void)
{
    if (!client.connected())
        if (!client.connect(Weather_Self_Info.host, 80))
            return false;

    String getUrl = "/v3/weather/daily.json?key=";
    getUrl += Weather_Self_Info.private_key;
    getUrl += "&location=";
    getUrl += Weather_Self_Info.city;
    getUrl += "&language=zh-Hans&unit=c&start=0&days=3";
    client.print(String("GET ") + getUrl + " HTTP/1.1\r\n" + "Host: " + Weather_Self_Info.host + "\r\n" + "Connection: close\r\n\r\n");

    char endOfHeaders[] = "\r\n\r\n";
    bool ok = client.find(endOfHeaders);
    if (!ok)
    {
        SCLOCK_LOGLN("[Network Error]No response or invalid response!");
        return false;
    }

    String line = "";

    line += client.readStringUntil('\n');

    DeserializationError error = deserializeJson(Weather_Json, line);
    if (error)
    {
        SCLOCK_LOGLN("[Json Error]deserialize json failed");
        return false;
    }
    // 当天天气详情
    strcpy(Weather_Info.day_one_date,Weather_Json["results"][0]["daily"][0]["date"].as<const char *>());
    strcpy(Weather_Info.day_one_text_day,Weather_Json["results"][0]["daily"][0]["text_day"].as<const char *>());
    Weather_Info.day_one_code_day = Weather_Json["results"][0]["daily"][0]["code_day"].as<const uint8_t>();
    // strcpy(Weather_Info.day_one_text_night,Weather_Json["results"][0]["daily"][0]["text_night"].as<const char *>());
    // Weather_Info.day_one_code_night = Weather_Json["results"][0]["daily"][0]["code_night"].as<const uint8_t>();
    Weather_Info.day_one_temp_high = Weather_Json["results"][0]["daily"][0]["high"].as<const int>();
    Weather_Info.day_one_temp_low = Weather_Json["results"][0]["daily"][0]["low"].as<const int>();
    Weather_Info.day_one_rainfall = Weather_Json["results"][0]["daily"][0]["rainfall"].as<const float>();
    Weather_Info.day_one_precip = Weather_Json["results"][0]["daily"][0]["precip"].as<const float>();
    strcpy(Weather_Info.day_one_wind_direction,Weather_Json["results"][0]["daily"][0]["wind_direction"].as<const char *>());
    Weather_Info.day_one_wind_direction_degree = Weather_Json["results"][0]["daily"][0]["wind_direction_degree"].as<const uint16_t>();
    Weather_Info.day_one_wind_speed = Weather_Json["results"][0]["daily"][0]["wind_speed"].as<const float>();
    Weather_Info.day_one_wind_scale = Weather_Json["results"][0]["daily"][0]["wind_scale"].as<const uint8_t>();
    Weather_Info.day_one_hum = Weather_Json["results"][0]["daily"][0]["humidity"].as<const uint8_t>();
    // sscanf(Weather_Json["results"][0]["daily"][0]["date"].as<const char *>(),"%d-%d-%d",&Weather_Info.day_one_year,&Weather_Info.day_one_month,&Weather_Info.day_one_date);
    
    // 第二天天气详情
    strcpy(Weather_Info.day_two_date,Weather_Json["results"][0]["daily"][1]["date"].as<const char *>());
    strcpy(Weather_Info.day_two_text_day,Weather_Json["results"][0]["daily"][1]["text_day"].as<const char *>());
    Weather_Info.day_two_code_day = Weather_Json["results"][0]["daily"][1]["code_day"].as<const uint8_t>();
    // strcpy(Weather_Info.day_two_text_night,Weather_Json["results"][0]["daily"][1]["text_night"].as<const char *>());
    // Weather_Info.day_two_code_night = Weather_Json["results"][0]["daily"][1]["code_night"].as<const uint8_t>();
    Weather_Info.day_two_temp_high = Weather_Json["results"][0]["daily"][1]["high"].as<const int>();
    Weather_Info.day_two_temp_low = Weather_Json["results"][0]["daily"][1]["low"].as<const int>();
    Weather_Info.day_two_rainfall = Weather_Json["results"][0]["daily"][1]["rainfall"].as<const float>();
    Weather_Info.day_two_precip = Weather_Json["results"][0]["daily"][1]["precip"].as<const float>();
    strcpy(Weather_Info.day_two_wind_direction,Weather_Json["results"][0]["daily"][1]["wind_direction"].as<const char *>());
    Weather_Info.day_two_wind_direction_degree = Weather_Json["results"][0]["daily"][1]["wind_direction_degree"].as<const uint16_t>();
    Weather_Info.day_two_wind_speed = Weather_Json["results"][0]["daily"][1]["wind_speed"].as<const float>();
    Weather_Info.day_two_wind_scale = Weather_Json["results"][0]["daily"][1]["wind_scale"].as<const uint8_t>();
    Weather_Info.day_two_hum = Weather_Json["results"][0]["daily"][1]["humidity"].as<const uint8_t>();

    // 第三天天气详情
    strcpy(Weather_Info.day_three_date,Weather_Json["results"][0]["daily"][2]["date"].as<const char *>());
    strcpy(Weather_Info.day_three_text_day,Weather_Json["results"][0]["daily"][2]["text_day"].as<const char *>());
    Weather_Info.day_three_code_day = Weather_Json["results"][0]["daily"][2]["code_day"].as<const uint8_t>();
    // strcpy(Weather_Info.day_three_text_night,Weather_Json["results"][0]["daily"][2]["text_night"].as<const char *>());
    // Weather_Info.day_three_code_night = Weather_Json["results"][0]["daily"][2]["code_night"].as<const uint8_t>();
    Weather_Info.day_three_temp_high = Weather_Json["results"][0]["daily"][2]["high"].as<const int>();
    Weather_Info.day_three_temp_low = Weather_Json["results"][0]["daily"][2]["low"].as<const int>();
    Weather_Info.day_three_rainfall = Weather_Json["results"][0]["daily"][2]["rainfall"].as<const float>();
    Weather_Info.day_three_precip = Weather_Json["results"][0]["daily"][2]["precip"].as<const float>();
    strcpy(Weather_Info.day_three_wind_direction,Weather_Json["results"][0]["daily"][2]["wind_direction"].as<const char *>());
    Weather_Info.day_three_wind_direction_degree = Weather_Json["results"][0]["daily"][2]["wind_direction_degree"].as<const uint16_t>();
    Weather_Info.day_three_wind_speed = Weather_Json["results"][0]["daily"][2]["wind_speed"].as<const float>();
    Weather_Info.day_three_wind_scale = Weather_Json["results"][0]["daily"][2]["wind_scale"].as<const uint8_t>();
    Weather_Info.day_three_hum = Weather_Json["results"][0]["daily"][2]["humidity"].as<const uint8_t>();

    Weather_Json.clear();
    client.stop();
    return true;
}