#ifndef _ESP_KEY_H_
#define _ESP_KEY_H_

enum
{
	KEY_NO_PRES   = 0,
	KEY_OK_PRES   = 1,
	KEY_NEXT_PRES = 2,
	KEY_PREV_PRES = 3
};

void Key_Init(void);
uint8_t Key_Scan();

#endif