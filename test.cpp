#include "lexer.h"
#include <iostream>

using namespace std;

int main() {
  string mysource = "-";
  Lexer lexer(mysource);

  // testing token
  Token mytoken = lexer.getToken();
  cout << "token source: " << mytoken.tokenText << endl;
  if (mytoken.tokenType == Token::TokenTypes::MINUS) {
    cout << "token type MINUS" << endl;
  } else {
    cout << "token type failure" << endl;
  }
}
