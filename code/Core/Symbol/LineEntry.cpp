/*
 * LineEntry.cpp
 *
 *  Created on: Dec 25, 2020
 *      Author: sok
 */

#include "LineEntry.h"

#include <string>
#include <stdint.h>

#include "Symbol.h"

using namespace std;

LineEntry::LineEntry() :
m_result(false)
{

}

void LineEntry::add_symbol(Symbol& val) {
	m_line.push_back(&val);
}


bool LineEntry::can_eval() {
	return !m_line.empty();
}

string LineEntry::to_string() {
	string ret_val;

	for(uint8_t i=0; i < m_line.size(); i++){
	   ret_val.append(m_line[i]->rep);
	}

	return ret_val;
}

int LineEntry::size() {
	return m_line.size();
}

bool LineEntry::get(int idx, Symbol* sym) {
	if (idx >= size()) {
		return false;
	}
	*sym = *m_line[idx];
	return true;
}
