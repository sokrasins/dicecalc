/*
 * Console.cpp
 *
 *  Created on: Jan 8, 2021
 *      Author: sok
 */

#include "Console.h"

#include "Device.h"


Console::Console() {
	this->m_uart = {0};
	this->m_uart.Init.BaudRate = 115200;
	this->m_uart.Init.WordLength = UART_WORDLENGTH_8B;
	this->m_uart.Init.StopBits = UART_STOPBITS_1;
	this->m_uart.Init.Parity = UART_PARITY_NONE;
	this->m_uart.Init.Mode = UART_MODE_TX_RX;
	this->m_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	this->m_uart.Init.OverSampling = UART_OVERSAMPLING_16;
}

bool Console::open(USART_TypeDef *instance) {
	if (instance == USART2) {
		this->m_uart.Instance = instance;

		if (HAL_UART_Init(&(this->m_uart)) != HAL_OK)
		{
			return false;
		}
		return true;
	}
	return false;
}

void Console::log(uint8_t *msg, uint16_t size) {
	uint8_t eol[] = {0xFF, 0xFF};
	HAL_UART_Transmit(&(this->m_uart), msg, size, 0xFFFF);
	HAL_UART_Transmit(&(this->m_uart), eol, 2, 0xFFFF);
}

