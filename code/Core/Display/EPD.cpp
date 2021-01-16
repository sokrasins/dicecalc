/*
 * EPD.cpp
 *
 *  Created on: Jan 7, 2021
 *      Author: sok
 */

#include "EPD.h"

#include <stdint.h>

#include "Device.h"

const unsigned char Epaper::full_update_lut[]= {
    0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
    0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
    0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
    0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

    0x03,0x03,0x00,0x00,0x02,                       // TP0 A~D RP0
    0x09,0x09,0x00,0x00,0x02,                       // TP1 A~D RP1
    0x03,0x03,0x00,0x00,0x02,                       // TP2 A~D RP2
    0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
    0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
    0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
    0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

    0x15,0x41,0xA8,0x32,0x30,0x0A,
};

const unsigned char Epaper::partial_update_lut[]= { //20 bytes
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
    0x40,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

    0x0A,0x00,0x00,0x00,0x00,                       // TP0 A~D RP0
    0x00,0x00,0x00,0x00,0x00,                       // TP1 A~D RP1
    0x00,0x00,0x00,0x00,0x00,                       // TP2 A~D RP2
    0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
    0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
    0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
    0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

    0x15,0x41,0xA8,0x32,0x30,0x0A,
};

Epaper::Epaper() {
	this->rst_pin = Gpio(EPD_RST_PORT, EPD_RST_PIN);
	this->dc_pin = Gpio(EPD_DC_PORT, EPD_DC_PIN);
	this->cs_pin = Gpio(EPD_CS_PORT, EPD_CS_PIN);
	this->busy_pin = Gpio(EPD_BUSY_PORT, EPD_BUSY_PIN);

	this->port = Spi();
}

bool Epaper::open() {
	this->rst_pin.enable(GPIO_OUTPUT);
	this->dc_pin.enable(GPIO_OUTPUT);
	this->cs_pin.enable(GPIO_OUTPUT);
	this->busy_pin.enable(GPIO_INPUT);

	bool success = this->port.open(SPI1);
	return success;
}

void Epaper::reset() {
	this->rst_pin.set_state(1);
    Delay_ms(50);
    this->rst_pin.set_state(0);
    Delay_ms(10);
    this->rst_pin.set_state(1);
    Delay_ms(50);
}

void Epaper::send_cmd(uint8_t reg) {
	this->dc_pin.set_state(0);
    this->cs_pin.set_state(0);
    this->port.write_byte(reg);
    this->cs_pin.set_state(1);
}

void Epaper::send_data(uint8_t data) {
	this->dc_pin.set_state(1);
    this->cs_pin.set_state(0);
    this->port.write_byte(data);
    this->cs_pin.set_state(1);
}

void Epaper::wait_until_idle() {
	while(this->busy_pin.get_state() == 1) {
		Delay_ms(5);
	}
}

void Epaper::turn_on_display() {
	this->send_cmd(0x22);
	this->send_data(0xC7);
	this->send_cmd(0x20);
	this->wait_until_idle();
}

void Epaper::turn_on_display_part() {
	this->send_cmd(0x22);
	this->send_data(0x0C);
	this->send_cmd(0x20);
	this->wait_until_idle();
}

void Epaper::init(UpdateMode mode) {
	uint8_t count = 0;
	this->reset();

	if (mode == EPD_UPDATE_FULL) {

		this->wait_until_idle();
		this->send_cmd(0x12);
		this->wait_until_idle();

		this->send_cmd(0x74);	// set analog block control
		this->send_data(0x54);
		this->send_cmd(0x7E);	// set digital block control
		this->send_data(0x3B);

		this->send_cmd(0x01);	// driver output control
		this->send_data(0xF9);
		this->send_data(0x00);
		this->send_data(0x00);

		this->send_cmd(0x11);	// data entry mode
		this->send_data(0x01);

		this->send_cmd(0x44);	// set Ram-X address start/end position
		this->send_data(0x00);
		this->send_data(0x0F);

		this->send_cmd(0x45);	// set Ram-Y address start/end position
		this->send_data(0xF9);
		this->send_data(0x00);
		this->send_data(0x00);
		this->send_data(0x00);

		this->send_cmd(0x3C);	// BorderWavefrom
		this->send_data(0x03);

		this->send_cmd(0x2C);	// VCOM Voltage
		this->send_data(0x55);

		this->send_cmd(0x03);
		this->send_data(Epaper::full_update_lut[70]);

		this->send_cmd(0x04);
		this->send_data(Epaper::full_update_lut[71]);
		this->send_data(Epaper::full_update_lut[72]);
		this->send_data(Epaper::full_update_lut[73]);

		this->send_cmd(0x3A);	// Dummy line
		this->send_data(Epaper::full_update_lut[74]);
		this->send_cmd(0x3B);
		this->send_data(Epaper::full_update_lut[75]);

		this->send_cmd(0x32);
		for (count = 0; count < 70; count++) {
			this->send_data(Epaper::full_update_lut[count]);
		}

		this->send_cmd(0x4E);	// Set ram x address count to 0
		this->send_data(0x00);
		this->send_cmd(0x4F);	// Set ram y address count to 0x127
		this->send_data(0xF9);
		this->send_data(0x00);
		this->wait_until_idle();

	} else if (mode == EPD_UPDATE_PARTIAL) {

		this->send_cmd(0x2C);	// VCOM Voltage
		this->send_cmd(0x26);

		this->wait_until_idle();

		this->send_cmd(0x32);
		for(count = 0; count < 70; count++) {
			this->send_data(Epaper::partial_update_lut[count]);
		}

		this->send_cmd(0x37);
		this->send_data(0x00);
		this->send_data(0x00);
		this->send_data(0x00);
		this->send_data(0x00);
		this->send_data(0x40);
		this->send_data(0x00);
		this->send_data(0x00);

		this->send_cmd(0x22);
		this->send_data(0xC0);

		this->send_cmd(0x20);
		this->wait_until_idle();

		this->send_cmd(0x3C);	// BorderWavefrom
		this->send_data(0x01);

	} else {
		// ERROR: unsupported mode
	}
}

void Epaper::clear() {
	uint16_t width = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8 ) : (EPD_WIDTH / 8 + 1);
	uint16_t height = EPD_HEIGHT;

	this->send_cmd(0x24);
	for(uint16_t j = 0; j < height; j++) {
		for(uint16_t i = 0; i < width; i++) {
			this->send_data(0xFF);
		}
	}
	this->turn_on_display();
}

void Epaper::display(Image& img) {
	uint8_t *image_buf = img.get_image();
	uint16_t width = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8 ) : (EPD_WIDTH / 8 + 1);
	uint16_t height = EPD_HEIGHT;

	this->send_cmd(0x24);
	for(uint16_t j = 0; j < height; j++) {
		for(uint16_t i = 0; i < width; i++) {
			this->send_data(image_buf[i + j * width]);
		}
	}
	this->turn_on_display();
}

void Epaper::display_base(Image& img) {
	uint8_t *image_buf = img.get_image();
	uint16_t width = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8 ) : (EPD_WIDTH / 8 + 1);
	uint16_t height = EPD_HEIGHT;

	uint32_t addr = 0;
	this->send_cmd(0x24);
	for(uint16_t j = 0; j < height; j++) {
		for(uint16_t i = 0; i < width; i++) {
			addr = i + j * width;
			this->send_data(image_buf[addr]);
		}
	}

	this->send_cmd(0x26);
	for(uint16_t j = 0; j < height; j++) {
		for(uint16_t i = 0; i < width; i++) {
			addr = i + j * width;
			this->send_data(image_buf[addr]);
		}
	}

	this->turn_on_display();
}

void Epaper::display_part(Image& img) {
	uint8_t *image_buf = img.get_image();
	uint16_t width = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8 ) : (EPD_WIDTH / 8 + 1);
	uint16_t height = EPD_HEIGHT;

	this->send_cmd(0x24);
	for(uint16_t j = 0; j < height; j++) {
		for(uint16_t i = 0; i < width; i++) {
			this->send_data(image_buf[i + j * width]);
		}
	}
	this->turn_on_display_part();
}

void Epaper::sleep() {
	this->send_cmd(0x22);	// power off
	this->send_data(0xC3);
	this->send_cmd(0x20);

	this->send_cmd(0x10);	// Enter deep sleep
	this->send_data(0x01);
	Delay_ms(100);
}
