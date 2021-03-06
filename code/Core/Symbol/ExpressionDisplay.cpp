/*
 * ExpressionDisplay.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: sok
 */

#include "ExpressionDisplay.h"

#include <assert.h>

#include "Expression.h"
#include "Symbol.h"

void ExpressionDisplay::key_event(KeyEvent* event) {
	if (event->state == KEYSTATE_UP) {
		return;
	}

	switch(event->key) {
	case KEY_0:
		this->add_symbol(Symbols::num(0));
		break;
	case KEY_1:
		this->add_symbol(Symbols::num(1));
		break;
	case KEY_2:
		this->add_symbol(Symbols::num(2));
		break;
	case KEY_3:
		this->add_symbol(Symbols::num(3));
		break;
	case KEY_4:
		this->add_symbol(Symbols::num(4));
		break;
	case KEY_5:
		this->add_symbol(Symbols::num(5));
		break;
	case KEY_6:
		this->add_symbol(Symbols::num(6));
		break;
	case KEY_7:
		this->add_symbol(Symbols::num(7));
		break;
	case KEY_8:
		this->add_symbol(Symbols::num(8));
		break;
	case KEY_9:
		this->add_symbol(Symbols::num(9));
		break;
	case KEY_PLUS:
		this->add_symbol(Symbols::op(SYMBOL_ADDITION));
		break;
	case KEY_MINUS:
		this->add_symbol(Symbols::op(SYMBOL_SUBTRACTION));
		break;
	case KEY_TIMES:
		this->add_symbol(Symbols::op(SYMBOL_MULTIPLICATION));
		break;
	case KEY_DIV:
		this->add_symbol(Symbols::op(SYMBOL_DIVISION));
		break;
	case KEY_D:
		this->add_symbol(Symbols::rand());
		break;
	case KEY_D4:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(4));
		break;
	case KEY_D6:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(6));
		break;
	case KEY_D8:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(8));
		break;
	case KEY_D10:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(1));
		this->add_symbol(Symbols::num(0));
		break;
	case KEY_D12:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(1));
		this->add_symbol(Symbols::num(2));
		break;
	case KEY_D20:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(2));
		this->add_symbol(Symbols::num(0));
		break;
	case KEY_D100:
		this->add_symbol(Symbols::rand());
		this->add_symbol(Symbols::num(1));
		this->add_symbol(Symbols::num(0));
		this->add_symbol(Symbols::num(0));
		break;
	case KEY_ENTER: {
		LineEntry *eval_line = this->m_stack.back();
		if (eval_line->size() > 0) {
			this->new_line();
			this->eval_expression(eval_line);
		} else {
			for (int i = this->m_stack.size(); i>0; i--) {
				eval_line = this->m_stack[(i-1)];
				if (eval_line->size() > 0 && !eval_line->is_result()) {
					break;
				}
			}
			this->eval_expression(eval_line);
		}
		break;
	}

	case KEY_BACKSPACE:
		this->remove_last_symbol();
		break;
	case KEY_CLEARLINE:
		delete this->m_stack.back();
		this->m_stack.pop_back();
		this->new_line();
		break;
	case KEY_CLEARALL:
		for (uint16_t idx=0; idx<this->m_stack.size(); idx++) {
			delete this->m_stack[idx];
		}
		this->m_stack.clear();
		this->new_line();
		break;

	default:
		// TODO: ERROR
		break;
	}
}

void ExpressionDisplay::eval_expression(LineEntry *line) {
	Expression *expr = new Expression();
	expr->convert_from_entry(*line);

	if (expr->can_eval()) {
		bool success = expr->eval();
		assert(success);
		//this->new_line();
		expr->write_to_entry(*(this->m_stack.back()));
		this->m_stack.back()->set_result(true);
		this->new_line();
	} else {
		// TODO: Display an error somehow?
	}

	delete expr;
}

void ExpressionDisplay::add_symbol(Symbol& new_symbol) {
	this->m_stack.back()->add_symbol(new_symbol);
}

void ExpressionDisplay::remove_last_symbol() {
	LineEntry *last_line = this->m_stack.back();
	if (last_line->size() > 0) {
		last_line->remove_last_symbol();
	}
}

void ExpressionDisplay::new_line() {
	this->m_stack.push_back(new LineEntry());
}
