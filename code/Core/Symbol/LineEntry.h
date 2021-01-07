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
	public:
		LineEntry() {};
		void add_symbol(Symbol& val);
		bool can_eval();
		string to_string();
		int size();
		bool get(int idx, Symbol* sym);
};



#endif /* INC_LINEENTRY_H_ */
