#include "lexer.h"
#include <iostream>

using namespace std;

int main() {
  string mysource = "-";
  Lexer lexer(mysource);

  // testing token
  Token mytoken = lexer.getToken();
  cout << "token source: " << mytoken.tokenText << endl;
  cout << "token type: " << mytoken.tokenType << endl;
}
