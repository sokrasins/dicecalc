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

	this->m_tim = {0};
	this->m_tim.Instance = TIM7;
	this->m_tim.Init.Period = 656;
	this->m_tim.Init.Prescaler = 0;
	this->m_tim.Init.ClockDivision = 0;
	this->m_tim.Init.CounterMode = TIM_COUNTERMODE_UP;

	this->clear_samps();
}

void Entropy::interrupt_cb() {
	HAL_TIM_IRQHandler(&this->m_tim);

	this->sample();

	if (this->num_samps() == ENTROPY_MAX_SAMPLES) {
		this->stop_timer();
		this->m_source_enable_pin.set_state(0);
	}
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

	HAL_TIM_Base_Init(&this->m_tim);
	HAL_TIM_Base_Start_IT(&this->m_tim);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

void Entropy::collect() {
	this->m_source_enable_pin.set_state(1);
	HAL_TIM_Base_Start(&this->m_tim);
}

void Entropy::stop_timer() {
	HAL_TIM_Base_Stop(&this->m_tim);
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

void Entropy::sample() {
	uint8_t samp = this->m_source_pin.get_state();
	this->add_new_sample(samp);
}

void Entropy::enable() {
	this->m_source_enable_pin.toggle();
}
