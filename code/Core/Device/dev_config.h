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

#define DEV_Delay_ms HAL_Delay

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

void DEV_Init(void);
uint8_t DEV_Digital_Read(uint8_t pin);
void DEV_Digital_Write(uint8_t pin, uint8_t state);
void DEV_SPI_WriteByte(uint8_t byte);
void Console_Log(uint8_t *msg, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_DEV_CONFIG_H_ */
