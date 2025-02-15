#include "lexer.h"
#include <iostream>

using namespace std;

int main() {
  string mysource = "LET foobar = 123";
  Lexer lexer(mysource);

  while (lexer.peek() != '\0') {
    cout << lexer.curChar << endl;
    lexer.nextChar();
  }
}
