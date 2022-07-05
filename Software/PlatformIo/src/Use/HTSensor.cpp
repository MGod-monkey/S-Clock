#include "Wire.h"
#include "AHTxx.h"
#include "Debug.h"
#include "HTSensor.h"

AHTxx AHT(AHTXX_ADDRESS_X38, AHT2x_SENSOR); //sensor address, sensor type
struct _HTSensor_Info HTSensor_Info;

bool HTSensor_Init()
{
    if (!AHT.begin())
    {
        SCLOCK_LOGLN("[AHT ERROR] Could not find AHT!");
        return false;
    }
    return true;
}

void HTSensor_Update()
{
    float value;
    value = AHT.readTemperature();
    if (value != AHTXX_ERROR)
        HTSensor_Info.temp = value-3.0;
    else
    {
        SCLOCK_LOGLN("[AHT ERROR] AHT Sensor read failed! Reseting!");
        AHT.softReset();
    }
    delay(10);
    value = AHT.readHumidity();
    if (value != AHTXX_ERROR)
        HTSensor_Info.hum = value;
    else
    {
        SCLOCK_LOGLN("[AHT ERROR] AHT Sensor read failed! Reseting!");
        AHT.softReset();
    }
}