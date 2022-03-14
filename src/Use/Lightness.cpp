#include "Lightness.h"

struct _Lightness_Info Lightness_Info;

void Lightness_Init(void)
{
    Lightness_Info.lightness = LIGHTNESS_MAX;
    Lightness_Info.lightness_percent = 100;
    pinMode(LIGHTNESS_PIN, OUTPUT);
    digitalWrite(LIGHTNESS_PIN, HIGH);
    // dacWrite(LIGHTNESS_PIN, Lightness_Info.lightness);
}

bool Lightness_Status(void)
{
    if (digitalRead(LIGHTNESS_PIN) == HIGH)
        return true;
    return false;
}

void Lightness_Shutdown(void)
{
    Lightness_Info.lightness = 0;
    Lightness_Info.lightness_percent = 0;
    digitalWrite(LIGHTNESS_PIN, LOW);
    // dacWrite(LIGHTNESS_PIN, 0);
}

void Lightness_Open(void)
{
    Lightness_Info.lightness = LIGHTNESS_MAX;
    Lightness_Info.lightness_percent = 100;
    dacWrite(LIGHTNESS_PIN, LIGHTNESS_MAX);
}

void Lightness_setNum(uint8_t lightness)
{
    if (lightness < LIGHTNESS_MIN) 
    {
      Lightness_Info.lightness = LIGHTNESS_MIN;
      Lightness_Info.lightness_percent = 0;
    } else if (lightness >= 100) 
    {
      Lightness_Info.lightness = LIGHTNESS_MAX;
      Lightness_Info.lightness_percent = 100;
    } else
    {
      Lightness_Info.lightness = lightness;
      Lightness_Info.lightness_percent = (uint8_t)((lightness-60)*10/4);
    }
    dacWrite(LIGHTNESS_PIN, Lightness_Info.lightness);
}

void Lightness_setPercent(uint8_t percent)
{
    Lightness_Info.lightness_percent=percent;
    if (percent >= 100)
      Lightness_Info.lightness = LIGHTNESS_MAX;
    else
      Lightness_Info.lightness = (uint8_t)(percent*4/10+60);
    dacWrite(LIGHTNESS_PIN, Lightness_Info.lightness);
}

void Lightness_setMax(void)
{
  Lightness_Info.lightness = LIGHTNESS_MAX;
  Lightness_Info.lightness_percent = 100;
  dacWrite(LIGHTNESS_PIN, LIGHTNESS_MAX);
}

void Lightness_setMin(void)
{
  Lightness_Info.lightness = LIGHTNESS_MIN;
  Lightness_Info.lightness_percent = 0;
  dacWrite(LIGHTNESS_PIN, LIGHTNESS_MIN);
}

uint8_t Lightness_getNum(void)
{
  return Lightness_Info.lightness;
}

uint8_t Lightness_getPercent(void)
{
  return Lightness_Info.lightness_percent;
}