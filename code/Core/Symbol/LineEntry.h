/*
 * LineEntry.h
 *
 *  Created on: Dec 25, 2020
 *      Author: sok
 */

#ifndef INC_LINEENTRY_H_
#define INC_LINEENTRY_H_

#include <vector>
#include <string>

#include "Symbol.h"

using namespace std;

class LineEntry {
		vector<Symbol *> m_line;
		bool m_result;
	public:
		LineEntry();
		void add_symbol(Symbol& val);
		bool can_eval();
		string to_string();
		int size();
		bool get(int idx, Symbol* sym);
		bool is_result() { return this->m_result; };
		void set_result(bool result) { this->m_result = result; };
		void remove_last_symbol();

};



#endif /* INC_LINEENTRY_H_ */
