#ifndef LEXER
#define LEXER

// will fix func declarations as I go
#include <string>

class Lexer {
  // declaring private vars

public:
  std::string source;
  char curChar;
  int curPos;

  // obj management
  Lexer(std::string &new_source);   // constructor
  ~Lexer();                         // destructor
  Lexer(const Lexer &l);            // copy constructor
  Lexer &operator=(const Lexer &l); // copy assignment operator

  // process the next char
  void nextChar();

  // return the lookahead character
  char peek();

  // invalid token found, print error message and exit
  void abort(std::string &message);

  // skip withespace except newlines, which we will use to indicate the [token]?
  void skipWhitespace();

  // skip comments in the code
  void skipComment();

  // return the next token
  void getToken();
};

#endif
