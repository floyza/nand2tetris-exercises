#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char **argv) {
  Parser::Lexer lex{std::cin};
  Parser::Parser parser{lex};

  parser.expr();

  /*
  while (lex.has_more_tokens()) {
          lex.advance();
          std::cerr << show_instruction(lex.read()) << '\n';
  }
  */
}
