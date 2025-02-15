#include "lexer.h"

using namespace std;

// private
// public
// obj management
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
