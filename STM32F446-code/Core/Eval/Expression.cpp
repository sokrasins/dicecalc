/*
 * Expression.cpp
 *
 *  Created on: Dec 29, 2020
 *      Author: sok
 */

#include "Expression.h"

#include <stdint.h>

#include "LineEntry.h"
#include "Symbol.h"

#include "Add.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"
#include "Roll.h"
#include "Number.h"

void Expression::add_token(Token& token) {
	m_expr.push_back(&token);
}

Expression::~Expression() {
	for (uint16_t i=0; i<m_expr.size(); i++) {
		Token *token = m_expr[i];
		delete token;
	}
}

bool Expression::can_eval() {
	if (m_expr.size() == 0) {
		return false;
	}

	if (m_expr.size() % 2 == 0) {
		return false;
	}

	// TODO: Check calc-ability

	return true;
}

int Expression::find_highest_order_op() {
	int first_order = LOWEST_ORDER;
	int idx = -1;

	for (uint16_t i=0; i<m_expr.size(); i++) {
		Token *next_token = m_expr[i];
		if (next_token->get_type() == TOKEN_OPERATOR) {
			int this_order = ((Operator *)next_token)->order();
			if (this_order < first_order) {
				first_order = this_order;
				idx = i;
			}
		}
	}
	return idx;
}

bool Expression::eval() {
	if (!this->can_eval()) {
		return false;
	}

	size_t vec_size = this->m_expr.size();

	while ((vec_size > 1)) {
		// Find next operation to evaluate
		int op_idx = find_highest_order_op();
		if (op_idx < 0) { return false; }

		// Get neighbor tokens
		Operator* op = (Operator *)this->m_expr[op_idx];
		Literal* left_val = (Literal *)this->m_expr[op_idx-1];
		Literal* right_val = (Literal *)this->m_expr[op_idx+1];

		// Evaluate operation
		int result = op->eval(left_val->value(), right_val->value());

		// Remove consumed tokens
		this->m_expr.erase(this->m_expr.begin()+(op_idx-1), this->m_expr.begin()+(op_idx+2));
		delete op;
		delete left_val;
		delete right_val;

		//Add result as a new token
		Number *result_literal = new Number(result);
		this->m_expr.insert(this->m_expr.begin()+(op_idx-1), result_literal);

		vec_size = this->m_expr.size();
	}

	// If the last token is a roll, then we need to evaluate
	// it, and push a number back to the stack
	Token *last_token = this->m_expr.back();
	if (last_token->get_type() == TOKEN_ROLL) {
		Roll *last_roll = (Roll *)last_token;
		this->m_expr.clear();
		Number *final_result = new Number(last_roll->value());
		delete last_token;
		this->m_expr.push_back(final_result);
	}

	return true;
}


// TODO: Convert LineEntry to be an iterable, so this method can be streamlined
bool Expression::convert_from_entry(LineEntry& entry) {
	m_expr.clear();
	Token* new_token;
	TokenType last_token_type = TOKEN_NONE;

	for (int i=0; i<entry.size(); i++) {
		Symbol sym;
		bool success = entry.get(i, &sym);

		if (m_expr.empty()) {
			last_token_type = TOKEN_NONE;
		} else {
			last_token_type = m_expr.back()->get_type();
		}

		switch(sym.type) {

		case SYMBOL_OPERATOR:
			switch(sym.data.as_op.op_type) {

			case SYMBOL_ADDITION:
				new_token = new Add();
				break;

			case SYMBOL_SUBTRACTION:
				new_token = new Sub();
				break;

			case SYMBOL_MULTIPLICATION:
				new_token = new Mult();
				break;

			case SYMBOL_DIVISION:
				new_token = new Div();
				break;
			}
			add_token(*new_token);
			break;

		case SYMBOL_INTEGER:
			new_token = new Number();
			do {
				((Number*)new_token)->add_least_sig_digit(sym.data.as_int.value);
				success = entry.get(++i, &sym);
			} while (success && (sym.type == SYMBOL_INTEGER));
			i--;

			if (last_token_type == TOKEN_ROLL) {
				int literal_val = ((Literal*)new_token)->value();
				((Roll *)m_expr.back())->set_sides(literal_val);
				delete new_token;
			} else {
				add_token(*new_token);
			}
			break;

		case SYMBOL_RAND:
			int num_rolls = 1;
			if (last_token_type == TOKEN_NUMBER) {
				Number *last_lit = (Number *)m_expr.back();
				num_rolls = last_lit->value();
				m_expr.pop_back();
				delete last_lit;
			}

			new_token = new Roll(0, num_rolls);
			add_token(*new_token);
			break;
		}

	}
	return true;
}

bool Expression::write_to_entry(LineEntry& entry) {
	for (uint16_t i=0; i<this->m_expr.size(); i++) {
		Token* token = m_expr[i];

		switch(token->get_type()) {
		case TOKEN_NUMBER: {
			int token_val = ((Number *)token)->value();
			this->write_number_to_entry(token_val, entry);
			break;
		}

		case TOKEN_OPERATOR:
			switch(((Operator *)token)->op_type()) {
			case OPTYPE_ADDITION:
				entry.add_symbol(Symbols::op(SYMBOL_ADDITION));
				break;

			case OPTYPE_SUBTRACTION:
				entry.add_symbol(Symbols::op(SYMBOL_SUBTRACTION));
				break;

			case OPTYPE_MULTIPLICATION:
				entry.add_symbol(Symbols::op(SYMBOL_MULTIPLICATION));
				break;

			case OPTYPE_DIVISION:
				entry.add_symbol(Symbols::op(SYMBOL_DIVISION));
				break;

			default:
				break;
			}
			break;

		case TOKEN_ROLL: {
			int sides = ((Roll *)token)->get_sides();
			int rolls = ((Roll *)token)->get_rolls();
			if (rolls != 1) {
				this->write_number_to_entry(rolls, entry);
			}
			entry.add_symbol(Symbols::rand());
			this->write_number_to_entry(sides, entry);
			break;
		}

		default:
			break;
		}
	}
	return true;
}

void Expression::write_number_to_entry(int num, LineEntry& entry) {
	int num_digits = 0;
	int factor = 1;

	while (num / factor > 0) {
		num_digits++;
		factor *= 10;
	}

	for (int i=num_digits; i>0; i--) {
		factor = 1;
		for (int j=0; j<(i-1); j++) {
			factor *= 10;
		}

		int digit = num / factor;
		entry.add_symbol(Symbols::num(digit));

		num = num % factor;
	}
}

