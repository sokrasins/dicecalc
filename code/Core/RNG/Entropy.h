/*
 * Entropy.h
 *
 *  Created on: Jan 8, 2021
 *      Author: sok
 */

#ifndef RNG_ENTROPY_H_
#define RNG_ENTROPY_H_

#include <stdint.h>

#include "Gpio.h"

#define ENTROPY_MAX_SAMPLES 1024
#define ENTROPY_BYTES (ENTROPY_MAX_SAMPLES / 8)

class Entropy {
	Gpio m_source_pin;
	Gpio m_source_enable_pin;
	uint16_t m_num_samps;
	uint8_t m_samps[ENTROPY_BYTES / 8];

	void clear_samps();
	void add_new_sample(uint8_t samp);
public:
	Entropy();
	void open();
	uint16_t num_samps() { return m_num_samps; };
	uint16_t get_samps(uint8_t *dest);
};

#endif /* RNG_ENTROPY_H_ */
