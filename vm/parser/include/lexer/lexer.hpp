#pragma once

#include <istream>

namespace Lexer {

enum class Token { Push, Pop,
	           Local, Argument, This, That, Constant, Static, Pointer, Temp,
                   Int,
                   Add, Sub,
                   None };

struct Instruction {
	Instruction(Token token=Token::None, int val=0) : token{token}, val{val} {}
	Token token;
	int val; // optional
};

class Lexer {
public:
	explicit Lexer(std::istream &is);

	bool has_more_tokens() const;
	void advance();
	Instruction read() const;
private:
	std::istream &is;
	Instruction curr;
	Instruction next;
};

std::string show_instruction(Instruction);

}
