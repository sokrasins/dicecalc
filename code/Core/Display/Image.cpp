/*
 * Image.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: sok
 */

#include "Image.h"

#include <string.h>

Image::Image() :
m_width(0),
m_height(0),
m_width_mem(0),
m_height_mem(0),
m_width_byte(0),
m_height_byte(0),
m_rotate(ROTATE_0),
m_mirror(MIRROR_NONE),
m_scale(2),
m_color(WHITE)
{
	memset(m_img, 0, IMAGE_SIZE);
}

Image::Image(uint16_t width, uint16_t height, uint8_t rotate, uint16_t color) {
	this->set_rotation(rotate);
	this->set_mirroring(MIRROR_NONE);
	this->set_color(color);
	this->set_scale(2);
	this->set_size(width, height);
}

void Image::set_size(uint16_t width, uint16_t height) {
	this->m_width_mem = width;
	this->m_height_mem = height;
	if (this->m_scale == 2) {
		this->m_width_byte = (this->m_width_mem % 8 == 0)? (this->m_width_mem / 8 ): (this->m_width_mem / 8 + 1);
	} else {
		this->m_width_byte = (this->m_width_mem % 4 == 0)? (this->m_width_mem / 4 ): (this->m_width_mem / 4 + 1);
	}
	this->m_height_byte = height;

	if(this->m_rotate == ROTATE_0 || this->m_rotate == ROTATE_180) {
		this->m_width = width;
		this->m_height = height;
	} else {
		this->m_width = height;
		this->m_height = width;
	}
}

void Image::set_rotation(uint16_t rotation) {
    if(rotation == ROTATE_0 ||
    		rotation == ROTATE_90 ||
			rotation == ROTATE_180 ||
			rotation == ROTATE_270) {

    	this->m_rotate = rotation;
    } else {
    	// error
    }
}

void Image::set_mirroring(uint8_t mirror) {
    if(mirror == MIRROR_NONE || mirror == MIRROR_HORIZONTAL ||
    		mirror == MIRROR_VERTICAL || mirror == MIRROR_ORIGIN) {
         this->m_mirror = mirror;
    } else {
        // error
    }
}

void Image::set_color(uint16_t color) {
	if (color == WHITE || color == BLACK || color == RED) {
		this->m_color = color;
	} else {
		// error
	}
}

void Image::set_scale(uint8_t scale) {
    if(scale == 2 || scale == 4){
    	this->m_scale = scale;
	} else {
		// error
    }
}

void Image::set_pixel(uint16_t x, uint16_t y, uint16_t color) {
	if(x > this->m_width || y > this->m_height){
		// error
		return;
	}

	uint16_t x_final, y_final;

	switch(this->m_rotate) {
	case 0:
		x_final = x;
	    y_final = y;
	    break;

	case 90:
		x_final = this->m_width_mem - y - 1;
	    y_final = x;
	    break;

	case 180:
		x_final = this->m_width_mem - x - 1;
		y_final = this->m_height_mem - y - 1;
	    break;

	case 270:
	    x_final = y;
	    y_final = this->m_height_mem - x - 1;
	    break;

	default:
	    return;
	}

	switch(this->m_mirror) {
	case MIRROR_NONE:
	    break;

	case MIRROR_HORIZONTAL:
	    x_final = this->m_width_mem - x_final - 1;
	    break;

	case MIRROR_VERTICAL:
		y_final = this->m_height_mem - y_final - 1;
		break;

	case MIRROR_ORIGIN:
		x_final = this->m_width_mem - x_final - 1;
		y_final = this->m_height_mem - y_final - 1;
	    break;

	default:
	    return;
	}

	if (x_final > this->m_width_mem || y_final > this->m_height_mem) {
		// error
		return;
	}

	if(this->m_scale == 2){
		uint32_t addr = x_final / 8 + y_final * this->m_width_byte;
		uint8_t r_data = this->m_img[addr];

		if(color == BLACK) {
			this->m_img[addr] = r_data & ~(0x80 >> (x_final % 8));
		} else {
			this->m_img[addr] = r_data | (0x80 >> (x_final % 8));
		}

	 } else if(this->m_scale == 4) {
		uint16_t width = (this->m_width_mem % 4 == 0)? (this->m_width_mem / 4 ): (this->m_width_mem / 4 + 1);
		uint32_t addr = x_final / 4 + y_final * width;
	    color = color % 4;		//Guaranteed color scale is 4  --- 0~3
	    uint8_t r_data = this->m_img[addr];

	    r_data = r_data & (~(0xC0 >> ((x_final % 4)*2)));
	    this->m_img[addr] =  r_data | (((color << 6) & 0xC0)>> ((x_final % 4)*2));
	 }
}

void Image::clear(uint16_t color) {
	if(this->m_scale == 2){
		for (uint16_t y = 0; y < this->m_height_byte; y++) {
			for (uint16_t x = 0; x < this->m_width_byte; x++ ) {	//8 pixel =  1 byte
				uint32_t addr = x + y*this->m_width_byte;
				this->m_img[addr] = color;
			}
		}
	} else if(this->m_scale == 4) {
		color = color % 4;

		if(color == 0x00){
			color = 0;
		} else if(color == 0x01) {
			color = 0x55;
		} else if(color == 0x02) {
			color = 0xAA;
		} else if(color == 0x03) {
			color = 0xff;
		}

		for (uint16_t y = 0; y < this->m_height_byte; y++) {
			for (uint16_t x = 0; x < this->m_width_byte; x++ ) {	//8 pixel =  1 byte
				uint32_t addr = x + y*this->m_width_byte;
				this->m_img[addr] = color;
			}
		}
	}
}

void Image::clear_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	uint16_t x_temp, y_temp;
	for (y_temp = y1; y_temp < y2; y_temp++) {
		for (x_temp = x1; x_temp < x2; x_temp++) {	//8 pixel =  1 byte
			this->set_pixel(x_temp, y_temp, color);
	    }
	}
}

void Image::draw_point(uint16_t x, uint16_t y, uint16_t color,
		PointSize weight, PointStyle style) {

    if (x > this->m_width || y > this->m_height) {
    	// error
        return;
    }

    int16_t x_dir_num , y_dir_num;
    if (style == POINT_STYLE_AROUND) {
        for (x_dir_num = 0; x_dir_num < 2 * weight - 1; x_dir_num++) {
            for (y_dir_num = 0; y_dir_num < 2 * weight - 1; y_dir_num++) {
                if(x + x_dir_num - weight < 0 || y + y_dir_num - weight < 0) {
                    break;
                }
                this->set_pixel(x + x_dir_num - weight, y + y_dir_num - weight, color);
            }
        }
    } else {
        for (x_dir_num = 0; x_dir_num < weight; x_dir_num++) {
            for (y_dir_num = 0; y_dir_num < weight; y_dir_num++) {
                this->set_pixel(x + x_dir_num - 1, y + y_dir_num - 1, color);
            }
        }
    }
}

void Image::draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color, PointSize weight, LineStyle style) {

    if (x1 > this->m_width || y1 > this->m_height ||
        x2 > this->m_width || y2 > this->m_height) {
        // error
        return;
    }

    uint16_t x_point = x1;
    uint16_t y_point = y1;
    int dx = (int)x2 - (int)x1 >= 0 ? x2 - x1 : x1 - x2;
    int dy = (int)y2 - (int)y1 <= 0 ? y2 - y1 : y1 - y2;

    // Increment direction, 1 is positive, -1 is counter;
    int x_add_way = x1 < x2 ? 1 : -1;
    int y_add_way = x1 < x2 ? 1 : -1;

    //Cumulative error
    int esp = dx + dy;
    char dotted_len = 0;

    for (;;) {
        dotted_len++;
        //Painted dotted line, 2 point is really virtual
        if (style == LINE_STYLE_DOTTED && dotted_len % 3 == 0) {
        	this->draw_point(x_point, y_point, IMAGE_BACKGROUND, weight, POINT_STYLE_DEFAULT);
            dotted_len = 0;
        } else {
        	this->draw_point(x_point, y_point, color, weight, POINT_STYLE_DEFAULT);
        }
        if (2 * esp >= dy) {
            if (x_point == x2) {
                break;
            }
            esp += dy;
            x_point += x_add_way;
        }
        if (2 * esp <= dx) {
            if (y_point == y2) {
                break;
            }
            esp += dx;
            y_point += y_add_way;
        }
    }
}


void Image::draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color, PointSize weight, FillStyle style) {

    if (x1 > this->m_width || y1 > this->m_height ||
        x2 > this->m_width || y2 > this->m_height) {
        // error
        return;
    }

	if (style) {
		uint16_t y;
	    for(y = y1; y < y2; y++) {
	    	this->draw_line(x1, y, x2, y, color , weight, LINE_STYLE_SOLID);
	    }
	} else {
	    this->draw_line(x1, y1, x2, y1, color, weight, LINE_STYLE_SOLID);
	    this->draw_line(x1, y1, x1, y2, color, weight, LINE_STYLE_SOLID);
	    this->draw_line(x2, y2, x2, y1, color, weight, LINE_STYLE_SOLID);
	    this->draw_line(x2, y2, x1, y2, color, weight, LINE_STYLE_SOLID);
	}
}

void Image::draw_circle(uint16_t x, uint16_t y, uint16_t r,
		uint16_t color, PointSize weight, FillStyle style) {

    if (x > this->m_width || y >= this->m_height) {
        // error
        return;
    }

    //Draw a circle from(0, R) as a starting point
    int16_t x_cur = 0;
    int16_t y_cur = r;

    //Cumulative error,judge the next point of the logo
    int16_t esp = 3 - (r << 1);

    int16_t cnt_y;
    if (style == DRAW_FILL_FULL) {
        while (x_cur <= y_cur) {
            for (cnt_y = x_cur; cnt_y <= y_cur; cnt_y++ ) {
            	this->draw_point(x + x_cur, y + cnt_y, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x - x_cur, y + cnt_y, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x - cnt_y, y + x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x - cnt_y, y - x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x - x_cur, y - cnt_y, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x + x_cur, y - cnt_y, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x + cnt_y, y - x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            	this->draw_point(x + cnt_y, y + x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
            }
            if (esp < 0) {
                esp += 4 * x_cur + 6;
            }
            else {
                esp += 10 + 4 * (x_cur - y_cur);
                y_cur--;
            }
            x_cur++;
        }
    } else { //Draw a hollow circle
        while (x_cur <= y_cur) {
        	this->draw_point(x + x_cur, y + y_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x - x_cur, y + y_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x - y_cur, y + x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x - y_cur, y - x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x - x_cur, y - y_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x + x_cur, y - y_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x + y_cur, y - x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);
        	this->draw_point(x + y_cur, y + x_cur, color, POINT_SIZE_DEFAULT, POINT_STYLE_DEFAULT);

            if (esp < 0)
                esp += 4 * x_cur + 6;
            else {
                esp += 10 + 4 * (x_cur - y_cur);
                y_cur--;
            }
            x_cur++;
        }
    }
}

void Image::draw_char(uint16_t x, uint16_t y, const char ascii_char, sFONT* Font,
		uint16_t fg_color, uint16_t bg_color) {

	uint16_t row, col;

	if (x > this->m_width || y > this->m_height) {
	    // error
		return;
	}

	uint32_t char_offset = (ascii_char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
	const unsigned char *ptr = &Font->table[char_offset];

	for (row = 0; row < Font->Height; row++) {
	    for (col = 0; col < Font->Width; col++) {

	        //To determine whether the font background color and screen background color is consistent
	        if (FONT_BACKGROUND == bg_color) { //this process is to speed up the scan
	            if (*ptr & (0x80 >> (col % 8))) {
	                this->set_pixel(x + col, y + row, fg_color);
	            }
	        } else {
	            if (*ptr & (0x80 >> (col % 8))) {
	                this->set_pixel(x + col, y + row, fg_color);
	            } else {
	                this->set_pixel(x + col, y + row, bg_color);
	            }
	        }

	        //One pixel is 8 bits
	        if (col % 8 == 7) {
	            ptr++;
	        }
	    }// Write a line

	    if (Font->Width % 8 != 0) {
	        ptr++;
	    }
	}// Write all
}

void Image::draw_string(uint16_t x, uint16_t y, const char * string, sFONT* Font,
		uint16_t fg_color, uint16_t bg_color) {

	uint16_t cur_x = x;
	uint16_t cur_y = y;

	if (x > this->m_width || y > this->m_height) {
	    // error
	    return;
	}

	while (*string != '\0') {
	    if ((cur_x + Font->Width ) > this->m_width) {
	        cur_x = x;
	        cur_y += Font->Height;
	    }

	    if ((cur_y  + Font->Height ) > this->m_height) {
	        cur_x = x;
	        cur_y = y;
	    }

	    this->draw_char(cur_x, cur_y, *string, Font, bg_color, fg_color);

	    //The next character of the address
	    string++;
	    cur_x += Font->Width;
	}
}

#define  ARRAY_LEN 255
void Image::draw_num(uint16_t x, uint16_t y, int32_t num, sFONT* Font,
		uint16_t fg_color, uint16_t bg_color) {

    int16_t num_bit = 0, str_bit = 0;
    uint8_t str_array[ARRAY_LEN] = {0}, num_array[ARRAY_LEN] = {0};
    uint8_t *str = str_array;

    if (x > this->m_width || y > this->m_height) {
        // error
        return;
    }

    //Converts a number to a string
    while (num) {
        num_array[num_bit] = num % 10 + '0';
        num_bit++;
        num /= 10;
    }

    //The string is inverted
    while (num_bit > 0) {
        str_array[str_bit] = num_array[num_bit - 1];
        str_bit++;
        num_bit--;
    }

    this->draw_string(x, y, (const char*)str, Font, bg_color, fg_color);
}

void Image::draw_time(uint16_t x, uint16_t y, Time *time, sFONT* Font,
		uint16_t fg_color, uint16_t bg_color) {

	uint8_t value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint16_t dx = Font->Width;

	this->draw_char(x                           , y, value[time->Hour / 10], Font, bg_color, fg_color);
	this->draw_char(x + dx                      , y, value[time->Hour % 10], Font, bg_color, fg_color);
	this->draw_char(x + dx + dx / 4 + dx / 2    , y, ':'                   , Font, bg_color, fg_color);
	this->draw_char(x + dx * 2 + dx / 2         , y, value[time->Min / 10] , Font, bg_color, fg_color);
	this->draw_char(x + dx * 3 + dx / 2         , y, value[time->Min % 10] , Font, bg_color, fg_color);
	this->draw_char(x + dx * 4 + dx / 2 - dx / 4, y, ':'                   , Font, bg_color, fg_color);
	this->draw_char(x + dx * 5                  , y, value[time->Sec / 10] , Font, bg_color, fg_color);
	this->draw_char(x + dx * 6                  , y, value[time->Sec % 10] , Font, bg_color, fg_color);
}

void Image::draw_bitmap(const unsigned char* image_buffer) {
    uint16_t x, y;
    uint32_t addr = 0;

    for (y = 0; y < this->m_height_byte; y++) {
        for (x = 0; x < this->m_width_byte; x++) {//8 pixel =  1 byte
            addr = x + y * this->m_width_byte;
            this->m_img[addr] = (unsigned char)image_buffer[addr];
        }
    }
}

void Image::draw_bitmap_block(const unsigned char* image_buffer, uint8_t region) {
    uint16_t x, y;
    uint32_t addr = 0;

    for (y = 0; y < this->m_height_byte; y++) {
		for (x = 0; x < this->m_width_byte; x++) {//8 pixel =  1 byte
			addr = x + y * this->m_width_byte ;
			this->m_img[addr] = \
						(unsigned char)image_buffer[addr+ (this->m_height_byte)*this->m_width_byte*(region - 1)];
		}
	}
}


