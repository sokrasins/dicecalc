/*
 * Add.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_ADD_H_
#define EVAL_ADD_H_

#include "Operator.h"

class Add : public Operator {
public:
	Add() : Operator(OPTYPE_ADDITION, 3) {};
	int eval(int left, int right) override { return left + right; };
};



#endif /* EVAL_ADD_H_ */
