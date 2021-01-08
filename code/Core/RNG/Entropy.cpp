/*
 * Entropy.cpp
 *
 *  Created on: Jan 8, 2021
 *      Author: sok
 */

#include "Entropy.h"

#include <string.h>

#include "Device.h"

Entropy::Entropy() {
	this->m_source_pin = Gpio(ENT_SOURCE_PORT, ENT_SOURCE_PIN);
	this->m_source_enable_pin = Gpio(ENT_EN_PORT, ENT_EN_PIN);

	this->clear_samps();
}

void Entropy::clear_samps() {
	this->m_num_samps = 0;
	for(uint8_t i = 0; i < ENTROPY_BYTES; i++) {
		this->m_samps[i] = 0x00;
	}
}

void Entropy::open() {
	this->m_source_pin.enable(GPIO_INPUT);
	this->m_source_enable_pin.enable(GPIO_OUTPUT);
}

void Entropy::add_new_sample(uint8_t samp) {
	if (this->m_num_samps >= ENTROPY_MAX_SAMPLES) {
		return;
	}

	uint8_t target_byte = this->m_num_samps / 8;
	uint8_t target_bit = this->m_num_samps % 8;

	this->m_samps[target_byte] |= (samp << target_bit);
	this->m_num_samps++;
}

uint16_t Entropy::get_samps(uint8_t *dest) {
	uint16_t num_xfer = this->m_num_samps;
	memcpy(dest, this->m_samps, ENTROPY_BYTES);
	this->clear_samps();
	return num_xfer;
}

