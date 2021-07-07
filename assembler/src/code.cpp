#include "code.hpp"
#include <algorithm>
#include <stdexcept>
#include <map>

std::string stoupper(std::string i) {
	std::transform(i.begin(), i.end(), i.begin(), ::toupper);
	return i;
}

std::bitset<3> dest_code(std::string i) {
	std::string symbol = stoupper(i);
	if (symbol == "NULL") {
		return 0;
	}
	std::bitset<3> out;
	for (char c : symbol) {
		if (c == 'A') {
			out[2] = true;
		} else if (c == 'D') {
			out[1] = true;
		} else if (c == 'M') {
			out[0] = true;
		} else {
			throw std::runtime_error{"dest_code(): invalid dest, " + symbol};
		}
	}
	return out;
}

std::bitset<7> comp_code(std::string i) {
	const static std::map<std::string, std::bitset<7>> map {
		{"0", std::bitset<7>{"0101010"}},
		{"1", std::bitset<7>{"0111111"}},
		{"-1", std::bitset<7>{"0111010"}},
		{"D", std::bitset<7>{"0001100"}},
		{"A", std::bitset<7>{"0110000"}},
		{"!D", std::bitset<7>{"0001101"}},
		{"!A", std::bitset<7>{"0110001"}},
		{"-D", std::bitset<7>{"0001111"}},
		{"-A", std::bitset<7>{"0110011"}},
		{"D+1", std::bitset<7>{"0011111"}},
		{"A+1", std::bitset<7>{"0110111"}},
		{"D-1", std::bitset<7>{"0001110"}},
		{"A-1", std::bitset<7>{"0110010"}},
		{"D+A", std::bitset<7>{"0000010"}},
		{"D-A", std::bitset<7>{"0010011"}},
		{"A-D", std::bitset<7>{"0000111"}},
		{"D&A", std::bitset<7>{"0000000"}},
		{"D|A", std::bitset<7>{"0010101"}},
		{"M", std::bitset<7>{"1110000"}},
		{"!M", std::bitset<7>{"1110001"}},
		{"-M", std::bitset<7>{"1110011"}},
		{"M+1", std::bitset<7>{"1110111"}},
		{"M-1", std::bitset<7>{"1110010"}},
		{"D+M", std::bitset<7>{"1000010"}},
		{"D-M", std::bitset<7>{"1010011"}},
		{"M-D", std::bitset<7>{"1000111"}},
		{"D&M", std::bitset<7>{"1000000"}},
		{"D|M", std::bitset<7>{"1010101"}}
	};
	std::string symbol = stoupper(i);
	if (auto res = map.find(symbol); res != map.end()) {
		return res->second;
	}
	throw std::runtime_error("comp_code(): invalid comp, " + symbol);
}

std::bitset<3> jump_code(std::string i) {
	const static std::map<std::string, std::bitset<3>> map {
  	{"NULL", std::bitset<3>{"000"}},
		{"JGT", std::bitset<3>{"001"}},
		{"JEQ", std::bitset<3>{"010"}},
		{"JGE", std::bitset<3>{"011"}},
		{"JLT", std::bitset<3>{"100"}},
		{"JNE", std::bitset<3>{"101"}},
		{"JLE", std::bitset<3>{"110"}},
		{"JMP", std::bitset<3>{"111"}}
	};
	std::string symbol = stoupper(i);
	if (auto res = map.find(symbol); res != map.end()) {
		return res->second;
	}
	throw std::runtime_error("jump_code(): invalid jump, " + symbol);
}
