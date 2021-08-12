/*
 * Operator.h
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#ifndef EVAL_OPERATOR_H_
#define EVAL_OPERATOR_H_

#include "Token.h"

#define LOWEST_ORDER 10

enum OperatorTokenType {
	OPTYPE_ADDITION,
	OPTYPE_SUBTRACTION,
	OPTYPE_MULTIPLICATION,
	OPTYPE_DIVISION,
	OPTYPE_NONE
};

class Operator : public Token {
protected:
	OperatorTokenType m_optype;
	int m_order;
public:
	Operator() : m_optype(OPTYPE_NONE), m_order(LOWEST_ORDER) {};
	virtual ~Operator() {};
	Operator(OperatorTokenType op_type, int order) : m_optype(op_type), m_order(order) {};
	TokenType get_type() override { return TOKEN_OPERATOR; };
	virtual int eval(int left, int right) = 0;
	OperatorTokenType op_type() { return m_optype; };
	int order() { return m_order; };
};



#endif /* EVAL_OPERATOR_H_ */
