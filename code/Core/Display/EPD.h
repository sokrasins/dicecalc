/*
 * EPD.h
 *
 *  Created on: Jan 7, 2021
 *      Author: sok
 */

#ifndef DISPLAY_EPD_H_
#define DISPLAY_EPD_H_

#define EPD_WIDTH 122
#define EPD_HEIGHT 250

#include <stdint.h>

#include <Gpio.h>
#include "Spi.h"

enum UpdateMode {
	EPD_UPDATE_FULL = 0,
	EPD_UPDATE_PARTIAL = 1
};

class Epaper {
	static const unsigned char full_update_lut[];
	static const unsigned char partial_update_lut[];

	Gpio rst_pin;
	Gpio dc_pin;
	Gpio cs_pin;
	Gpio busy_pin;
	Spi port;

	void reset();
	void send_cmd(uint8_t reg);
	void send_data(uint8_t data);
	void wait_until_idle();
	void turn_on_display();
	void turn_on_display_part();

public:
	Epaper();
	void init(UpdateMode mode);
	bool open();
	void clear();
	void display(uint8_t *image);
	void display_part(uint8_t *image);
	void display_base(uint8_t *image);
	void sleep();
};

#endif /* DISPLAY_EPD_H_ */
