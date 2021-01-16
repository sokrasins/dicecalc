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

typedef void(*GpioCallback)(void*);

enum GpioMode {
	GPIO_INPUT, GPIO_OUTPUT, GPIO_IT
};

class Gpio {
	uint16_t m_pin;
	GPIO_TypeDef  *m_port;
	bool enabled;
	GpioMode m_mode;

	GpioCallback m_it_cb;
	void * m_it_obj;

	static Gpio *s_it_pins[64];
	static int s_num_it_pins;

public:
	Gpio();
	Gpio(GPIO_TypeDef *port, uint16_t pin);
	void set_pin(GPIO_TypeDef *port, uint16_t pin);
	void connect_cb(GpioCallback cb, void *p);
	void enable(GpioMode mode);

	/* Getters and Setters */
	uint16_t pin_num() { return this->m_pin; };

	/* Input */
	uint8_t get_state();

	/* Output */
	void set_state(int state);
	void toggle();

	/* Interrupt */
	static void add_it_pin(Gpio *pin);
	static void pin_pressed(uint16_t pin);
	void exec_cb();
};

#endif /* DEVICE_GPIO_H_ */
