#ifndef __PARSER_H_
#define __PARSER_H_

#include <iostream>
#include <regex>
#include <tuple>

enum class Command { A_COMMAND, C_COMMAND, L_COMMAND };

struct Instruction {
	Command curr_type;
	// these should be a variant
	std::string symbol_val;
	std::tuple<std::string, std::string, std::string> c_command;
	int pos;
	bool valid;
};

class Parser {
	public:
		Parser(std::istream &is);

		// L_COMMAND not yet implemented
		bool has_more_commands() const;
		void advance(); // if ^ is true
		std::string symbol() const; // call if A_COMMAND or L_COMAND
		Command command_type() const;
		std::string dest() const; // call if C_COMMAND
		std::string comp() const; // call if C_COMMAND
		std::string jump() const; // call if C_COMMAND
		int pos() const; // useful for first pass, for L_COMMAND
	private:
		std::istream &is;
		Instruction curr;
		Instruction next;
};

#endif // __PARSER_H_
