/*
 * Expression.h
 *
 *  Created on: Dec 26, 2020
 *      Author: sok
 */

#ifndef EVAL_EXPRESSION_H_
#define EVAL_EXPRESSION_H_

#include "LineEntry.h"

#include <vector>

#include "Token.h"

using namespace std;

class Expression {
	vector<Token*> m_expr;
	void add_token(Token& token);
	int find_highest_order_op();
	void write_number_to_entry(int num, LineEntry& entry);
public:
	Expression() {};
	~Expression();
	bool convert_from_entry(LineEntry& entry);
	bool write_to_entry(LineEntry& entry);
	bool can_eval();
	bool eval();
};

#endif /* EVAL_EXPRESSION_H_ */
