#include "symbol_table.hpp"
#include <iostream>
#include <cassert>

Symbol_table::Symbol_table() {
	symbol_defs["SP"] = 0;
	symbol_defs["LCL"] = 1;
	symbol_defs["ARG"] = 2;
	symbol_defs["THIS"] = 3;
	symbol_defs["THAT"] = 4;
	symbol_defs["SCREEN"] = 16384;
	symbol_defs["KBD"] = 24576;
	symbol_defs["R0"] = 0;
	symbol_defs["R1"] = 1;
	symbol_defs["R2"] = 2;
	symbol_defs["R3"] = 3;
	symbol_defs["R4"] = 4;
	symbol_defs["R5"] = 5;
	symbol_defs["R6"] = 6;
	symbol_defs["R7"] = 7;
	symbol_defs["R8"] = 8;
	symbol_defs["R9"] = 9;
	symbol_defs["R10"] = 10;
	symbol_defs["R11"] = 11;
	symbol_defs["R12"] = 12;
	symbol_defs["R13"] = 13;
	symbol_defs["R14"] = 14;
	symbol_defs["R15"] = 15;
}

void Symbol_table::add_entry(std::string symbol, int address)
{
	if (symbol_defs.find(symbol) != symbol_defs.end()) {
		std::cerr << "WARNING: refinition of '" << symbol << "'\n";
	}
	symbol_defs[symbol] = address;
}

bool Symbol_table::contains(const std::string &symbol) const
{
	return symbol_defs.find(symbol) != symbol_defs.end();
}

int Symbol_table::get_address(const std::string &symbol) const
{
	auto i = symbol_defs.find(symbol);
	assert(i != symbol_defs.end());
	return i->second;
}

int Symbol_table::get_new_address()
{
	int addr = addr_cnt++;
	if (addr >= 16384) {
		throw std::runtime_error{"Symbol_table::get_new_address(): all addresses used up"};
	}
	return addr;
}
