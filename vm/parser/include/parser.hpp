#pragma once

#include "lexer.hpp"

namespace Parser {

class Parser {
public:
	Parser(Lexer &lexer);

	void expr();
private:
	bool accept(Token);
	void expect(Token);
	void dest();
	Lexer &lexer;
};

}
