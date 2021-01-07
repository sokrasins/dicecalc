/*
 * ExpressionDisplay.h
 *
 *  Created on: Dec 31, 2020
 *      Author: sok
 */

#ifndef SYMBOL_EXPRESSIONDISPLAY_H_
#define SYMBOL_EXPRESSIONDISPLAY_H_

#include <vector>

#include "KeyEvent.h"
#include "LineEntry.h"

using namespace std;

//#define MAX_LINES 10

class ExpressionDisplay {
	vector<LineEntry*> m_stack;

	void add_symbol(Symbol& new_symbol);
	void new_line();
	void eval_last_expression();
public:
	ExpressionDisplay() { this->new_line(); };
	void key_event(KeyEvent* event);
	int num_lines() { return this->m_stack.size(); };
	LineEntry *line(uint16_t idx) { return this->m_stack[idx]; };
};



#endif /* SYMBOL_EXPRESSIONDISPLAY_H_ */
