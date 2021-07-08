#include "lexer.hpp"
#include <istream>

namespace Parser {

Lexer::Lexer(std::istream &is)
  : is(is)
{ }

bool Lexer::has_more_tokens() const {
	return next.token == Token::None ? true : false;
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

		if (keyword == "push")
			next = { Token::Push };
		else
			throw std::runtime_error { std::string{"Lexer: invalid keyword: "} + keyword };
		return;
	}
	throw std::runtime_error { std::string{"Lexer: invalid input: "} + c };
}

Instruction Lexer::read() const {
	return curr;
}

}
