#include "Arduino.h"
#include "Clock.h"
#include "Alarm.h"
#include "Weather.h"
#include "Debug.h"
#include "View.h"
#include "HTSensor.h"
#include "ESP/ESP_BLE.h"
#include "ESP/ESP_Save.h"
#include "NimBLEDevice.h"
#include "Menu/Menu_Apps.h"
// #include "ESP/ESP_Save.h"

static struct _BLE_Serve
{
    NimBLEServer* pServer;
    NimBLEService* pClockService;
    NimBLEService* pAlarmService;
    NimBLEService* pSensorService;
    NimBLEService* pWeatherService;
    NimBLEAdvertising* pAdvertising;
}BLE_Server;

struct _BLE_Info BLE_Info;

/**              服务器连接回调函数                   */  
class ServerCallbacks: public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        // SCLOCK_LOGLN("Client connected");
        // SCLOCK_LOGLN("Multi-connect support: start advertising");
        // NimBLEDevice::startAdvertising();
        BLE_Info.ble_status = BLE_CONNECTED;
    };

    void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) {
        SCLOCK_LOG("[ESP BLE] Client address: ");
        SCLOCK_LOGLN(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
        /** We can use the connection handle here to ask for different connection parameters.
         *  Args: connection handle, min connection interval, max connection interval
         *  latency, supervision timeout.
         *  Units; Min/Max Intervals: 1.25 millisecond increments.
         *  Latency: number of intervals allowed to skip.
         *  Timeout: 10 millisecond increments, try for 5x interval time for best results.  
         */
        pServer->updateConnParams(desc->conn_handle, 24, 48, 0, 60);
    };
    void onDisconnect(NimBLEServer* pServer) {
        SCLOCK_LOGLN("[ESP BLE] Client disconnected - start advertising");
        BLE_Info.ble_status = BLE_CONNECTING;
        NimBLEDevice::startAdvertising();
    };
    // void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
    //     SCLOCK_LOGf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
    // };
};

/**                     特征动作的处理程序类                     */
class CharacteristicCallbacks: public NimBLECharacteristicCallbacks {
    // void onRead(NimBLECharacteristic* pCharacteristic){
    //     std::string uuid = pCharacteristic->getUUID().toString();
    //     std::string value = pCharacteristic->getValue();
    //     SCLOCK_LOG(uuid.c_str());
    //     SCLOCK_LOG(": onRead(), value: ");
    //     SCLOCK_LOGLN(value.c_str());
    // };

    void onWrite(NimBLECharacteristic* pCharacteristic) {
        std::string uuid = pCharacteristic->getUUID().toString();
        std::string value = pCharacteristic->getValue();
        // time格式:1200->(12:00)
        if (!uuid.compare(UUID_FULL_NAME(CHARACTERUUID_CLOCK_TIME).c_str()))
        {
            uint8_t hour = (uint8_t)String_Sub_To_Int(value, 0, 2);
            uint8_t minute = (uint8_t)String_Sub_To_Int(value, 2, 2);
            Clock_setTime(hour, minute, 0);
            char buffer[] = "[BLE MESS] set time: hh:mm";
            SCLOCK_LOGLN(Clock_toString(buffer));
            View_Show_Messagebox("消息", "设置时间成功!", 1200);
        }
        // date格式:20220101->(2022/01/01)
        else if (!uuid.compare(UUID_FULL_NAME(CHARACTERUUID_CLOCK_DATE).c_str()))
        {
            uint16_t year = (uint16_t)String_Sub_To_Int(value, 0, 4);
            uint8_t month = (uint8_t)String_Sub_To_Int(value, 4, 2);
            uint8_t day = (uint8_t)String_Sub_To_Int(value, 6, 2);
            Clock_setDate(year, month, day);
            char buffer[] = "[BLE MESS] set date: YY/MM/DD";
            SCLOCK_LOGLN(Clock_toString(buffer));
            View_Show_Messagebox("消息", "设置日期成功!", 1200);
        }
        // 添加闹钟数量
        else if (!uuid.compare(UUID_FULL_NAME(CHARACTERUUID_ALARM_NUM).c_str()))
        {
            uint8_t alarm_num = (uint8_t)String_Sub_To_Int(value, 0, 1);
            SCLOCK_LOG("[BLE MESS] set alarm num: ");
            SCLOCK_LOGLN(alarm_num);
            Alarm_setAlarmNum(alarm_num);
            if (NOW_PAGE == AlarmMenu_Page)
                AlarmMenu_Update();
            else
                View_Show_Messagebox("消息", "添加闹钟数量成功!", 1200);
        } 
        // alarm格式:  如11120010000000
        // 第1个数：闹钟索引 index(1~5)
        // 第2个数：开启或关闭 on:1/off:0
        // 第3~6个数：闹钟时间 1200->12:00
        // 第7个数：闹钟频率格式 freq_mode(1~4)
        // 第8~15个数：选择的星期 choose_days(0000000)分别对应星期日~星期六
        else if (!uuid.compare(UUID_FULL_NAME(CHARACTERUUID_ALARM).c_str()))
        {
            uint8_t index = (uint8_t)String_Sub_To_Int(value, 0, 1);
            Alarm_setFullAlarm(value);
            ESPSave_updateConfig(SAVE_CMD_BLE);
            SCLOCK_LOG("[BLE MESS] set alarm: [");
            SCLOCK_LOG(index);
            char buffer[] = "]hh:mm";
            SCLOCK_LOGLN(Alarm_toString(buffer));
            if (NOW_PAGE == AlarmMenu_Page)
                AlarmMenu_Update();
            View_Show_Messagebox("消息", "设置闹钟成功!", 1200);
        } 
        // 天气格式: 如0guiling或1xxxxxxxxxxx
        // 第一个数：设置天气秘钥或天气城市
        // 后面：
        else if (!uuid.compare(UUID_FULL_NAME(CHARACTERUUID_WEATHER).c_str()))
        {
            uint8_t code = (uint8_t)String_Sub_To_Int(value, 0, 1);
            const char* _value = value.substr(1).c_str();
            if (code != 0)
            {
                Weather_setPrivateKey(_value);
                SCLOCK_LOG("[BLE MESS] set weather private key: ");
                SCLOCK_LOGLN(_value);
                // View_Show_Messagebox("消息", "设置天气城市成功!", 1200);
            }
            else
            {
                Weather_setCity(_value);
                SCLOCK_LOG("[BLE MESS] set weather city: ");
                SCLOCK_LOGLN(_value);
                View_Show_Messagebox("消息", "设置天气城市成功!", 1200);
            }
        }
    };
    // /** Called before notification or indication is sent, 
    //  *  the value can be changed here before sending if desired.
    //  */
    // void onNotify(NimBLECharacteristic* pCharacteristic) {
    //     SCLOCK_LOGLN("Sending notification to clients");
    // };


    // /** The status returned in status is defined in NimBLECharacteristic.h.
    //  *  The value returned in code is the NimBLE host return code.
    //  */
    // void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) {
    //     String str = ("Notification/Indication status code: ");
    //     str += status;
    //     str += ", return code: ";
    //     str += code;
    //     str += ", "; 
    //     str += NimBLEUtils::returnCodeToString(code);
    //     SCLOCK_LOGLN(str);
    // };

    // void onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue) {
    //     String str = "Client ID: ";
    //     str += desc->conn_handle;
    //     str += " Address: ";
    //     str += std::string(NimBLEAddress(desc->peer_ota_addr)).c_str();
    //     if(subValue == 0) {
    //         str += " Unsubscribed to ";
    //     }else if(subValue == 1) {
    //         str += " Subscribed to notfications for ";
    //     } else if(subValue == 2) {
    //         str += " Subscribed to indications for ";
    //     } else if(subValue == 3) {
    //         str += " Subscribed to notifications and indications for ";
    //     }
    //     str += std::string(pCharacteristic->getUUID()).c_str();

    //     SCLOCK_LOGLN(str);
    // };
};

/** Define callback instances globally to use for multiple Charateristics \ Descriptors */ 
static CharacteristicCallbacks chrCallbacks;

/**
  * @brief  蓝牙初识化
  * @param  无
  * @retval 无
  */
void BLE_Init(void){
    /** sets device name */
    NimBLEDevice::init(ESP32_BLE_NAME);

    /** Optional: set the transmit power, default is 3db */
    NimBLEDevice::setPower(ESP_PWR_LVL_P9); /** +9db */

    //NimBLEDevice::setSecurityAuth(false, false, true); 
    NimBLEDevice::setSecurityAuth(/*BLE_SM_PAIR_AUTHREQ_BOND*/BLE_SM_PAIR_AUTHREQ_MITM | BLE_SM_PAIR_AUTHREQ_SC);

    BLE_Server.pServer = NimBLEDevice::createServer();
    BLE_Server.pServer->setCallbacks(new ServerCallbacks());
    BLE_Server.pServer->advertiseOnDisconnect(true); // 设置客户端断开时自动广播
    // 创建时钟服务
    BLE_Server.pClockService = BLE_Server.pServer->createService(SERVICEUUID_CLOCK);
    NimBLECharacteristic* pTimeCharacteristic = BLE_Server.pClockService->createCharacteristic(
                                                CHARACTERUUID_CLOCK_TIME,
                                                NIMBLE_PROPERTY::READ |
                                                NIMBLE_PROPERTY::WRITE
                                              );
    NimBLECharacteristic* pDateCharacteristic = BLE_Server.pClockService->createCharacteristic(
                                                CHARACTERUUID_CLOCK_DATE,
                                                NIMBLE_PROPERTY::READ |
                                                NIMBLE_PROPERTY::WRITE
                                              );
    pTimeCharacteristic->setCallbacks(&chrCallbacks);
    pDateCharacteristic->setCallbacks(&chrCallbacks);

    // NimBLE2904* pBATT2904 = (NimBLE2904*)pCLOCKCharacteristic->createDescriptor("2904",NIMBLE_PROPERTY::READ,20);
    // pBATT2904->setFormat(NimBLE2904::FORMAT_UTF8);
    // pBATT2904->setValue("Smart Clock");
    // pBATT2904->setCallbacks(&dscCallbacks);
    // 创建闹钟服务
    BLE_Server.pAlarmService = BLE_Server.pServer->createService(SERVICEUUID_ALARM);
    NimBLECharacteristic* pAlarmCharacteristic = BLE_Server.pAlarmService->createCharacteristic(
                                               CHARACTERUUID_ALARM,
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::WRITE|
                                               NIMBLE_PROPERTY::NOTIFY
                                              );
    NimBLECharacteristic* pAlarmNumCharacteristic = BLE_Server.pAlarmService->createCharacteristic(
                                               CHARACTERUUID_ALARM_NUM,
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::WRITE|
                                               NIMBLE_PROPERTY::NOTIFY
                                              );
    BLE_Info.last_alarm_num = 0;
    // SCLOCK_LOGLN(Alarm_toCSVStr());
    // pAlarmNumCharacteristic->setValue(BLE_Info.last_alarm_num);
    // pAlarmCharacteristic->setValue(Alarm_toCSVStr());
    pAlarmCharacteristic->setCallbacks(&chrCallbacks);
    pAlarmNumCharacteristic->setCallbacks(&chrCallbacks);
    NimBLEDescriptor* pAlarmdsc = pAlarmCharacteristic->createDescriptor(
                                               "2901",
                                               NIMBLE_PROPERTY::READ,
                                               10);
    pAlarmdsc->setValue("Alarm");
    // pAlarmdsc->setCallbacks(&dscCallbacks);
    // 创建传感器服务
    BLE_Server.pSensorService = BLE_Server.pServer->createService(SERVICEUUID_SENSOR);
    NimBLECharacteristic* pTempCharacteristic = BLE_Server.pSensorService->createCharacteristic(
                                               CHARACTERUUID_SENSOR_TEMP,
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::NOTIFY
                                              );
    NimBLECharacteristic* pHumCharacteristic = BLE_Server.pSensorService->createCharacteristic(
                                               CHARACTERUUID_SENSOR_HUM,
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::NOTIFY
                                              );

    // pAlarmCharacteristic->setValue(batteryLevel);
    // pAlarmCharacteristic->notify(true);
    pTempCharacteristic->setCallbacks(&chrCallbacks);
    pHumCharacteristic->setCallbacks(&chrCallbacks);
    NimBLEDescriptor* pTempdsc = pTempCharacteristic->createDescriptor(
                                               "2901",
                                               NIMBLE_PROPERTY::READ,
                                               15);
    pTempdsc->setValue("Tempreature");
    NimBLEDescriptor* pHumdsc = pHumCharacteristic->createDescriptor(
                                               "2901",
                                               NIMBLE_PROPERTY::READ,
                                               15);
    pHumdsc->setValue("Humidity");
    // 创建天气服务
    BLE_Server.pWeatherService = BLE_Server.pServer->createService(SERVICEUUID_WEATHER);
    NimBLECharacteristic* pWeatherCharacteristic = BLE_Server.pWeatherService->createCharacteristic(
                                               CHARACTERUUID_WEATHER,
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::WRITE
                                              );
    pWeatherCharacteristic->setCallbacks(&chrCallbacks);
    NimBLEDescriptor* pWeatherdsc = pWeatherCharacteristic->createDescriptor(
                                               "2901",
                                               NIMBLE_PROPERTY::READ,
                                               10);
    pWeatherdsc->setValue("Weather");

    /** Start the services when finished creating all Characteristics and Descriptors */  
    BLE_Server.pClockService->start();
    BLE_Server.pAlarmService->start();
    BLE_Server.pSensorService->start();
    BLE_Server.pWeatherService->start();
    // 开启广播
    BLE_Server.pAdvertising = NimBLEDevice::getAdvertising();
    /** Add the services to the advertisment data **/
    BLE_Server.pAdvertising->addServiceUUID(BLE_Server.pClockService->getUUID());
    BLE_Server.pAdvertising->addServiceUUID(BLE_Server.pAlarmService->getUUID());
    BLE_Server.pAdvertising->addServiceUUID(BLE_Server.pSensorService->getUUID());
    /** If your device is battery powered you may consider setting scan response
     *  to false as it will extend battery life at the expense of less data sent.
     */
    BLE_Server.pAdvertising->setScanResponse(false);
    BLE_Server.pAdvertising->start();
    BLE_Info.ble_status = BLE_CONNECTING;
    BLE_Info.ble_adv = true;
}

/**
  * @brief  重置蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_resetAdvert(void)
{
    BLE_Server.pAdvertising->reset();
    BLE_Info.ble_status = BLE_CONNECTING;
    BLE_Info.ble_adv = true;
}

/**
  * @brief  关闭蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_closeAdvert(void)
{
    if (BLE_Server.pAdvertising->isAdvertising())
    {
        BLE_Server.pAdvertising->stop();
    }
    BLE_Info.ble_status = BLE_CLOSE;
    BLE_Info.ble_adv = false;
}

/**
  * @brief  开启蓝牙广播
  * @param  无
  * @retval 无
  */
void BLE_openAdvert(void)
{
    if (BLE_Server.pAdvertising->isAdvertising())
        BLE_Server.pAdvertising->reset();
    else
        BLE_Server.pAdvertising->start();
    BLE_Info.ble_status = BLE_CONNECTING;
    BLE_Info.ble_adv = true;
}

/**
  * @brief  返回蓝牙广播状态
  * @param  无
  * @retval 广播状态：bool
  */
bool BLE_isAdvertising(void)
{
    return BLE_Server.pAdvertising->isAdvertising();
}

/**
  * @brief  返回蓝牙连接状态
  * @param  无
  * @retval 连接状态：bool
  */
bool BLE_isConnected(void)
{
    if (BLE_Server.pServer->getConnectedCount())
        return true;
    return false;
}

/**
  * @brief  返回蓝牙设备名称
  * @param  无
  * @retval 名称: const char*
  */
const char* BLE_getDeviceName(void)
{
    return ESP32_BLE_NAME;
}

/**
  * @brief  返回蓝牙地址
  * @param  无
  * @retval Address: const char*
  */
const char* BLE_getAddress(void)
{
    return NimBLEDevice::toString().c_str();
}

/**
  * @brief  蓝牙通信内容
  * @param  无
  * @retval 无
  */
void BLE_Notify(void)
{
    if(BLE_Server.pServer->getConnectedCount()) {
        NimBLEService* pSvc = nullptr;
        NimBLECharacteristic* pChr=nullptr;
        std::string t;
        // if (Alarm_Info.alarm_num != BLE_Info.last_alarm_num)
        // {
        //     BLE_Info.last_alarm_num = Alarm_Info.alarm_num;
        //     pSvc = BLE_Server.pServer->getServiceByUUID(SERVICEUUID_ALARM);
        //     if (pSvc)
        //     {
        //         pChr = pSvc->getCharacteristic(CHARACTERUUID_ALARM_NUM);
        //         if (pChr)
        //         {
        //             t = String(BLE_Info.last_alarm_num).c_str();
        //             pChr->setValue(t);
        //             pChr->notify(true);
        //         }
        //     }
        // }
        pSvc = BLE_Server.pServer->getServiceByUUID(SERVICEUUID_ALARM);
        if (pSvc)
        {
            pChr = pSvc->getCharacteristic(CHARACTERUUID_ALARM_NUM);
            if (pChr)
            {
                t = String(Alarm_Info.alarm_num).c_str();
                pChr->setValue(t);
                pChr->notify(true);
            }
        }
        pSvc = BLE_Server.pServer->getServiceByUUID(SERVICEUUID_SENSOR);
        if(pSvc) {
            pChr = pSvc->getCharacteristic(CHARACTERUUID_SENSOR_TEMP);
            if(pChr) {
                t = String((int)HTSensor_Info.temp).c_str();
                pChr->setValue(t);
                pChr->notify(true);
            }
            pChr = pSvc->getCharacteristic(CHARACTERUUID_SENSOR_HUM);
            if(pChr) {
                t = String((int)HTSensor_Info.hum).c_str();
                pChr->setValue(t);
                pChr->notify(true);
            }
        }
    }
}