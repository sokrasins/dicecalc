/*
 * Token.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_TOKEN_H_
#define EVAL_TOKEN_H_

enum TokenType {
	TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_ROLL, TOKEN_NONE
};

class Token {
public:
	virtual ~Token() {};
	virtual TokenType get_type() = 0;
};

#endif /* EVAL_TOKEN_H_ */
