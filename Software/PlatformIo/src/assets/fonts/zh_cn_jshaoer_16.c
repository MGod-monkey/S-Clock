/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ZH_CN_JSHAOER_16
#define ZH_CN_JSHAOER_16 1
#endif

#if ZH_CN_JSHAOER_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x4, 0xbc, 0xdd, 0x90, 0x4, 0xf8, 0x0, 0x8f,
    0xa0, 0xcf, 0x0, 0x0, 0xdf, 0x1f, 0xc0, 0x0,
    0x9, 0xf3, 0xee, 0x0, 0x0, 0xcf, 0x8, 0xf8,
    0x0, 0x6f, 0x90, 0x7, 0xce, 0xed, 0x70, 0x0,

    /* U+0031 "1" */
    0xb, 0xff, 0xa0, 0x0, 0x5, 0xfa, 0x0, 0x0,
    0x3f, 0x80, 0x0, 0x3, 0xf7, 0x0, 0x0, 0x4f,
    0x60, 0x0, 0x6, 0xf6, 0x0, 0x3d, 0xff, 0xfe,
    0x20,

    /* U+0032 "2" */
    0x0, 0x6d, 0xdd, 0x80, 0x2, 0xf7, 0x7, 0xf5,
    0x3, 0xf6, 0x8, 0xf5, 0x0, 0xef, 0xcf, 0xf1,
    0x0, 0x15, 0xcf, 0x60, 0x0, 0x2c, 0xf7, 0x22,
    0x1a, 0xff, 0xff, 0xe7,

    /* U+0033 "3" */
    0x4, 0xff, 0xff, 0xc0, 0x0, 0x1, 0xee, 0x20,
    0x0, 0xc, 0xe3, 0x0, 0x1, 0xcf, 0xc4, 0x0,
    0x5, 0x55, 0xcf, 0x60, 0x0, 0x0, 0x3f, 0x90,
    0x4, 0x20, 0x8f, 0x30, 0x7, 0xbb, 0x92, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0xce, 0x10, 0x0, 0x0, 0x7f, 0xf2,
    0x0, 0x0, 0x2e, 0xbf, 0x20, 0x0, 0xb, 0x79,
    0xf2, 0x0, 0x5, 0xd0, 0x9f, 0x10, 0x1, 0xe8,
    0x1b, 0xf3, 0x10, 0x9f, 0xff, 0xff, 0xfd, 0x0,
    0x0, 0xb, 0xf0, 0x0, 0x0, 0x0, 0x9d, 0x0,
    0x0, 0x0, 0x0, 0x10, 0x0,

    /* U+0035 "5" */
    0x0, 0x4, 0xed, 0x30, 0x0, 0x1e, 0xec, 0xd0,
    0x0, 0xaf, 0x43, 0xf4, 0x5, 0xfd, 0x10, 0x71,
    0x2, 0x3b, 0xf3, 0x0, 0x0, 0x2, 0xfb, 0x0,
    0x21, 0x5, 0xf8, 0x0, 0x4c, 0xbb, 0x60, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x9f, 0x90,
    0x0, 0x2d, 0xe6, 0x0, 0x1, 0xec, 0x10, 0x0,
    0xa, 0xf9, 0xde, 0x60, 0x2f, 0x80, 0x1b, 0xf1,
    0x5f, 0x40, 0x4, 0xf4, 0x4f, 0x60, 0x5, 0xf1,
    0x1f, 0xd3, 0x5e, 0x90, 0x5, 0xef, 0xd6, 0x0,

    /* U+0037 "7" */
    0x8f, 0xff, 0xff, 0x1, 0x22, 0x7f, 0x70, 0x0,
    0xc, 0xd0, 0x0, 0x5, 0xf4, 0x0, 0x0, 0xec,
    0x0, 0x0, 0x7f, 0x40, 0x0, 0xa, 0x90, 0x0,
    0x0,

    /* U+0038 "8" */
    0x0, 0x5, 0x76, 0x10, 0x3, 0xec, 0x9f, 0xe1,
    0xc, 0xe0, 0x8, 0xf4, 0xf, 0xb0, 0x7, 0xf3,
    0xd, 0xf3, 0x1d, 0xa0, 0x2, 0xef, 0xfe, 0x20,
    0x7, 0xd3, 0x9f, 0xb0, 0xd, 0xb0, 0x3f, 0xa0,
    0x4, 0xcd, 0xeb, 0x10,

    /* U+0039 "9" */
    0x0, 0x7d, 0xfb, 0x10, 0x9, 0xf8, 0x9f, 0xc0,
    0x1f, 0x50, 0x6, 0xf3, 0x4f, 0x10, 0x2, 0xf6,
    0x5f, 0x20, 0x2, 0xf5, 0x2f, 0xb3, 0x49, 0xf1,
    0x8, 0xfe, 0xbf, 0x70, 0x0, 0x7, 0xfa, 0x0,
    0x3, 0xcf, 0x80, 0x0, 0x5, 0x83, 0x0, 0x0,

    /* U+003A ":" */
    0x0, 0x0, 0x1e, 0x40, 0x4, 0x90, 0x0, 0x0,
    0x18, 0x10, 0xa, 0xa0, 0x0, 0x0,

    /* U+4E00 "???" */
    0x0, 0x1, 0x22, 0x33, 0x33, 0x33, 0x10, 0x6e,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3b, 0xcc,
    0xdd, 0xdd, 0xdc, 0xcb, 0x92,

    /* U+4E09 "???" */
    0x0, 0x0, 0x1, 0x12, 0x23, 0x32, 0x0, 0x0,
    0x8e, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x6,
    0xbb, 0xbb, 0xbb, 0xa9, 0x97, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xbc,
    0xdd, 0xee, 0xee, 0xa0, 0x0, 0x1, 0xdf, 0xff,
    0xff, 0xfe, 0xd9, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x58, 0x9a, 0xab, 0xbc, 0xcc,
    0xcc, 0x90, 0x2f, 0xff, 0xff, 0xff, 0xee, 0xed,
    0xda, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+4E8C "???" */
    0x0, 0x0, 0x1, 0x12, 0x22, 0x21, 0x0, 0x0,
    0x4e, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x0, 0x3,
    0xcd, 0xde, 0xee, 0xdc, 0xb9, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x12, 0x23,
    0x33, 0x32, 0x0, 0x3c, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0x4, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xfd, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0,

    /* U+4E94 "???" */
    0x0, 0x4, 0x67, 0x89, 0x9a, 0xba, 0x70, 0x0,
    0x4, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x0, 0x0,
    0x1, 0x23, 0x5f, 0x83, 0x20, 0x0, 0x0, 0x0,
    0x0, 0x5, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0x60, 0x0, 0x0, 0x0, 0x2, 0x9b,
    0xdf, 0xff, 0xed, 0xb4, 0x0, 0x0, 0x8f, 0xff,
    0xff, 0xfe, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x3f,
    0xe0, 0x0, 0xdf, 0x30, 0x0, 0x0, 0x6, 0xfa,
    0x0, 0xc, 0xf3, 0x0, 0x0, 0x0, 0xaf, 0x70,
    0x0, 0xef, 0x10, 0x0, 0x0, 0xd, 0xf4, 0x0,
    0x2f, 0xe0, 0x0, 0x47, 0x8a, 0xff, 0xa9, 0xac,
    0xfe, 0x93, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xee, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+516D "???" */
    0x0, 0x0, 0x1, 0xdd, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x5, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xbb, 0x10, 0x0, 0x0, 0x1, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x0, 0xaf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf6, 0x5b, 0xdd, 0xdd, 0xdd, 0xcc,
    0xba, 0x93, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5, 0x30, 0x0, 0x3, 0x0, 0x0,
    0x0, 0x2f, 0xb0, 0x0, 0xf, 0xd0, 0x0, 0x0,
    0xaf, 0x80, 0x0, 0xa, 0xf9, 0x0, 0x3, 0xff,
    0x10, 0x0, 0x2, 0xff, 0x30, 0xc, 0xf8, 0x0,
    0x0, 0x0, 0x9f, 0xc0, 0x3f, 0xc0, 0x0, 0x0,
    0x0, 0x1e, 0xf1, 0x7, 0x10, 0x0, 0x0, 0x0,
    0x1, 0x50,

    /* U+56DB "???" */
    0x0, 0x2, 0x57, 0x89, 0x98, 0x73, 0x0, 0xac,
    0xef, 0xff, 0xff, 0xff, 0xff, 0x90, 0xbf, 0x77,
    0x6f, 0x57, 0xf3, 0x4d, 0xf4, 0xaf, 0x0, 0x6f,
    0x48, 0xf2, 0x7, 0xf8, 0xaf, 0x20, 0xaf, 0x28,
    0xf2, 0x5, 0xf9, 0x9f, 0x40, 0xee, 0x8, 0xf2,
    0x5, 0xf9, 0x8f, 0x64, 0xfa, 0x7, 0xf3, 0x5,
    0xf8, 0x7f, 0x89, 0xf6, 0x4, 0xfe, 0xc8, 0xf8,
    0x5f, 0x9d, 0xf1, 0x0, 0xaf, 0xd9, 0xf6, 0x4f,
    0xba, 0x70, 0x0, 0x0, 0xa, 0xf4, 0x2f, 0xd0,
    0x0, 0x1, 0x11, 0x1d, 0xf1, 0xf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf2, 0xb, 0xd8, 0x88, 0x88,
    0x77, 0x76, 0x40,

    /* U+65E5 "???" */
    0x0, 0x0, 0x1, 0x23, 0x20, 0x0, 0x1d, 0x6b,
    0xef, 0xff, 0xfd, 0x10, 0x3f, 0xee, 0xca, 0x98,
    0xdf, 0x90, 0x5f, 0x80, 0x0, 0x0, 0x3f, 0xd0,
    0x5f, 0x80, 0x0, 0x0, 0x1f, 0xe0, 0x5f, 0x90,
    0x0, 0x0, 0xf, 0xf0, 0x5f, 0xec, 0xde, 0xff,
    0xaf, 0xf0, 0x4f, 0xed, 0xdc, 0xb9, 0x4f, 0xf0,
    0x4f, 0xa0, 0x0, 0x0, 0xf, 0xf0, 0x4f, 0xa0,
    0x0, 0x0, 0xf, 0xf0, 0x4f, 0xb0, 0x0, 0x0,
    0x1f, 0xe0, 0x3f, 0xb0, 0x0, 0x0, 0x2f, 0xd0,
    0x2f, 0xd7, 0x88, 0x9a, 0xbf, 0xe0, 0x1f, 0xee,
    0xff, 0xee, 0xee, 0xb0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 145, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 135, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 132, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 121, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 117, .adv_w = 130, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 162, .adv_w = 122, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 194, .adv_w = 124, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 335, .adv_w = 47, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 349, .adv_w = 256, .box_w = 14, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 370, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 475, .adv_w = 256, .box_w = 15, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 573, .adv_w = 256, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 678, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 776, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 867, .adv_w = 256, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x9, 0x8c, 0x94, 0x36d, 0x8db, 0x17e5
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 19968, .range_length = 6118, .glyph_id_start = 12,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t zh_cn_jshaoer_16 = {
#else
lv_font_t zh_cn_jshaoer_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ZH_CN_JSHAOER_16*/

