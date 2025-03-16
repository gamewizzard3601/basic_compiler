#include "lexer.h"
#include <cctype>
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
Lexer::Lexer(const string &new_source) {
  // default constructor
  source = new_source + "\n";
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
  // copy assignment operator
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
  cout << "aborted: " << message << endl;
  return;
}

void Lexer::skipWhitespace() {
  while (curChar == ' ') {
    nextChar();
  }
}

void Lexer::skipComment() {
  // its assumed that comment has already been detected so we skip to nextline
  while (curChar != '\n' and curChar != '\0') {
    nextChar();
  }
  nextChar();
}

std::ostream &operator<<(std::ostream &os, const Token::TokenTypes &t) {
  switch (t) {
  case Token::TokenTypes::EOF_1:
    os << "EOF_1";
    return os;
  case Token::TokenTypes::NEWLINE:
    os << "NEWLINE";
    return os;
  case Token::TokenTypes::NUMBER:
    os << "NUMBER";
    return os;
  case Token::TokenTypes::IDENT:
    os << "IDENT";
    return os;
  case Token::TokenTypes::STRING:
    os << "STRING";
    return os;
  case Token::TokenTypes::LABEL:
    os << "LABEL";
    return os;
  case Token::TokenTypes::GOTO:
    os << "GOTO";
    return os;
  case Token::TokenTypes::PRINT:
    os << "PRINT";
    return os;
  case Token::TokenTypes::INPUT:
    os << "INPUT";
    return os;
  case Token::TokenTypes::LET:
    os << "LET";
    return os;
  case Token::TokenTypes::IF:
    os << "IF";
    return os;
  case Token::TokenTypes::THEN:
    os << "THEN";
    return os;
  case Token::TokenTypes::ENDIF:
    os << "ENDIF";
    return os;
  case Token::TokenTypes::WHILE:
    os << "WHILE";
    return os;
  case Token::TokenTypes::REPEAT:
    os << "REPEAT";
    return os;
  case Token::TokenTypes::ENDWHILE:
    os << "ENDWHILE";
    return os;
  case Token::TokenTypes::EQ:
    os << "EQ";
    return os;
  case Token::TokenTypes::PLUS:
    os << "PLUS";
    return os;
  case Token::TokenTypes::MINUS:
    os << "MINUS";
    return os;
  case Token::TokenTypes::ASTERISK:
    os << "ASTERISK";
    return os;
  case Token::TokenTypes::SLASH:
    os << "SLASH";
    return os;
  case Token::TokenTypes::EQEQ:
    os << "EQEQ";
    return os;
  case Token::TokenTypes::NOTEQ:
    os << "NOTEQ";
    return os;
  case Token::TokenTypes::LT:
    os << "LT";
    return os;
  case Token::TokenTypes::LTEQ:
    os << "LTEQ";
    return os;
  case Token::TokenTypes::GT:
    os << "GT";
    return os;
  case Token::TokenTypes::GTEQ:
    os << "GTEQ";
    return os;
  }
  os << "invalid token";
  return os;
}

bool Lexer::isNum(const string &s) {
  try {
    stof(s);
  } catch (const exception) {
    return false;
  }
  return true;
}

Token Lexer::getToken() {
  // gets and labels/identifies the next token

  Token token;
  Lexer::skipWhitespace();
  switch (curChar) {
  // checking first char of token to see if we can identify it
  case '+': // plus token
    token.tokenText = "+";
    token.tokenType = Token::TokenTypes::PLUS;
    nextChar();
    return token;
  case '-': // minus token
    if (Lexer::peek() == ' ' or Lexer::peek() == '\n' or
        Lexer::peek() == '\0') {
      token.tokenText = "-";
      token.tokenType = Token::TokenTypes::MINUS;
      nextChar();
      return token;
    }
    break;
  case '*': // asteriks token
    token.tokenText = "*";
    token.tokenType = Token::TokenTypes::ASTERISK;
    nextChar();
    return token;
  case '/': // slash token
    token.tokenText = "/";
    token.tokenType = Token::TokenTypes::SLASH;
    nextChar();
    return token;
  case '\n': // newline token
    token.tokenText = "\n";
    token.tokenType = Token::TokenTypes::NEWLINE;
    nextChar();
    return token;
  case '\0': // eof token
    token.tokenText = "\0";
    token.tokenType = Token::TokenTypes::EOF_1;
    nextChar();
    return token;
  case '\"': // string token
    token.tokenType = Token::TokenTypes::STRING;
    int tokenStartIndex = curPos + 1;
    nextChar();
    while (curChar != '\0' and curChar != '\"' and curChar != '\n') {
      nextChar();
    }
    token.tokenText = source.substr(tokenStartIndex, curPos - 1);
    if (curChar != '\"') {
      abort("unclosed string: " + token.tokenText);
    }
    nextChar();
    return token;
  }

  // get rest of token to next ' '
  int tokenStartIndex = curPos;
  while (curChar != ' ' and curChar != '\0' and curChar != '\n') {
    nextChar();
  }
  token.tokenText = source.substr(tokenStartIndex, curPos);

  // there's got to be a better way to do this
  if (token.tokenText == "==") { // operators
    token.tokenType = Token::TokenTypes::EQEQ;
  } else if (token.tokenText == "!=") {
    token.tokenType = Token::TokenTypes::NOTEQ;
  } else if (token.tokenText == ">=" or token.tokenText == "=>") {
    token.tokenType = Token::TokenTypes::GTEQ;
  } else if (token.tokenText == "<=" or token.tokenText == "=<") {
    token.tokenType = Token::TokenTypes::LTEQ;
  } else if (token.tokenText == "LABEL") { // keywords
    token.tokenType = Token::TokenTypes::LABEL;
  } else if (token.tokenText == "GOTO") {
    token.tokenType = Token::TokenTypes::GOTO;
  } else if (token.tokenText == "PRINT") {
    token.tokenType = Token::TokenTypes::PRINT;
  } else if (token.tokenText == "INPUT") {
    token.tokenType = Token::TokenTypes::INPUT;
  } else if (token.tokenText == "LET") {
    token.tokenType = Token::TokenTypes::LET;
  } else if (token.tokenText == "IF") {
    token.tokenType = Token::TokenTypes::IF;
  } else if (token.tokenText == "THEN") {
    token.tokenType = Token::TokenTypes::THEN;
  } else if (token.tokenText == "ENDIF") {
    token.tokenType = Token::TokenTypes::ENDIF;
  } else if (token.tokenText == "WHILE") {
    token.tokenType = Token::TokenTypes::WHILE;
  } else if (token.tokenText == "REPEAT") {
    token.tokenType = Token::TokenTypes::REPEAT;
  } else if (token.tokenText == "ENDWHILE") {
    token.tokenType = Token::TokenTypes::ENDWHILE;
  } else if (isNum(token.tokenText)) {
    token.tokenType = Token::TokenTypes::NUMBER;
  } else {
    token.tokenType = Token::TokenTypes::IDENT;
  }

  nextChar();
  return token;
}
