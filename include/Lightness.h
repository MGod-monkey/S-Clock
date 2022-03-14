#ifndef __LIGHTNESS_H
#define __LIGHTNESS_H

#include "Arduino.h"
#include "stdint.h"
#include "globalConfig.h"

#define LIGHTNESS_PIN TFT_BL
#define LIGHTNESS_MAX 255
#define LIGHTNESS_MIN 60

// #ifdef USE_LIGHTNESS

struct _Lightness_Info
{
    uint8_t lightness;
    uint8_t lightness_percent;
};

extern struct _Lightness_Info Lightness_Info;

/**
  * @brief  初识化背光引脚
  * @param  无
  * @retval 无
  */
void Lightness_Init(void);


/**
  * @brief  返回背光状态
  * @param  无
  * @retval bool:背光状态
  */
bool Lightness_Status(void);


/**
  * @brief  关闭背光
  * @param  无
  * @retval 无
  */
void Lightness_Shutdown(void);


/**
  * @brief  打开背光
  * @param  无
  * @retval 无
  */
void Lightness_Open(void);


/**
  * @brief  根据数值调节背光
  * @param  lightness:亮度值（0~250）（实际60~100区间变化明显）
  * @retval 无
  */
void Lightness_setNum(uint8_t lightness);


/**
  * @brief  根据百分比调节背光
  * @param  percent:亮度百分比值（0~100）
  * @retval 无
  */
void Lightness_setPercent(uint8_t percent);

/**
  * @brief  设置背光最大亮度
  * @retval 无
  */
void Lightness_setMax(void);

/**
  * @brief  设置背光最最小亮度
  * @retval 无
  */
void Lightness_setMax(void);

/**
  * @brief  获取亮度值
  * @retval 无
  */
uint8_t Lightness_getNum(void);

/**
  * @brief  获取亮度百分比值
  * @retval 无
  */
uint8_t Lightness_getPercent(void);


#endif