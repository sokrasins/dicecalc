/*
 * Div.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_DIV_H_
#define EVAL_DIV_H_

#include "Operator.h"

class Div : public Operator {
public:
	Div() : Operator(OPTYPE_DIVISION, 2) {};
	int eval(int left, int right) override { return left / right; };
};



#endif /* EVAL_DIV_H_ */
