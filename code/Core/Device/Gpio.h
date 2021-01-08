/*
 * Gpio.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef DEVICE_GPIO_H_
#define DEVICE_GPIO_H_

#include <stdint.h>

#include "Device.h"

enum GpioMode {
	GPIO_INPUT, GPIO_OUTPUT
};

class Gpio {
	uint16_t m_pin;
	GPIO_TypeDef  *m_port;
	bool enabled;
	GpioMode m_mode;

public:
	Gpio() : m_pin(0), m_port(GPIOA), enabled(false) {};
	Gpio(GPIO_TypeDef *port, uint16_t pin) : m_pin(pin), m_port(port), enabled(false) {};
	void set_pin(GPIO_TypeDef *port, uint16_t pin);
	void enable(GpioMode mode);

	/* Input */
	uint8_t get_state();

	/* Output */
	void set_state(int state);
	void toggle();
};

#endif /* DEVICE_GPIO_H_ */
