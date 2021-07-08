#include "lexer/lexer.hpp"
#include <istream>
#include <algorithm>
#include <string>

namespace Lexer {

Lexer::Lexer(std::istream &is)
  : is(is)
{ 
	advance();
}

bool Lexer::has_more_tokens() const {
	return next.token == Token::None ? false : true;
}

void Lexer::advance() {
	curr = next;
	next = {};

	if (!is) return;
	char c;

	// get rid of whitespace
	do { c = is.get(); } while (is && isspace(c));
	is.putback(c);

	// get next token
	if (!is) return;
	c = is.get();
	if (std::isdigit(c)) { // check for number
		std::string num;
		do {
			num += c;
			c = is.get();
		} while (is && std::isdigit(c));
		is.putback(c);
		next = {Token::Int, std::stoi(num)};
		return;
	}
	if (std::isalpha(c)) { // check for keyword
		std::string keyword;
		do {
			keyword += c;
			c = is.get();
		} while (is && std::isalpha(c));
		std::transform(keyword.begin(), keyword.end(), keyword.begin(),
				[](unsigned char c){ return std::tolower(c); });

		if (keyword == "push")
			next = { Token::Push };
		else if (keyword == "pop")
			next = { Token::Pop };
		else if (keyword == "local")
			next = { Token::Local };
		else if (keyword == "argument")
			next = { Token::Argument };
		else if (keyword == "this")
			next = { Token::This };
		else if (keyword == "that")
			next = { Token::That };
		else if (keyword == "constant")
			next = { Token::Constant };
		else if (keyword == "static")
			next = { Token::Static };
		else if (keyword == "pointer")
			next = { Token::Pointer };
		else if (keyword == "temp")
			next = { Token::Temp };
		else if (keyword == "add")
			next = { Token::Add };
		else if (keyword == "sub")
			next = { Token::Sub };
		else
			throw std::runtime_error { std::string{"Lexer: invalid keyword: "} + keyword };
		return;
	}
	throw std::runtime_error { std::string{"Lexer: invalid input: "} + c };
}

Instruction Lexer::read() const {
	return curr;
}

std::string show_instruction(Instruction i) {
	switch (i.token) {
#define DISP(name) \
	case name: return #name
		DISP(Token::Push);
		DISP(Token::Pop);
		DISP(Token::Local);
		DISP(Token::Argument);
		DISP(Token::This);
		DISP(Token::That);
		DISP(Token::Constant);
		DISP(Token::Static);
		DISP(Token::Pointer);
		DISP(Token::Temp);
        	DISP(Token::Add);
		DISP(Token::Sub);
        	DISP(Token::None);
#undef DISP
	case Token::Int:
		return std::string{"Int: ("} + std::to_string(i.val) + ")";
	default:
		return "Unknown Token";
	}
}

}
