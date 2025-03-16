#ifndef LEXER
#define LEXER

// will fix func declarations as I go
#include <ostream>
#include <string>

class Token {
  // token class, contains original text and type

public:
  enum class TokenTypes {
    EOF_1 = -1,
    NEWLINE = 0,
    NUMBER = 1,
    IDENT = 2,
    STRING = 3,
    // keywords
    LABEL = 101,
    GOTO = 102,
    PRINT = 103,
    INPUT = 104,
    LET = 105,
    IF = 106,
    THEN = 107,
    ENDIF = 108,
    WHILE = 109,
    REPEAT = 110,
    ENDWHILE = 111,
    // operators
    EQ = 201,
    PLUS = 202,
    MINUS = 203,
    ASTERISK = 204,
    SLASH = 205,
    EQEQ = 206,
    NOTEQ = 207,
    LT = 208,
    LTEQ = 209,
    GT = 210,
    GTEQ = 211,
  };

  std::string tokenText;
  TokenTypes tokenType;

  // obj management
  Token();                          // constructor
  ~Token();                         // destructor
  Token(const Token &t);            // copy constructor
  Token &operator=(const Token &t); // copy assignment operator
  friend std::ostream &operator<<(std::ostream &os, const Token::TokenTypes &t);
};

class Lexer {
  // lexer object class

public:
  std::string source;
  char curChar;
  int curPos;

  // obj management
  Lexer(const std::string &new_source); // constructor
  ~Lexer();                             // destructor
  Lexer(const Lexer &l);                // copy constructor
  Lexer &operator=(const Lexer &l);     // copy assignment operator

  // process the next char
  void nextChar();

  // return the lookahead character
  char peek();

  // invalid token found, print error message and exit
  void abort(const std::string &message);

  // skip whitespace except newlines, which we will use to indicate the
  // [token]?
  void skipWhitespace();

  // skip comments in the code
  void skipComment();

  // checks if given string is number
  bool isNum(const std::string &s);

  // return the next token
  Token getToken();
};

#endif
