/*
 * Gpio.cpp
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#include "Gpio.h"

void Gpio::set_pin(GPIO_TypeDef *port, uint16_t pin) {
	this->m_port = port;
	this->m_pin = pin;
}

void Gpio::enable(GpioMode mode) {
	this->m_mode = mode;

	GPIO_InitTypeDef pin_init = {0};
	pin_init.Pin = this->m_pin;
	pin_init.Pull = GPIO_NOPULL;

	if (this->m_mode == GPIO_INPUT) {
		pin_init.Mode = GPIO_MODE_INPUT;
	} else {
		pin_init.Mode = GPIO_MODE_OUTPUT_PP;
	}

	HAL_GPIO_Init(this->m_port, &pin_init);
	this->enabled = true;
}

void Gpio::set_state(int state) {
	if (!this->enabled) {
		return;
	}

	if (this->m_mode != GPIO_OUTPUT) {
		return;
	}

	if (state == 0) {
		HAL_GPIO_WritePin(this->m_port, this->m_pin, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(this->m_port, this->m_pin, GPIO_PIN_SET);
	}
}

void Gpio::toggle() {
	if (!this->enabled) {
		return;
	}

	if (this->m_mode != GPIO_OUTPUT) {
		return;
	}

	HAL_GPIO_TogglePin(this->m_port, this->m_pin);
}

uint8_t Gpio::get_state() {
	if (!this->enabled) {
		return 0;
	}

	GPIO_PinState state = HAL_GPIO_ReadPin(this->m_port, this->m_pin);

	if (state == GPIO_PIN_SET) {
		return 1;
	}
	return 0;
}
