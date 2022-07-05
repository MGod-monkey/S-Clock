#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "Debug.h"
#include "Arduino.h"
#include "Lightness.h"
#include "ESP/ESP_Key.h"
#include "globalConfig.h"
#include "ESP/ESP_Sleep.h"
#include "MD_UISwitch.h"
#include "MD_REncoder.h"


#ifdef USE_RENCODER
	static MD_REncoder R = MD_REncoder(RotaryPinA, RotaryPinB);		//旋转编码器
#else
	MD_UISwitch_Digital Key_L(RotaryPinA, (uint8_t)LOW);
	MD_UISwitch_Digital Key_R(RotaryPinB, (uint8_t)LOW);
#endif

void Key_Init(void)
{
	#ifdef	USE_RENCODER
		R.begin();
	#else
		pinMode(RotaryPinA, INPUT_PULLUP);
		pinMode(RotaryPinB, INPUT_PULLUP);
		// Key_L.begin();
		// Key_R.begin();
		Key_L.enableDoublePress(false);	// 是否允许双击
		Key_L.enableLongPress(false);	// 是否允许长按
		Key_R.enableDoublePress(false);	// 是否允许双击
		Key_R.enableLongPress(false);	// 是否允许长按
	#endif
	pinMode(ClickedPin, INPUT_PULLUP);
}

#ifdef USE_RENCODER

	uint8_t Key_Scan()
	{	

		if (digitalRead(ClickedPin) == LOW)
		{
			SCLOCK_LOGLN("[Navigation] click");
			ESPSleep_Update();
			if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
			{
				// ESPSleep_Info.on_sleep=false;
				// ESPSleep_Close();
				return KEY_NO_PRES;
			}   
			return KEY_OK_PRES;
		}
		uint8_t x = R.read();
		if (x)
		{
			// x == DIR_CW;
			if (x == DIR_CW ) {
				SCLOCK_LOGLN("[Navigation] next"); 
				ESPSleep_Update();
				if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
				{
					ESPSleep_Info.on_sleep=false;
					ESPSleep_Close();
					return KEY_NO_PRES;
				}           
				return KEY_NEXT_PRES;
			}
			else
			{
				SCLOCK_LOGLN("[Navigation] prev");
				ESPSleep_Update();
				if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
				{
					ESPSleep_Info.on_sleep=false;
					ESPSleep_Close();
					return KEY_NO_PRES;
				}  
				return KEY_PREV_PRES;
			}
		}
		return KEY_NO_PRES;
	}
#else
	uint8_t Key_Scan()
	{
		if (digitalRead(ClickedPin) == LOW)
		{
			SCLOCK_LOGLN("[Navigation] click");
			ESPSleep_Update();
			if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
			{
				// ESPSleep_Info.on_sleep=false;
				// ESPSleep_Close();
				return KEY_NO_PRES;
			}   
			return KEY_OK_PRES;
		}
		MD_UISwitch::keyResult_t k_r = Key_R.read();
		MD_UISwitch::keyResult_t k_l = Key_L.read();

		if (k_l == MD_UISwitch::KEY_PRESS)
		{
			SCLOCK_LOGLN("[Navigation] prev");
			ESPSleep_Update();
			if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
			{
				ESPSleep_Close();
				return KEY_NO_PRES;
			}  
			return KEY_PREV_PRES;
		}
		else if (k_r == MD_UISwitch::KEY_PRESS)
		{
			SCLOCK_LOGLN("[Navigation] next"); 
			ESPSleep_Update();
			if (ESPSleep_Status() && ESPSleep_Info.on_sleep)
			{
				ESPSleep_Close();
				return KEY_NO_PRES;
			}           
			return KEY_NEXT_PRES;			
		}
		return KEY_NO_PRES;
	}
#endif

// void lv_indev_focus_group(lv_group_t* group)
// {
	
// }