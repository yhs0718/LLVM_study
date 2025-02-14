#include "parser.cpp"

int main() {
    while (true) {
        std::cout << "Ready> ";
        getNextToken();
        if (CurTok == tok_eof) break;

        if (CurTok == tok_def) {
            ParseFunctionDefinition();
            std::cout << "Parsed a function definition.\n";
            getNextToken();
            continue;  
        } 

        ParseBinaryExpr();
        std::cout << "Parsed an expression.\n";
    }
    return 0;
}
