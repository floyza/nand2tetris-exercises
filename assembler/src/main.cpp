#include <iostream>
#include <vector>
#include <fstream>
#include "parser.hpp"
#include "code.hpp"
#include "symbol_table.hpp"

std::vector<std::string> parse_args(int argc, char **argv) {
	std::vector<std::string> args;
	for (int i=0; i < argc; ++i)
		args.emplace_back(argv[i]);
	return args;
}

void usage(std::string_view progname) {
	std::cerr << "Usage: " << progname << " <prog.asm>\n";
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args = parse_args(argc, argv);
	if (args.size() < 2) {
		usage(args[0]);
		return -1;
	}
	std::string name = args[1];
	std::ifstream is{name};
	Symbol_table table;
	{
		// first pass, fill symbol table
		Parser p(is);
		while (p.has_more_commands()) {
			p.advance();
			if (p.command_type() == Command::L_COMMAND) {
				table.add_entry(p.symbol(), p.pos()+1);
			}
		}
	}
	// reset to begin
	is.clear();
	is.seekg(0, std::ios::beg);
	{
		// second pass, generate code
		Parser p(is);
		while (p.has_more_commands()) {
			p.advance();
			switch(p.command_type()) {
				case Command::A_COMMAND:
					try {
						int code = std::stoi(p.symbol());
						std::cout << '0' << std::bitset<15>(code) << "\n";
					} catch (std::invalid_argument&) {
						if (!table.contains(p.symbol())) {
							table.add_entry(p.symbol(), table.get_new_address());
						}
						//std::cout << p.symbol() << std::endl << table.get_address(p.symbol()) << std::endl;
						std::cout << '0' << std::bitset<15>(table.get_address(p.symbol())) << "\n";
					}
					break;
				case Command::C_COMMAND:
					std::cout << "111" << comp_code(p.comp()) << dest_code(p.dest()) << jump_code(p.jump()) << "\n";
					break;
				case Command::L_COMMAND:
					// ignore
					break;
			}
		}
	}
}
