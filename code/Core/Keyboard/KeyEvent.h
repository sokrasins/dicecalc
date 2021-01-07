/*
 * KeyEvent.h
 *
 *  Created on: Dec 31, 2020
 *      Author: sok
 */

#ifndef KEYBOARD_KEYEVENT_H_
#define KEYBOARD_KEYEVENT_H_

enum KeyState {
	KEYSTATE_DOWN,
	KEYSTATE_UP,
};

enum KeyType {
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_PLUS,
	KEY_MINUS,
	KEY_TIMES,
	KEY_DIV,
	KEY_D,
	KEY_D4,
	KEY_D6,
	KEY_D8,
	KEY_D10,
	KEY_D12,
	KEY_D20,
	KEY_D100,
	KEY_ENTER,
	KEY_BACKSPACE,
	KEY_CLEARLINE,
	KEY_CLEARALL,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
};

struct KeyEvent {
	KeyState state;
	KeyType key;
};

#endif /* KEYBOARD_KEYEVENT_H_ */
