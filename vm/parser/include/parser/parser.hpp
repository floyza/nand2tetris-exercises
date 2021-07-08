#pragma once

#include "lexer/lexer.hpp"

namespace Parser {

class Parser {
public:
	Parser(Lexer::Lexer &lexer);

	void expr();
private:
	bool accept(Lexer::Token);
	void expect(Lexer::Token);
	void dest();
	Lexer::Lexer &lexer;
};

}
