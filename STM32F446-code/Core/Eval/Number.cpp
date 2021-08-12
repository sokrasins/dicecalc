/*
 * Number.cpp
 *
 *  Created on: Dec 26, 2020
 *      Author: sok
 */

#include "Number.h"

void Number::add_least_sig_digit(int new_digit) {
	m_value = m_value * 10 + new_digit;
}
