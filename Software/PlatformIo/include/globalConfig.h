/* *********************  全局配置  ************************** */
#ifndef __GLOBALCONFIG_H
#define __GLOBALCONFIG_H

#define DEBUG_FLAG      1 //Debug标识

/**********************
 *     彩屏配置
 **********************/

#define TFT_WIDTH  128  //屏幕宽
#define TFT_HEIGHT 128  //屏幕高
#define USE_LIGHTNESS           //启用背光调节
#define DEFAULT_LIGHTNESS   255 //默认亮度（）


//  #define TFT_RGB_ORDER TFT_RGB  // 颜色排序为RGB
#define TFT_RGB_ORDER TFT_BGR  // 颜色排序为BGR

// 引脚定义
#define TFT_MOSI 19 // SPI的MOSI引脚或叫SDA引脚
#define TFT_SCLK 18 // SPI的时钟引脚
#define TFT_CS   32 // SPI的片选引脚
#define TFT_DC   23 // SPI的指令控制引脚
#define TFT_RST  33 // 重置引脚
#define TFT_BL   26
//#define TFT_RST  -1  // 如果RST引脚接到ESP32的复位引脚

#define TFT_ROTATION_MODE     uint8_t // 屏幕翻转方位，从排针朝上为上，上->下表示像素点从上到下
#define TFT_ROTATION_U        0   // 上->下
#define TFT_ROTATION_R        1   // 右->左
#define TFT_ROTATION_D        2   // 下->上
#define TFT_ROTATION_L        3   // 左->右

/**********************
 *     编码器配置(或多功能按键)
 **********************/
#define USE_KEY        // 使用多功能按键
// #define USE_RENCODER    // 使用编码器
#define RotaryPinA 17
#define RotaryPinB 16
#define ClickedPin 13

/**********************
 *     蜂鸣器配置
 **********************/
#define BuzzerPin 4

/**********************
 *     DS1307配置
 **********************/
#define RTC_SDA 21
#define RTC_SCL 22

/**********************
 *  温湿度传感器配置
 **********************/
// #define SENSOR_SHTxx    //SHTxx温度传感器
#define SENSOR_AHTxx    //AHTxx温度传感器

/**********************
 *     闹钟配置
 **********************/
#define DEFALUT_SLEEP_OPEN       true                 // 默认开启贪睡模式
#define DEFAULT_ALARM_NUM        1                    // 默认闹钟数量
#define DEFAULT_ALARM            "1120010000000"      // 默认闹铃格式

/**********************
 *     蓝牙配置
 **********************/
#define DEFAULT_BLE_OPEN    true                     // 默认开启蓝牙

/**********************
 *     Wifi配置
 **********************/
// #define DEFAULT_WIFI_OPEN   true                     // 默认开启wifi
#define WIFI_SSID   "mi"
#define WIFI_PASSWD "wpq5201314"
#define WIFI_SMARTCONFIG_TIMEOUT   60*1000   // 智能配网超时时间(ms)
#define WIFI_CONNECT_TIMEOUT       5*1000    // wifi连接超时时间(ms)

/**********************
 *     天气配置
 **********************/
#define HOST                  "api.seniverse.com"
#define DEFAULT_PRIVATE_KEY   "SdZjOV5WU3kXzlQkD"   // 查看你的API密匙https://www.seniverse.com/dashboard
#define DEFAULT_CITY          "guigang"             // 默认城市

/**********************
 *     息屏配置
 **********************/
#define DEFALUT_SLEEP_MODE        0           // 默认休眠方式(0:深度睡眠, 1:息屏)
#define DEFAULT_SLEEP_MAX_TIMER   0          // 默认最大无操纵息屏时间(s)


#endif