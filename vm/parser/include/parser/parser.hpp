#pragma once

class Parser {
public:
	Parser(std::istream &is);

	bool has_more_instructions() const;
	void advance();
private:
	std::istream &is;
};
