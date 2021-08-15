/*
 * Prng.h
 *
 *  Created on: Jan 16, 2021
 *      Author: sok
 */

#ifndef RNG_PRNG_H_
#define RNG_PRNG_H_

extern "C" {
	#include "SHA256.h"
	#include "Aes.h"
}

#define KEY_LEN 256
#define KEY_BYTES (KEY_LEN / 8)

class Prng {
	struct AES_ctx m_aes_ctx;
	uint8_t m_counter[AES_BLOCKLEN];

	Prng();

	void next_rand(uint8_t *result);
	void increment_counter();

public:
	static Prng& get_instance();

	void set_seed(uint8_t *seed);
	int rand_int(int min, int max);
};

#endif /* RNG_PRNG_H_ */
