/*
 * Spi.cpp
 *
 *  Created on: Jan 7, 2021
 *      Author: sok
 */

#include "Spi.h"

#include <stdint.h>
#include <string.h>

//#include "stm32f4xx_hal.h"
#include "dev_config.h"

Spi::Spi() {
	this->m_spi.State = HAL_SPI_STATE_RESET;
	this->m_spi.Init.Mode = SPI_MODE_MASTER;
	this->m_spi.Init.Direction = SPI_DIRECTION_2LINES;
	this->m_spi.Init.DataSize = SPI_DATASIZE_8BIT;
	this->m_spi.Init.CLKPolarity = SPI_POLARITY_LOW;
	this->m_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
	this->m_spi.Init.NSS = SPI_NSS_SOFT;
	this->m_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	this->m_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	this->m_spi.Init.TIMode = SPI_TIMODE_DISABLE;
	this->m_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	this->m_spi.Init.CRCPolynomial = 10;
}

bool Spi::open(SPI_TypeDef *instance) {
	if (instance == SPI1) {
		this->m_spi.Instance = instance;
		__HAL_RCC_SPI1_CLK_ENABLE();

		if (MX_SPI_Init(&(this->m_spi)) != HAL_OK) {
			return false;
		}
		return true;
	}
	return false;
}

void Spi::write_byte(uint8_t byte) {
	HAL_SPI_Transmit(&this->m_spi, &byte, 1, 0xFFFF);
}
