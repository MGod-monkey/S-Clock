#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif
#ifndef LV_ATTRIBUTE_IMG_ICON_WIFI_ON
#define LV_ATTRIBUTE_IMG_ICON_WIFI_ON
#endif
const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_ICON_WIFI_ON uint8_t icon_wifi_on_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x19, 0x37, 0x33, 0x37, 0x33, 0x37, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x37, 0x36, 0x37, 0xbc, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xbc, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x37, 0x55, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xdf, 0x37, 0xdc, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0x55, 0x00, 0x00, 
  0x00, 0x00, 0x37, 0xd2, 0x37, 0xff, 0x37, 0x84, 0x37, 0x38, 0x17, 0x22, 0x37, 0x2e, 0x37, 0x27, 0x37, 0x58, 0x37, 0xff, 0x37, 0xd2, 0x00, 0x00, 
  0x37, 0x18, 0x37, 0xff, 0x37, 0x6a, 0x37, 0x49, 0x37, 0xdb, 0x37, 0xdc, 0x37, 0xdd, 0x37, 0xff, 0x37, 0x8a, 0x17, 0x3f, 0x37, 0xff, 0x37, 0x18, 
  0x17, 0x31, 0x37, 0xff, 0x37, 0xff, 0x37, 0x5f, 0x17, 0x1f, 0x17, 0x2f, 0x37, 0x1c, 0x17, 0x15, 0x37, 0x53, 0x37, 0xff, 0x37, 0xff, 0x17, 0x31, 
  0x17, 0x31, 0x37, 0xff, 0x37, 0xff, 0x37, 0xbf, 0x37, 0xe9, 0x37, 0xf0, 0x37, 0xf8, 0x37, 0xff, 0x37, 0xaa, 0x37, 0xdc, 0x37, 0xff, 0x17, 0x31, 
  0x37, 0x18, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x00, 0x00, 0x37, 0x72, 0x37, 0x6c, 0x00, 0x00, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0x18, 
  0x00, 0x00, 0x37, 0xd2, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0x73, 0x37, 0x80, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xd2, 0x00, 0x00, 
  0x00, 0x00, 0x37, 0x55, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0x73, 0x37, 0x80, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0x55, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x37, 0x36, 0x37, 0xbc, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xff, 0x37, 0xbc, 0x37, 0x36, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x19, 0x37, 0x33, 0x37, 0x33, 0x37, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x14, 0x19, 0xbb, 0x14, 0x33, 0xbb, 0x14, 0x33, 0xdc, 0x14, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x14, 0x36, 0xdb, 0x14, 0xbc, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0xbc, 0xdb, 0x14, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xbb, 0x14, 0x55, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xdf, 0xbb, 0x14, 0xdc, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x55, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xdb, 0x14, 0xd2, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0x84, 0xbb, 0x14, 0x38, 0xbb, 0x14, 0x22, 0xbc, 0x14, 0x2e, 0xbc, 0x14, 0x27, 0xdb, 0x14, 0x58, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0xd2, 0x00, 0x00, 0x00, 
  0xbc, 0x1c, 0x18, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x6a, 0xbb, 0x14, 0x49, 0xbb, 0x14, 0xdb, 0xdb, 0x14, 0xdc, 0xbb, 0x14, 0xdd, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x8a, 0xbb, 0x14, 0x3f, 0xbb, 0x14, 0xff, 0xbc, 0x1c, 0x18, 
  0xdb, 0x14, 0x31, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x5f, 0xbc, 0x14, 0x1f, 0x9b, 0x14, 0x2f, 0xfb, 0x14, 0x1c, 0x9b, 0x0c, 0x15, 0xdb, 0x14, 0x53, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0x31, 
  0xdb, 0x14, 0x31, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xbf, 0xbb, 0x14, 0xe9, 0xbb, 0x14, 0xf0, 0xbb, 0x14, 0xf8, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xaa, 0xbb, 0x14, 0xdc, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0x31, 
  0xbc, 0x1c, 0x18, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0x00, 0x00, 0x00, 0xbb, 0x14, 0x72, 0xdb, 0x14, 0x6c, 0x00, 0x00, 0x00, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbc, 0x1c, 0x18, 
  0x00, 0x00, 0x00, 0xdb, 0x14, 0xd2, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0x73, 0xbb, 0x14, 0x80, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0xd2, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xbb, 0x14, 0x55, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x73, 0xbb, 0x14, 0x80, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0x55, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x14, 0x36, 0xdb, 0x14, 0xbc, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xbb, 0x14, 0xff, 0xdb, 0x14, 0xbc, 0xdb, 0x14, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x14, 0x19, 0xbb, 0x14, 0x33, 0xbb, 0x14, 0x33, 0xdc, 0x14, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xdc, 0x19, 0x14, 0xbb, 0x33, 0x14, 0xbb, 0x33, 0x14, 0xdc, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xdb, 0x36, 0x14, 0xdb, 0xbc, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0xbc, 0x14, 0xdb, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x14, 0xbb, 0x55, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xdf, 0x14, 0xbb, 0xdc, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x55, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x14, 0xdb, 0xd2, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0x84, 0x14, 0xbb, 0x38, 0x14, 0xbb, 0x22, 0x14, 0xbc, 0x2e, 0x14, 0xbc, 0x27, 0x14, 0xdb, 0x58, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0xd2, 0x00, 0x00, 0x00, 
  0x1c, 0xbc, 0x18, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x6a, 0x14, 0xbb, 0x49, 0x14, 0xbb, 0xdb, 0x14, 0xdb, 0xdc, 0x14, 0xbb, 0xdd, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x8a, 0x14, 0xbb, 0x3f, 0x14, 0xbb, 0xff, 0x1c, 0xbc, 0x18, 
  0x14, 0xdb, 0x31, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x5f, 0x14, 0xbc, 0x1f, 0x14, 0x9b, 0x2f, 0x14, 0xfb, 0x1c, 0x0c, 0x9b, 0x15, 0x14, 0xdb, 0x53, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0x31, 
  0x14, 0xdb, 0x31, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xbf, 0x14, 0xbb, 0xe9, 0x14, 0xbb, 0xf0, 0x14, 0xbb, 0xf8, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xaa, 0x14, 0xbb, 0xdc, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0x31, 
  0x1c, 0xbc, 0x18, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x00, 0x00, 0x00, 0x14, 0xbb, 0x72, 0x14, 0xdb, 0x6c, 0x00, 0x00, 0x00, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x1c, 0xbc, 0x18, 
  0x00, 0x00, 0x00, 0x14, 0xdb, 0xd2, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0x73, 0x14, 0xbb, 0x80, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0xd2, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x14, 0xbb, 0x55, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x73, 0x14, 0xbb, 0x80, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0x55, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xdb, 0x36, 0x14, 0xdb, 0xbc, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xbb, 0xff, 0x14, 0xdb, 0xbc, 0x14, 0xdb, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xdc, 0x19, 0x14, 0xbb, 0x33, 0x14, 0xbb, 0x33, 0x14, 0xdc, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x99, 0x14, 0x19, 0xdc, 0x96, 0x14, 0x33, 0xdc, 0x96, 0x14, 0x33, 0xe0, 0x99, 0x14, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd9, 0x97, 0x13, 0x36, 0xda, 0x97, 0x12, 0xbc, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xda, 0x97, 0x12, 0xbc, 0xd9, 0x97, 0x13, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xdb, 0x96, 0x12, 0x55, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdc, 0x96, 0x12, 0xdf, 0xdb, 0x96, 0x11, 0xdc, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0x55, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xdb, 0x97, 0x12, 0xd2, 0xdb, 0x96, 0x12, 0xff, 0xda, 0x97, 0x11, 0x84, 0xdb, 0x96, 0x12, 0x38, 0xda, 0x96, 0x0f, 0x22, 0xde, 0x96, 0x11, 0x2e, 0xde, 0x96, 0x14, 0x27, 0xdc, 0x97, 0x11, 0x58, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x97, 0x12, 0xd2, 0x00, 0x00, 0x00, 0x00, 
  0xdf, 0x95, 0x15, 0x18, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x95, 0x11, 0x6a, 0xdc, 0x96, 0x11, 0x49, 0xdb, 0x96, 0x11, 0xdb, 0xdb, 0x97, 0x13, 0xdc, 0xda, 0x96, 0x12, 0xdd, 0xdb, 0x96, 0x12, 0xff, 0xdc, 0x96, 0x12, 0x8a, 0xdb, 0x96, 0x10, 0x3f, 0xdb, 0x96, 0x12, 0xff, 0xdf, 0x95, 0x15, 0x18, 
  0xdb, 0x97, 0x10, 0x31, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdc, 0x96, 0x13, 0x5f, 0xde, 0x94, 0x10, 0x1f, 0xd9, 0x92, 0x10, 0x2f, 0xdb, 0x9b, 0x12, 0x1c, 0xdb, 0x92, 0x0c, 0x15, 0xda, 0x97, 0x12, 0x53, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x97, 0x10, 0x31, 
  0xdb, 0x97, 0x10, 0x31, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x11, 0xbf, 0xdb, 0x96, 0x12, 0xe9, 0xdb, 0x96, 0x12, 0xf0, 0xdb, 0x96, 0x11, 0xf8, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xaa, 0xdb, 0x96, 0x13, 0xdc, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x97, 0x10, 0x31, 
  0xdf, 0x95, 0x15, 0x18, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x96, 0x12, 0x72, 0xdc, 0x97, 0x13, 0x6c, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdf, 0x95, 0x15, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0xdb, 0x97, 0x12, 0xd2, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdc, 0x97, 0x12, 0x73, 0xd9, 0x95, 0x12, 0x80, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x97, 0x12, 0xd2, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xdb, 0x96, 0x12, 0x55, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdc, 0x95, 0x12, 0x73, 0xd9, 0x95, 0x12, 0x80, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0x55, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd9, 0x97, 0x13, 0x36, 0xda, 0x97, 0x12, 0xbc, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xdb, 0x96, 0x12, 0xff, 0xda, 0x97, 0x12, 0xbc, 0xd9, 0x97, 0x13, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x99, 0x14, 0x19, 0xdc, 0x96, 0x14, 0x33, 0xdc, 0x96, 0x14, 0x33, 0xe0, 0x99, 0x14, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t icon_wifi_on = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 12,
  .header.h = 12,
  .data_size = 144 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = icon_wifi_on_map,
};
