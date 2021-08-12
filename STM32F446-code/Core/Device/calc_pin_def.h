/*
 * calc_pin_def.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef DEVICE_CALC_PIN_DEF_H_
#define DEVICE_CALC_PIN_DEF_H_

#include "stm32f4xx_hal.h"

// Define pins for debug UART port
#define DEBUG_USART_PORT GPIOA
#define DEBUG_USART_TX_Pin GPIO_PIN_2
#define DEBUG_USART_RX_Pin GPIO_PIN_3

// Entropy source pins
#define ENT_SOURCE_PORT	GPIOD
#define ENT_SOURCE_PIN	GPIO_PIN_2

#define ENT_EN_PORT		GPIOC
#define ENT_EN_PIN		GPIO_PIN_11

// E-paper display pins
#define EPD_RST_PORT    GPIOB
#define EPD_RST_PIN 	GPIO_PIN_8

#define EPD_DC_PORT     GPIOC
#define EPD_DC_PIN 		GPIO_PIN_6

#define EPD_CS_PORT		GPIOC
#define EPD_CS_PIN 		GPIO_PIN_8

#define EPD_BUSY_PORT   GPIOC
#define EPD_BUSY_PIN 	GPIO_PIN_9

#define EPD_SPI_PORT	GPIOA
#define EPD_SCK_PIN		GPIO_PIN_5
#define EPD_MOSI_PIN	GPIO_PIN_7
#define EPD_MISO_PIN	GPIO_PIN_6

// Keypad pins
#define KEY_0_PORT		GPIOC
#define KEY_0_PIN		GPIO_PIN_0

#define KEY_1_PORT		GPIOC
#define KEY_1_PIN		GPIO_PIN_1

#define KEY_2_PORT		GPIOB
#define KEY_2_PIN		GPIO_PIN_5

#define KEY_3_PORT		GPIOB
#define KEY_3_PIN		GPIO_PIN_13

#define KEY_4_PORT		GPIOB
#define KEY_4_PIN		GPIO_PIN_0

#define KEY_5_PORT		GPIOB
#define KEY_5_PIN		GPIO_PIN_14

#define KEY_6_PORT		GPIOB
#define KEY_6_PIN		GPIO_PIN_10

#define KEY_7_PORT		GPIOA
#define KEY_7_PIN		GPIO_PIN_0

#define KEY_8_PORT		GPIOA
#define KEY_8_PIN		GPIO_PIN_1

#define KEY_9_PORT		GPIOA
#define KEY_9_PIN		GPIO_PIN_8

#define KEY_F1_PORT		GPIOC
#define KEY_F1_PIN		GPIO_PIN_15

#define KEY_F2_PORT		GPIOA
#define KEY_F2_PIN		GPIO_PIN_4

#define KEY_F3_PORT		GPIOC
#define KEY_F3_PIN		GPIO_PIN_2

#define KEY_F4_PORT		GPIOC
#define KEY_F4_PIN		GPIO_PIN_3

#define KEY_PLUS_PORT	GPIOB
#define KEY_PLUS_PIN	GPIO_PIN_4

#define KEY_MINUS_PORT	GPIOB
#define KEY_MINUS_PIN	GPIO_PIN_15

#define KEY_TIMES_PORT	GPIOA
#define KEY_TIMES_PIN	GPIO_PIN_9

#define KEY_DIV_PORT	GPIOB
#define KEY_DIV_PIN		GPIO_PIN_6

#define KEY_D_PORT		GPIOB
#define KEY_D_PIN		GPIO_PIN_12

#define KEY_D4_PORT		GPIOB
#define KEY_D4_PIN		GPIO_PIN_7

#define KEY_D6_PORT		GPIOC
#define KEY_D6_PIN		GPIO_PIN_13

#define KEY_D8_PORT		GPIOC
#define KEY_D8_PIN		GPIO_PIN_14

#define KEY_D10_PORT	GPIOC
#define KEY_D10_PIN		GPIO_PIN_7

#define KEY_D12_PORT	GPIOC
#define KEY_D12_PIN		GPIO_PIN_10

#define KEY_D20_PORT	GPIOC
#define KEY_D20_PIN		GPIO_PIN_12

#define KEY_D100_PORT	GPIOA
#define KEY_D100_PIN	GPIO_PIN_15

#define KEY_ENTER_PORT	GPIOB
#define KEY_ENTER_PIN	GPIO_PIN_3

#define KEY_CLRALL_PORT	GPIOC
#define KEY_CLRALL_PIN	GPIO_PIN_4

#define KEY_CLRLINE_PORT GPIOA
#define KEY_CLRLINE_PIN	GPIO_PIN_10

#define KEY_BKSPC_PORT	GPIOA
#define KEY_BKSPC_PIN	GPIO_PIN_11

#endif /* DEVICE_CALC_PIN_DEF_H_ */
