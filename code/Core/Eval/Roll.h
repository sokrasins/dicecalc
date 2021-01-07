/*
 * Roll.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_ROLL_H_
#define EVAL_ROLL_H_

#include "Literal.h"

class Roll : public Literal {
	int m_sides;
	int m_rolls;
public:
	Roll() : m_sides(0), m_rolls(0) {};
	Roll(int sides, int rolls) : m_sides(sides), m_rolls(rolls) {};
	void set_sides(int sides) { m_sides = sides; };
	void set_rolls(int rolls) { m_rolls = rolls; };
	int value() override { return m_sides * m_rolls; }; // TODO
	TokenType get_type() override { return TOKEN_ROLL; };

	int get_sides() { return m_sides; };
	int get_rolls() { return m_rolls; };
};



#endif /* EVAL_ROLL_H_ */
