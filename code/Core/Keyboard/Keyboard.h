/*
 * Keyboard.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef KEYBOARD_KEYBOARD_H_
#define KEYBOARD_KEYBOARD_H_

#include "Gpio.h"
#include "KeyEvent.h"

#define NUM_KEYS 30

class Key {
	Gpio m_pin;
	KeyType m_type;
public:
	Key() {};
	Key(KeyType type, GPIO_TypeDef* port, uint16_t pin);
	KeyType get_type() { return this->m_type; };
	bool pressed();
};

class Keyboard {
	static uint16_t KEY_PINS[NUM_KEYS];
	static GPIO_TypeDef* KEY_PORTS[NUM_KEYS];
	static KeyType KEY_TYPE[NUM_KEYS];

	bool last_key_state[NUM_KEYS];
	Key m_keys[NUM_KEYS];
public:
	Keyboard();
	bool check_for_changes(KeyEvent* event);
};

#endif /* KEYBOARD_KEYBOARD_H_ */
