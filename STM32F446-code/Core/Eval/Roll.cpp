/*
 * Roll.cpp
 *
 *  Created on: Jan 16, 2021
 *      Author: sok
 */

#include "Roll.h"

#include "Prng.h"

int Roll::value() {
	int result = 0;
	Prng& prng = Prng::get_instance();
	for (int i=0; i<this->m_rolls; i++) {
		result += prng.rand_int(1, this->m_sides);
	}
	return result;
}


