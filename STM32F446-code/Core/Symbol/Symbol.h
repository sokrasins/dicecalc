/*
 * Symbol.h
 *
 *  Created on: Dec 25, 2020
 *      Author: sok
 */

#ifndef INC_SYMBOL_H_
#define INC_SYMBOL_H_

#include <string>

using namespace std;

enum SymbolType{
	SYMBOL_OPERATOR, SYMBOL_INTEGER, SYMBOL_RAND
};

enum OperatorSymbolType {
	SYMBOL_MULTIPLICATION, SYMBOL_DIVISION, SYMBOL_ADDITION, SYMBOL_SUBTRACTION
};

struct IntegerSymbol {
	int value;
};

struct OperatorSymbol {
	OperatorSymbolType op_type;
};

struct RandSymbol {
	// Nothing right now
};

union SymbolData {
	IntegerSymbol as_int;
	OperatorSymbol as_op;
	RandSymbol as_rand;
};

struct Symbol {
	SymbolType type;
	string rep;
	SymbolData data;
};

class Symbols {
	static bool m_needs_init;
	static Symbol m_num[10];
	static Symbol m_op[4];
	static Symbol m_rand;

	static void init();
public:
	static Symbol& num(int num);
	static Symbol& op(OperatorSymbolType op);
	static Symbol& rand();
};

#endif /* INC_SYMBOL_H_ */
