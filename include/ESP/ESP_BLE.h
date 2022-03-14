#ifndef __ESP_BLE_H
#define __ESP_BLE_H

#include "NimBLEDevice.h"

#define ESP32_BLE_NAME          "S-CLOCK BLE"
#define SERVICEUUID_CLOCK       "fff0"
#define SERVICEUUID_ALARM       "fd36"
#define SERVICEUUID_SENSOR      "fd2d"
#define SERVICEUUID_WEATHER     "fd43"
#define CHARACTERUUID_CLOCK_TIME    "fff1"
#define CHARACTERUUID_CLOCK_DATE    "fff2"
#define CHARACTERUUID_SENSOR_TEMP   "fd2e"
#define CHARACTERUUID_SENSOR_HUM    "fd2f"
#define CHARACTERUUID_ALARM         "fd37"
#define CHARACTERUUID_ALARM_NUM     "fd38"
#define CHARACTERUUID_WEATHER       "fd44"
#define UUID_FULL_NAME(x)       ("0x"+String(x))

enum ble_status_t
{
    BLE_CONNECTED,
    BLE_DISCONNECTED,
    BLE_CONNECTING,
    BLE_CLOSE
};

struct _BLE_Info
{
    ble_status_t ble_status;
    bool ble_adv;
    uint8_t last_alarm_num;
};

extern struct _BLE_Info BLE_Info;

void BLE_Init();

/**
  * @brief  重置蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_resetAdvert(void);

/**
  * @brief  关闭蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_closeAdvert(void);

/**
  * @brief  开启蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_openAdvert(void);

/**
  * @brief  返回蓝牙广播状态
  * @param  无
  * @retval 广播状态：bool
  */
bool BLE_isAdvertising(void);

/**
  * @brief  返回蓝牙连接状态
  * @param  无
  * @retval 连接状态：bool
  */
bool BLE_isConnected(void);

/**
  * @brief  返回蓝牙设备名称
  * @param  无
  * @retval 名称: const char*
  */
const char* BLE_getDeviceName(void);

/**
  * @brief  返回蓝牙地址
  * @param  无
  * @retval Address: const char*
  */
const char* BLE_getAddress(void);

/**
  * @brief  蓝牙通信内容
  * @param  无
  * @retval 无
  */
void BLE_Notify(void);

#endif // !__BLE_H