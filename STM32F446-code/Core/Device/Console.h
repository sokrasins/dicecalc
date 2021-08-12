/*
 * Console.h
 *
 *  Created on: Jan 8, 2021
 *      Author: sok
 */

#ifndef DEVICE_CONSOLE_H_
#define DEVICE_CONSOLE_H_

#include <Device.h>

class Console {
	UART_HandleTypeDef m_uart;
public:
	Console();
	bool open(USART_TypeDef *instance);
	void log(uint8_t *msg, uint16_t size);
};

#endif /* DEVICE_CONSOLE_H_ */
