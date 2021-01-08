/*
 * Spi.h
 *
 *  Created on: Jan 7, 2021
 *      Author: sok
 */

#ifndef DEVICE_SPI_H_
#define DEVICE_SPI_H_

#include "stm32f4xx_hal.h"

class Spi {
	SPI_HandleTypeDef m_spi;
public:
	Spi();
	bool open(SPI_TypeDef *instance);
	void write_byte(uint8_t byte);
};

#endif /* DEVICE_SPI_H_ */
