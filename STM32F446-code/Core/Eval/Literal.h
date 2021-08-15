/*
 * Literal.h
 *
 *  Created on: Dec 26, 2020
 *      Author: sok
 */

#ifndef EVAL_LITERAL_H_
#define EVAL_LITERAL_H_

#include "Token.h"

class Literal : public Token {
public:
	virtual ~Literal() {}
	virtual int value() = 0;
};

#endif /* EVAL_LITERAL_H_ */
