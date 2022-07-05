#ifndef __HTSENSOR_H
#define __HTSENSOR_H

// #include "Debug.h"
// #include "Adafruit_AHTX0.h"

// Adafruit_AHTX0 AHT;
// static sensors_event_t Hum, Temp;
// struct _HTSensor
// {
//     float temp;
//     float hum;
// } HTSensor;

// // 函数声明
// bool AHT_Init(void);
// void AHT_Update(void);

// bool AHT_Init(void)
// {
//     if (! AHT.begin())
//     {
//         SCLOCK_LOGLN("[AHT ERROR]Could not find AHT!");
//         return false;
//     }
//     return true;
// }

// void AHT_Update(void)
// {
//     AHT.getEvent(&Hum, &Temp);
//     HTSensor.temp = Temp.temperature;
//     HTSensor.hum = Hum.relative_humidity;
// }


// #ifdef  SENSOR_AHTxx

 struct _HTSensor_Info
  {
      float temp;
      float hum;
  };

extern struct _HTSensor_Info HTSensor_Info;

/**
  * @brief  温湿度传感器初识化
  * @param  无
  * @retval bool:初识化成功状态
  */
  bool HTSensor_Init();

  /**
  * @brief  温湿度传感器刷新数值
  * @param  无
  * @retval 无
  */
  void HTSensor_Update();

// #else

// #include "Wire.h"
// #include "SHT3x.h"
// #include "Debug.h"

// SHT3x SHT(0x45); //Set the address by hands

//   struct _HTSensor_Info
//   {
//       float temp;
//       float hum;
//   } HTSensor_Info;

//   // 函数声明
//   bool HTSensor_Init();
//   void HTSensor_Update();

//   /**
//   * @brief  初识化传感器
//   * @param  无
//   * @retval bool:初识化成功状态
//   */
//   bool HTSensor_Init()
//   {
//     SHT.SetUpdateInterval(1000);
//     SHT.Begin();
//     if (SHT._Error != noError)
//     {
//       Serial.println("[SHT ERROR] SHT init failed!");
//       return false;
//     }
//     return true;
//   }

//   /**
//   * @brief  更新温湿度值
//   * @param  无
//   * @retval 无
//   */
//   void HTSensor_Update()
//   {
//       SHT.UpdateData();
//       if (!SHT.GetError())
//       {
//         HTSensor_Info.temp = SHT.GetTemperature();
//         HTSensor_Info.hum = SHT.GetRelHumidity();
//       }
//       else SHT.SoftReset();
//   }

// #endif

#endif