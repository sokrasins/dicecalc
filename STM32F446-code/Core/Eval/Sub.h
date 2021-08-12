/*
 * Sub.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_SUB_H_
#define EVAL_SUB_H_

#include "Operator.h"

class Sub : public Operator {
public:
	Sub() : Operator(OPTYPE_SUBTRACTION, 3) {};
	int eval(int left, int right) override { return left - right; };
};



#endif /* EVAL_SUB_H_ */
