/*
 * Mult.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_MULT_H_
#define EVAL_MULT_H_

#include "Operator.h"

class Mult : public Operator {
public:
	Mult() : Operator(OPTYPE_MULTIPLICATION, 2) {};
	int eval(int left, int right) override { return left * right; };
};



#endif /* EVAL_MULT_H_ */
