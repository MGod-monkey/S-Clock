#include "ESP/ESP_WiFi.h"

static WiFiUDP ntpUDP;
struct _Wifi_Info Wifi_Info;
static NTPClient timeClient(ntpUDP,8*3600);

void ESPWifi_Init(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    #ifdef  WIFI_SSID
        strcpy(Wifi_Info.ssid, WIFI_SSID);
    #endif
    #ifdef WIFI_PASSWD
        strcpy(Wifi_Info.passwd, WIFI_PASSWD);
    #endif
    delay(100);
    if (WiFi.status() != WL_CONNECTED)
        Wifi_Info.wifi_status = WF_DISCONNECTED;
    else
        Wifi_Info.wifi_status = WF_CONNECTED;
}

bool ESPWifi_Status(void)
{
    if (WiFi.status() != WL_CONNECTED)
        return false;
    strcmp(Wifi_Info.ssid, WiFi.SSID().c_str());
    strcmp(Wifi_Info.passwd, WiFi.psk().c_str());
    Wifi_Info.wifi_status = WF_CONNECTED;
    return true;
}

bool ESPWifi_smartConfigStatus(void)
{
    if (!WiFi.smartConfigDone())
        return false;
    return true;
}

const char* ESPWifi_localIP(void)
{
    if (Wifi_Info.wifi_status == WF_CLOSE)
        return "未开启";
    else if (Wifi_Info.wifi_status == WF_CONNECTING)
        return "连接中";
    else if (Wifi_Info.wifi_status == WF_CONNECTED)
        return WiFi.localIP().toString().c_str();
    return "未连接";
}

uint8_t ESPWifi_RSSI(void)
{
    if (Wifi_Info.wifi_status == WF_CONNECTED)
        return WiFi.RSSI();
    return 0;
}

void ESPWifi_connectToWifi(const char* ssid, const char* passwd)
{
    if (ESPWifi_Status())
        WiFi.disconnect();
    WiFi.begin(ssid, passwd);
}

// void ESPWifi_Close()
// {
//     WiFi.disconnect();
//     Wifi_Info.wifi_status = WF_CLOSE;
// }

// void ESPWifi_Open()
// {
//     WiFi.reconnect();
//     if (WiFi.status() != WL_CONNECTED)
//         Wifi_Info.wifi_status = WF_DISCONNECTED;
//     else Wifi_Info.wifi_status = WF_CONNECTED;
// }

bool ESPWifi_setNTPTime(void)
{
    timeClient.begin();
    if (timeClient.update())
    {
        Clock_setDateTime((uint32_t)timeClient.getEpochTime());
        timeClient.end();
        return true;
    }
    timeClient.end();
    return false;
}

void ESPWifi_startSmartConfig(void)
{
    WiFi.beginSmartConfig();
    Wifi_Info.smartconfig_status = WF_CONNECTING;
}

void ESPWifi_stopSmartConfig(void)
{
    WiFi.stopSmartConfig();
    Wifi_Info.smartconfig_status = WF_DISCONNECTED;
}