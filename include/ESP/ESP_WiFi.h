#ifndef __ESP_WIFI_H
#define __ESP_WIFI_H

#include "WiFi.h"
#include "Clock.h"
#include "NTPClient.h"
// #include "globalConfig.h"
#include "WiFiUdp.h"

enum wifi_status_t
{
    WF_CLOSE,  
    WF_CONNECTING,
    WF_CONNECTED,
    WF_DISCONNECTED
};

struct _Wifi_Info
{
    char ssid[32];
    char passwd[32];
    wifi_status_t smartconfig_status;
    wifi_status_t wifi_status;
};

extern struct _Wifi_Info Wifi_Info;

void ESPWifi_Init(void);
// {
//     WiFi.mode(WIFI_STA);
//     WiFi.setAutoConnect(true);
//     WiFi.setAutoReconnect(true);
//     #ifdef  WIFI_SSID
//         strcpy(Wifi_Info.ssid, WIFI_SSID);
//     #endif
//     #ifdef WIFI_PASSWD
//         strcpy(Wifi_Info.passwd, WIFI_PASSWD);
//     #endif
//     delay(100);
//     if (WiFi.status() != WL_CONNECTED)
//         Wifi_Info.wifi_status = WF_DISCONNECTED;
//     else
//         Wifi_Info.wifi_status = WF_CONNECTED;
// }

bool ESPWifi_Status(void);
// {
//     if (WiFi.status() != WL_CONNECTED)
//         return false;
//     strcmp(Wifi_Info.ssid, WiFi.SSID().c_str());
//     strcmp(Wifi_Info.passwd, WiFi.psk().c_str());
//     Wifi_Info.wifi_status = WF_CONNECTED;
//     return true;
// }

bool ESPWifi_smartConfigStatus(void);
// {
//     if (!WiFi.smartConfigDone())
//         return false;
//     return true;
// }

const char* ESPWifi_localIP(void);
// {
//     if (Wifi_Info.wifi_status == WF_CLOSE)
//         return "未开启";
//     else if (Wifi_Info.wifi_status == WF_CONNECTING)
//         return "连接中";
//     else if (Wifi_Info.wifi_status == WF_CONNECTED)
//         return WiFi.localIP().toString().c_str();
//     return "未连接";
// }

uint8_t ESPWifi_RSSI(void);
// {
//     if (Wifi_Info.wifi_status == WF_CONNECTED)
//         return WiFi.RSSI();
//     return 0;
// }

void ESPWifi_connectToWifi(const char* ssid, const char* passwd);
// {
//     if (ESPWifi_Status())
//         WiFi.disconnect();
//     WiFi.begin(ssid, passwd);
// }

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

bool ESPWifi_setNTPTime(void);
// {
//     timeClient.begin();
//     timeClient.update();
//     Clock_setDateTime((uint32_t)timeClient.getEpochTime());
//     timeClient.end();
// }

void ESPWifi_startSmartConfig(void);
// {
//     WiFi.beginSmartConfig();
//     Wifi_Info.smartconfig_status = WF_CONNECTING;
// }

void ESPWifi_stopSmartConfig(void);
// {
//     WiFi.stopSmartConfig();
//     Wifi_Info.smartconfig_status = WF_DISCONNECTED;
// }

#endif // !__ESP_WIFI_H