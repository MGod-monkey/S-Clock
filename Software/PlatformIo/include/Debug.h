#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "Arduino.h"
#include "globalConfig.h"

// static void serialPrint(const char c[]){
//     #ifdef DEBUG_FLAG
//         Serial.print(c);
//     #endif
// }

// static void serialPrint(const String &s){
//     #ifdef DEBUG_FLAG
//         Serial.print(s);
//     #endif
// }

// static void serialPrint(int num){
//     #ifdef DEBUG_FLAG
//         Serial.print(num);
//     #endif
// }

// static void serialPrint(uint8_t num){
//     #ifdef DEBUG_FLAG
//         Serial.print(num);
//     #endif
// }

// static void serialPrint(uint16_t num){
//     #ifdef DEBUG_FLAG
//         Serial.print(num);
//     #endif
// }

// static void serialPrint(uint32_t num){
//     #ifdef DEBUG_FLAG
//         Serial.print(num);
//     #endif
// }

// static void serialPrint(long num){
//     #ifdef DEBUG_FLAG
//         Serial.print(num);
//     #endif
// }

// static void serialPrintln(const char c[]){
//     #ifdef DEBUG_FLAG
//         Serial.println(c);
//     #endif
// }

// static void serialPrintln(const String &s){
//     #ifdef DEBUG_FLAG
//         Serial.println(s);
//     #endif
// }

// static void serialPrintln(int num){
//     #ifdef DEBUG_FLAG
//         Serial.println(num);
//     #endif
// }

// static void serialPrintln(uint8_t num){
//     #ifdef DEBUG_FLAG
//         Serial.println(num);
//     #endif
// }

// static void serialPrintln(uint16_t num){
//     #ifdef DEBUG_FLAG
//         Serial.println(num);
//     #endif
// }

// static void serialPrintln(uint32_t num){
//     #ifdef DEBUG_FLAG
//         Serial.println(num);
//     #endif
// }

// static void serialPrintln(long num){
//     #ifdef DEBUG_FLAG
//         Serial.println(num);
//     #endif
// }

#if DEBUG_FLAG
    #define SCLOCK_LOG(x)   Serial.print(x)
    #define SCLOCK_LOGLN(x) Serial.println(x)
#else
    #define SCLOCK_LOG(x)   Serial.flash()
    #define SCLOCK_LOGLN(x) Serial.flash()
#endif // DEBUG


/**
  * @brief  截取字符串，输出整型
  * @param  std::string:要截取的字符串
  * @param  uint16_t:起始位置
  * @param  size_t:截取的长度
  * @retval char*:字符串首地址
  */
long String_Sub_To_Int(std::string str, uint16_t start_pos, size_t size);


/**
  * @brief  截取字符串指定位置后的字符串，输出字符串
  * @param  std::string:要截取的字符串
  * @param  uint16_t:起始位置
  * @retval char*:字符串首地址
  */
const char* String_Sub_To_Str(std::string str, uint16_t start_pos);


/**
  * @brief  截取字符串，输出字符串
  * @param  std::string:要截取的字符串
  * @param  uint16_t:起始位置
  * @param  size_t:截取的长度
  * @retval char*:字符串首地址
  */
const char* String_Sub_To_Str(std::string str, uint16_t start_pos, size_t size);

#endif // !_DEBUG_H_