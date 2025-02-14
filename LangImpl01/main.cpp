#include <iostream>
#include "lexer.cpp"

int main() {
    while (true) {
        int tok = gettok();
        std::cout << "Token " << tok << "\n";
        if (tok == tok_eof) break;
    }
    return 0;
}