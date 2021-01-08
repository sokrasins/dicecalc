/*
 * dev_config.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef DEVICE_DEV_CONFIG_H_
#define DEVICE_DEV_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "calc_pin_def.h"

#define Delay_ms HAL_Delay

void DEV_Init(void);
uint8_t DEV_Digital_Read(uint8_t pin);
void DEV_Digital_Write(uint8_t pin, uint8_t state);
void DEV_SPI_WriteByte(uint8_t byte);
void Console_Log(uint8_t *msg, uint16_t size);

HAL_StatusTypeDef MX_SPI_Init(SPI_HandleTypeDef *handle);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_DEV_CONFIG_H_ */
