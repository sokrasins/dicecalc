/*
 * Gpio.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include <stdint.h>

#include "stm32f4xx_hal.h"

enum GpioMode {
	GPIO_INPUT, GPIO_OUTPUT
};

class Gpio {
	uint8_t m_pin;
	GPIO_TypeDef  *m_port;
	bool enabled;
	GpioMode m_mode;

public:
	Gpio() : m_pin(0), m_port(GPIOA), enabled(false) {};
	Gpio(GPIO_TypeDef *port, uint8_t pin) : m_pin(pin), m_port(port), enabled(false) {};
	void set_pin(GPIO_TypeDef *port, uint8_t pin);
	void enable(GpioMode mode);

	/* Input */
	uint8_t get_state();

	/* Output */
	void set_state(int state);
	void toggle();
};

#endif /* GPIO_GPIO_H_ */
