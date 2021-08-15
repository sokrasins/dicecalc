/*
 * Number.h
 *
 *  Created on: Dec 30, 2020
 *      Author: sok
 */

#ifndef EVAL_NUMBER_H_
#define EVAL_NUMBER_H_

#include "Literal.h"

class Number : public Literal {
	int m_value;
public:
	Number() : m_value(0) {};
	Number(int value) : m_value(value) {};
	void add_least_sig_digit(int new_digit);
	int value() override { return m_value; };
	TokenType get_type() override { return TOKEN_NUMBER; };
};



#endif /* EVAL_NUMBER_H_ */
