#ifndef __SYMBOL_TABLE_H_
#define __SYMBOL_TABLE_H_

#include <string>
#include <map>

class Symbol_table {
	public:
		Symbol_table();
		void add_entry(std::string symbol, int address);
		bool contains(const std::string &symbol) const;
		int get_address(const std::string &symbol) const;
		int get_new_address();
	private:
		std::map<std::string, int> symbol_defs;
		int addr_cnt = 16;
};

#endif // __SYMBOL_TABLE_H_
