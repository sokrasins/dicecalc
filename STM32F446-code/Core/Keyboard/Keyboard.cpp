/*
 * Keyboard.cpp
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#include "Keyboard.h"

#include "Device.h"
#include "KeyEvent.h"

uint16_t Keyboard::KEY_PINS[NUM_KEYS] = {
		KEY_F4_PIN,
		KEY_0_PIN,
		KEY_CLRLINE_PIN,
		KEY_CLRALL_PIN,
		KEY_ENTER_PIN,
		KEY_F3_PIN,
		KEY_1_PIN,
		KEY_2_PIN,
		KEY_3_PIN,
		KEY_PLUS_PIN,
		KEY_F2_PIN,
		KEY_4_PIN,
		KEY_5_PIN,
		KEY_6_PIN,
		KEY_MINUS_PIN,
		KEY_F1_PIN,
		KEY_7_PIN,
		KEY_8_PIN,
		KEY_9_PIN,
		KEY_TIMES_PIN,
		KEY_D4_PIN,
		KEY_D6_PIN,
		KEY_D8_PIN,
		KEY_D10_PIN,
		KEY_DIV_PIN,
		KEY_D12_PIN,
		KEY_D20_PIN,
		KEY_D100_PIN,
		KEY_D_PIN,
		KEY_BKSPC_PIN,
};

GPIO_TypeDef* Keyboard::KEY_PORTS[NUM_KEYS] = {
		KEY_F4_PORT,
		KEY_0_PORT,
		KEY_CLRLINE_PORT,
		KEY_CLRALL_PORT,
		KEY_ENTER_PORT,
		KEY_F3_PORT,
		KEY_1_PORT,
		KEY_2_PORT,
		KEY_3_PORT,
		KEY_PLUS_PORT,
		KEY_F2_PORT,
		KEY_4_PORT,
		KEY_5_PORT,
		KEY_6_PORT,
		KEY_MINUS_PORT,
		KEY_F1_PORT,
		KEY_7_PORT,
		KEY_8_PORT,
		KEY_9_PORT,
		KEY_TIMES_PORT,
		KEY_D4_PORT,
		KEY_D6_PORT,
		KEY_D8_PORT,
		KEY_D10_PORT,
		KEY_DIV_PORT,
		KEY_D12_PORT,
		KEY_D20_PORT,
		KEY_D100_PORT,
		KEY_D_PORT,
		KEY_BKSPC_PORT,
};

KeyType Keyboard::KEY_TYPE[NUM_KEYS] = {
		KEY_F4,
		KEY_0,
		KEY_CLEARLINE,
		KEY_CLEARALL,
		KEY_ENTER,
		KEY_F3,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_PLUS,
		KEY_F2,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_MINUS,
		KEY_F1,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_TIMES,
		KEY_D4,
		KEY_D6,
		KEY_D8,
		KEY_D10,
		KEY_DIV,
		KEY_D12,
		KEY_D20,
		KEY_D100,
		KEY_D,
		KEY_BACKSPACE,
};

Key::Key(KeyType type, GPIO_TypeDef* port, uint16_t pin) {
	this->m_pin = Gpio(port, pin);
	this->m_type = type;
}

void Key::open() {
	this->m_pin.enable(GPIO_INPUT);
}

bool Key::pressed() {
	uint8_t state = this->m_pin.get_state();
	if (state == 0) {
		return 1;
	} else {
		return 0;
	}
}

Keyboard::Keyboard() {
	for (uint8_t i=0; i<NUM_KEYS; i++) {
		this->m_keys[i] = Key(
				Keyboard::KEY_TYPE[i],
				Keyboard::KEY_PORTS[i],
				Keyboard::KEY_PINS[i]
		);
		last_key_state[i] = false;
	}
	this->m_tim = {0};
}

void Keyboard::open() {
	for (uint8_t i=0; i<NUM_KEYS; i++) {
		this->m_keys[i].open();
	}

	this->m_tim.Instance = TIM4;
	this->m_tim.Init.Period = 10000;
	this->m_tim.Init.Prescaler = 100;
	this->m_tim.Init.ClockDivision = 0; //TIM_CLOCKDIVISION_DIV4;
	this->m_tim.Init.CounterMode = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Init(&this->m_tim);
	HAL_TIM_Base_Start_IT(&this->m_tim);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_TIM_Base_Start(&this->m_tim);
}

void Keyboard::check_for_changes() {
	KeyEvent event;
	bool cur_state = false;
	bool last_state = false;

	HAL_TIM_IRQHandler(&this->m_tim);

	for (uint8_t i=0; i<NUM_KEYS; i++) {
		cur_state = this->m_keys[i].pressed();
		last_state = this->last_key_state[i];

		if (cur_state != last_state) {
			event.key = this->m_keys[i].get_type();
			if (cur_state) {
				event.state = KEYSTATE_DOWN;
			} else {
				event.state = KEYSTATE_UP;
			}
			this->m_events.push_back(event);
			this->last_key_state[i] = cur_state;
		}
	}
}

bool Keyboard::get_event(KeyEvent* event) {
	if (this->m_events.size() > 0) {
		KeyEvent evt = this->m_events.front();
		event->key = evt.key;
		event->state = evt.state;
		this->m_events.erase(
				this->m_events.begin(),
				this->m_events.begin()+1);
		return true;
	}
	return false;
}

