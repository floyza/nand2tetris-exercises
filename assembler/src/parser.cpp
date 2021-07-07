#include <cassert>
#include "parser.hpp"

Parser::Parser(std::istream &is)
	: is{is}
{
	next.pos = -1;
	advance();
	// curr is in an undefined state
}

bool Parser::has_more_commands() const
{
	return next.valid;
}

void Parser::advance()
{
	// one issue with this regex:
	// it accepts expressions with empty dest, eg.
	// `=1;JMP` or `=A`
	// also see 'setup.org' in the project root for more info on the regex
	const static std::regex language_regex
		{
		R"((?:(@((?:[0-9]+)|(?:[A-Z_.$:][A-Z_.$:0-9]*)))|((?:((?:null)|(?:A?M?D?))=)?([01DAM\-+&|!]+)(?:;((?:null)|(?:JGT)|(?:JEQ)|(?:JGE)|(?:JLT)|(?:JNE)|(?:JLE)|(?:JMP)))?))|(?:\(([A-Z_.$:][A-Z_.$:0-9]*)\))|(?:\/\/.*))",
		std::regex::icase
	};
	std::string line;
	std::getline(is, line);
	std::smatch results;
	std::regex_search(line, results, language_regex);
	if (results[2].matched) {
		curr = next;
		next.pos = curr.pos + 1;
		next.valid = true;
		next.curr_type = Command::A_COMMAND;
		next.symbol_val = results[2].str();
		return;
	} else if (results[3].matched && (results[4].matched || results[6].matched)) {
		curr = next;
		next.pos = curr.pos + 1;
		next.valid = true;
		next.curr_type = Command::C_COMMAND;
		if (results[4].matched) {
			assert(results[4].length() > 0);
			std::get<0>(next.c_command) = results[4].str();
		} else {
			std::get<0>(next.c_command) = "null";
		}
		if (results[6].matched) {
			std::get<2>(next.c_command) = results[6].str();
		} else {
			std::get<2>(next.c_command) = "null";
		}
		std::get<1>(next.c_command) = results[5].str();
		return;
	} else if (results[7].matched) {
		curr = next;
		next.pos = curr.pos;
		next.valid = true;
		next.curr_type = Command::L_COMMAND;
		next.symbol_val = results[7].str();
		return;
	}
	if (!is) {
		curr = next;
		next.valid = false;
		return;
	}
	// no match and not at end, keep going
	advance();
}

auto Parser::command_type() const -> Command {
	return curr.curr_type;
}

std::string Parser::dest() const {
	return std::get<0>(curr.c_command);
}

std::string Parser::comp() const {
	return std::get<1>(curr.c_command);
}

std::string Parser::jump() const {
	return std::get<2>(curr.c_command);
}

std::string Parser::symbol() const {
	return curr.symbol_val;
}

int Parser::pos() const {
	return curr.pos;
}
