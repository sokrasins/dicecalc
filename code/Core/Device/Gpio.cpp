/*
 * Gpio.cpp
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#include <Gpio.h>

Gpio* Gpio::s_it_pins[64] = {NULL};
int Gpio::s_num_it_pins = 0;

Gpio::Gpio() :
	m_pin(0),
	m_port(GPIOA),
	enabled(false),
	m_it_cb(NULL),
	m_it_obj(NULL)
{}

Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin) :
		m_pin(pin),
		m_port(port),
		enabled(false),
		m_it_cb(NULL),
		m_it_obj(NULL)
{}

void Gpio::set_pin(GPIO_TypeDef *port, uint16_t pin) {
	this->m_port = port;
	this->m_pin = pin;
}

void Gpio::connect_cb(GpioCallback cb, void *p) {
	this->m_it_cb = cb;
	this->m_it_obj = p;
}

void Gpio::enable(GpioMode mode) {
	this->m_mode = mode;

	GPIO_InitTypeDef pin_init = {0};
	pin_init.Pin = this->m_pin;
	pin_init.Pull = GPIO_NOPULL;

	if (this->m_mode == GPIO_INPUT) {
		pin_init.Mode = GPIO_MODE_INPUT;
	} else if (this->m_mode == GPIO_OUTPUT){
		pin_init.Mode = GPIO_MODE_OUTPUT_PP;
	} else if (this->m_mode == GPIO_IT) {
		if (this->m_it_cb == NULL || this->m_it_obj == NULL) {
			return;
		}
		pin_init.Mode = GPIO_MODE_IT_FALLING;
		Gpio::add_it_pin(this);
	} else {
		return;
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

void Gpio::exec_cb() {
	if (!(this->m_mode == GPIO_IT)) {
		return;
	}
	this->m_it_cb(this->m_it_obj);
}

void Gpio::add_it_pin(Gpio *pin) {
	Gpio::s_it_pins[Gpio::s_num_it_pins] = pin;
	Gpio::s_num_it_pins++;
}

void Gpio::pin_pressed(uint16_t pin_num) {
	for(uint8_t i=0; i<Gpio::s_num_it_pins; i++) {
		Gpio *pin = Gpio::s_it_pins[i];
		if (pin->pin_num() == pin_num &&
				pin->get_state() == 0) {
			pin->exec_cb();
		}
	}
}


