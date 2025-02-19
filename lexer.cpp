#include "lexer.h"
#include <iostream>

using namespace std;

// token definitions
Token::Token() {
  // default constructor
  /*tokenText = newTokenText;*/
  /*tokenType = newTokenType;*/
}

Token::~Token() {
  // destructor
}

Token::Token(const Token &t) {
  // copy constructor
  tokenText = t.tokenText;
  tokenType = t.tokenType;
}

Token &Token::operator=(const Token &t) {
  // copy assignment operator
  tokenText = t.tokenText;
  tokenType = t.tokenType;
  return *this;
}

// lexer definitions
Lexer::Lexer(string &new_source) {
  // default constructor
  source = new_source + "\n";
  // curChar = '';
  curPos = -1;
  nextChar();
}

Lexer::~Lexer() {
  // destructor
}

Lexer::Lexer(const Lexer &l) {
  // copy constructor
  source = l.source;
  curChar = l.curChar;
  curPos = l.curPos;
}

Lexer &Lexer::operator=(const Lexer &l) {
  source = l.source;
  curChar = l.curChar;
  curPos = l.curPos;
  return *this;
}

void Lexer::nextChar() {
  // process the next character
  curPos += 1;
  if (curPos >= source.size()) {
    curChar = '\0'; // EOF
  } else {
    curChar = source[curPos];
  }
}

char Lexer::peek() {
  // return the lookahead character
  if (curPos + 1 >= source.size()) {
    return '\0';
  }
  return source[curPos + 1];
}

void Lexer::abort(const string &message) {
  // invalid token found, print error message and exit
  cout << message << endl;
  return;
}

void Lexer::skipWhitespace() {} // will define later

void Lexer::skipComment() {} // will define later

Token Lexer::getToken() {
  // gets and labels/identifies the next token

  Token token;
  switch (curChar) {
  // checking first char of token to see if we can identify it
  case '+': // plus token
    token.tokenText = "+";
    token.tokenType = Token::TokenTypes::PLUS;
    break;
  case '-': // minus token
    token.tokenText = "-";
    token.tokenType = Token::TokenTypes::MINUS;
    break;
  case '*': // asteriks token
    token.tokenText = "*";
    token.tokenType = Token::TokenTypes::ASTERISK;
    break;
  case '/': // slash token
    token.tokenText = "/";
    token.tokenType = Token::TokenTypes::SLASH;
    break;
  case '\n': // newline token
    token.tokenText = "\n";
    token.tokenType = Token::TokenTypes::NEWLINE;
    break;
  case '\0': // eof token
    token.tokenText = "\0";
    token.tokenType = Token::TokenTypes::EOF_1;
    break;
  default: // unkown token
    string abrtstr = "Unkown token: ";
    abort(abrtstr += curChar);
  }

  nextChar();
  return token;
}
