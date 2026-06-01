#include <string>
#include <iostream>
#include "modules/Interpreter.h"
#include "modules/Lexer.cpp"
#include "modules/Parser.cpp"

using namespace Interpreter;

int main()
{
    std::string expr{"5 - 23 + 6 * 3"};
    Tokens tokens{ Lexer::Tokenize(expr)};

    std::cout << "Expression: " << expr
              << "\nTokenising expression...\n";

    for(Token t: tokens)
        std::cout << t << " ";
    std::cout << '\n';

    std::cout << "Parsing expression...\n";

    Tokens parsedTokens {Parser::Parse(tokens)};
    for(Token t: parsedTokens)
        std::cout << t << " ";
    std::cout << '\n';

    return 0;
}