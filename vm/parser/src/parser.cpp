#include "parser.hpp"


namespace Parser {

Parser::Parser(Lexer &lexer)
  : lexer{lexer}
{
}

bool Parser::accept(Token t) {
	if (lexer.read().token == t) {
		return true;
	}
	return false;
}

void Parser::expect(Token t) {
	if (lexer.read().token == t) {
		return;
	}
	throw std::runtime_error {
		std::string("Expected: ") + 
			show_instruction(t) +
			", received: " +
			show_instruction(lexer.read()) +
			"\n" };
}

void Parser::expr() {
	lexer.advance();
	if (accept(Token::Push) || accept(Token::Pop)) {
		dest();
		expect(Token::EOL);
	} else if (accept(Token::Add) || accept(Token::Sub)) {
		lexer.advance();
		expect(Token::Int);
		lexer.advance();
		expect(Token::EOL);
	}
}

void Parser::dest() {
	lexer.advance();
	if (!(accept(Token::Local)    || accept(Token::Argument) ||
	      accept(Token::This)     || accept(Token::That) ||
	      accept(Token::Constant) || accept(Token::Static) ||
	      accept(Token::Pointer)  || accept(Token::Temp))) {
		throw std::runtime_error { std::string("Invalid destination: got ") + show_instruction(lexer.read()) + "\n" };
	}
	lexer.advance();
	expect(Token::Int);
}

}
