/*
 * dev_config.h
 *
 *  Created on: Jan 5, 2021
 *      Author: sok
 */

#ifndef DEVICE_DEVICE_H_
#define DEVICE_DEVICE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "calc_pin_def.h"

#define Delay_ms HAL_Delay
void DEV_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_DEVICE_H_ */
