#include <iostream>
#include "lexer/lexer.hpp"

using namespace Lexer;

int main(int argc, char **argv) {
	Lexer::Lexer lex {std::cin};
	while (lex.has_more_tokens()) {
		lex.advance();
		std::cerr << show_instruction(lex.read()) << '\n';
	}
}
