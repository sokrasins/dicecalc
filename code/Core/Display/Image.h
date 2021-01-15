/*
 * Imahe.h
 *
 *  Created on: Jan 14, 2021
 *      Author: sok
 */

#ifndef DISPLAY_IMAGE_H_
#define DISPLAY_IMAGE_H_

#include <stdint.h>

#include "fonts.h"

/**
 * Display rotate
**/
#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

/**
 * Display Flip
**/
enum MirrorType {
    MIRROR_NONE  = 0x00,
    MIRROR_HORIZONTAL = 0x01,
    MIRROR_VERTICAL = 0x02,
    MIRROR_ORIGIN = 0x03,
};
#define MIRROR_IMAGE_DFT MIRROR_NONE

/**
 * image color
**/
#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

//4 Gray level
#define  GRAY1 0x03 //Blackest
#define  GRAY2 0x02
#define  GRAY3 0x01 //gray
#define  GRAY4 0x00 //white

/**
 * The size of the point
**/
enum PointSize {
    POINT_SIZE_1X1  = 1,	// 1 x 1
	POINT_SIZE_2X2, 		// 2 X 2
	POINT_SIZE_3X3,			// 3 X 3
	POINT_SIZE_4X4,			// 4 X 4
	POINT_SIZE_5X5, 		// 5 X 5
	POINT_SIZE_6X6, 		// 6 X 6
	POINT_SIZE_7X7, 		// 7 X 7
	POINT_SIZE_8X8, 		// 8 X 8
};
#define POINT_SIZE_DEFAULT  POINT_SIZE_1X1	//Default dot pilex

/**
 * Point size fill style
**/
enum PointStyle {
    POINT_STYLE_AROUND = 1,		// dot pixel 1 x 1
    POINT_STYLE_RIGHTUP, 		// dot pixel 2 X 2
};
#define POINT_STYLE_DEFAULT  POINT_STYLE_AROUND  //Default dot pilex

/**
 * Line style, solid or dashed
**/
enum LineStyle {
    LINE_STYLE_SOLID = 0,
    LINE_STYLE_DOTTED,
};

/**
 * Whether the graphic is filled
**/
enum FillStyle {
    DRAW_FILL_EMPTY = 0,
    DRAW_FILL_FULL,
};

/**
 * Custom structure of a time attribute
**/
typedef struct {
	uint16_t Year;  //0000
    uint8_t  Month; //1 - 12
    uint8_t  Day;   //1 - 30
    uint8_t  Hour;  //0 - 23
    uint8_t  Min;   //0 - 59
    uint8_t  Sec;   //0 - 59
} Time;

#define IMAGE_SIZE 4000

class Image {
	uint8_t m_img[IMAGE_SIZE];

	uint16_t m_width;
	uint16_t m_height;
	uint16_t m_width_mem;
	uint16_t m_height_mem;
	uint16_t m_width_byte;
	uint16_t m_height_byte;

	uint16_t m_rotate;
	uint8_t m_mirror;
	uint8_t m_scale;
	uint16_t m_color;

public:
	Image();
	Image(uint16_t width, uint16_t height, uint8_t rotate, uint16_t color);

	void set_size(uint16_t width, uint16_t height);
	void set_rotation(uint16_t rotation);
	void set_mirroring(uint8_t mirror);
	void set_color(uint16_t color);
	void set_scale(uint8_t scale);

	void set_pixel(uint16_t x, uint16_t y, uint16_t color);
	void clear(uint16_t color);
	void clear_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

	void draw_point(uint16_t x, uint16_t y, uint16_t color, PointSize weight, PointStyle style);
	void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, PointSize weight, LineStyle style);
	void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, PointSize weight, FillStyle style);
	void draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color, PointSize weight, FillStyle style);

	void draw_char(uint16_t x, uint16_t y, const char ascii_char, sFONT* Font, uint16_t fg_color, uint16_t bg_color);
	void draw_string(uint16_t x, uint16_t y, const char * string, sFONT* Font, uint16_t fg_color, uint16_t bg_color);
	void draw_num(uint16_t x, uint16_t y, int32_t num, sFONT* Font, uint16_t fg_color, uint16_t bg_color);
	void draw_time(uint16_t x, uint16_t y, Time *time, sFONT* Font, uint16_t fg_color, uint16_t bg_color);

	void draw_bitmap(const unsigned char* image_buffer);
	void draw_bitmap_block(const unsigned char* image_buffer, uint8_t region);
};

#endif /* DISPLAY_IMAGE_H_ */
