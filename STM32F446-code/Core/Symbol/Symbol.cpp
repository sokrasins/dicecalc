/*
 * Symbol.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: sok
 */

#include "Symbol.h"

bool Symbols::m_needs_init = true;

Symbol Symbols::m_num[10];
Symbol Symbols::m_op[4];
Symbol Symbols::m_rand;

Symbol& Symbols::num(int num) {
	if (m_needs_init) {
		init();
		m_needs_init = false;
	}

	if ((num < 0) || (num > 9)) {
		// TODO: error
	}

	return m_num[num];
}

Symbol& Symbols::op(OperatorSymbolType op) {
	if (m_needs_init) {
		init();
		m_needs_init = false;
	}

	if ((op < 0) || (op > 3)) {
		// TODO: error
	}

	return m_op[op];
}

Symbol& Symbols::rand() {
	if (m_needs_init) {
		init();
		m_needs_init = false;
	}

	return m_rand;
}


void Symbols::init() {
	for (int i=0; i<10; i++) {
		m_num[i].type = SYMBOL_INTEGER;
		m_num[i].rep = std::to_string(i);
		m_num[i].data.as_int.value = i;
	}

	m_op[SYMBOL_MULTIPLICATION].type = SYMBOL_OPERATOR;
	m_op[SYMBOL_MULTIPLICATION].rep = "*";
	m_op[SYMBOL_MULTIPLICATION].data.as_op.op_type = SYMBOL_MULTIPLICATION;

	m_op[SYMBOL_DIVISION].type = SYMBOL_OPERATOR;
	m_op[SYMBOL_DIVISION].rep = "/";
	m_op[SYMBOL_DIVISION].data.as_op.op_type = SYMBOL_DIVISION;

	m_op[SYMBOL_ADDITION].type = SYMBOL_OPERATOR;
	m_op[SYMBOL_ADDITION].rep = "+";
	m_op[SYMBOL_ADDITION].data.as_op.op_type = SYMBOL_ADDITION;

	m_op[SYMBOL_SUBTRACTION].type = SYMBOL_OPERATOR;
	m_op[SYMBOL_SUBTRACTION].rep = "-";
	m_op[SYMBOL_SUBTRACTION].data.as_op.op_type = SYMBOL_SUBTRACTION;

	m_rand.type = SYMBOL_RAND;
	m_rand.rep = "d";
}


