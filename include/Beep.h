#ifndef __BEEP_H
#define __BEEP_H

/**
  * @brief  初识化蜂鸣器
  * @param  无
  * @retval 无
  */
void Beep_Init(void);


/**
  * @brief  蜂鸣器播放
  * @param  无
  * @retval 无
  */
void Beep_Play(void);


/**
  * @brief  获取蜂鸣器播放状态
  * @param  无
  * @retval bool:播放状态
  */
bool Beep_isPlaying(void);


/**
  * @brief  蜂鸣器停止播放
  * @param  无
  * @retval 无
  */
void Beep_Shutdown(void);

#endif // !__BEEP_H