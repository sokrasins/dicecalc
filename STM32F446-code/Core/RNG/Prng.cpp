/*
 * Prng.cpp
 *
 *  Created on: Jan 16, 2021
 *      Author: sok
 */

#include "Prng.h"

#include <stdint.h>
#include "string.h"

Prng::Prng() {
	memset(this->m_counter, 0, AES_BLOCKLEN);
	this->m_aes_ctx = {0};
}

Prng& Prng::get_instance() {
	static Prng instance;
	return instance;
}

void Prng::set_seed(uint8_t *seed) {
	AES_init_ctx(&this->m_aes_ctx, seed);
	memset(this->m_counter, 0, AES_BLOCKLEN);
}

void Prng::next_rand(uint8_t *result) {
	memcpy(result, this->m_counter, AES_BLOCKLEN);
	AES_ECB_encrypt(&this->m_aes_ctx, result);
	this->increment_counter();
}

void Prng::increment_counter() {
	for (uint8_t i=0; i<AES_BLOCKLEN; i++) {
		this->m_counter[i]++;
		if (this->m_counter[0] != 0) {
			return;
		}
	}
}

// generated a random integer, inclusive of min and max
int Prng::rand_int(int min, int max) {
	uint8_t rand_val[AES_BLOCKLEN] = {0};
	int span = max - min + 1;

	bool success = false;
	while(!success) {
		this->next_rand(rand_val);

		for (uint8_t i=0; i<(AES_BLOCKLEN / 4); i++) {
			uint32_t small_part = rand_val[4*i];
			small_part |= rand_val[4*i+1] << 8;
			small_part |= rand_val[4*i+2] << 16;
			small_part |= rand_val[4*i+3] << 24;

			uint64_t m = span * (0x100000000 / span);

			if (small_part < m) {
				return (small_part % span) + min;
			}
		}

	}
	return min;
}
