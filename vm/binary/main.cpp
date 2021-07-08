#include <iostream>
#include "parser/lexer.hpp"

using namespace Parser;

int main(int argc, char **argv) {
	Lexer lex {std::cin};
	while (lex.has_more_tokens())
		lex.advance();
}
