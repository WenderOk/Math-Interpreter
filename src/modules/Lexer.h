#pragma once

#include <vector>
#include <string>

namespace Interpreter
{
    struct Token
    {
        std::string content;
    };

    typedef std::vector<Token> Tokens;
    enum Operator
    {
        Plus = '+',
        Minus = '-',
        Mult = '*',
        Div = '/'
    };
    // typedef Operator Token;

    namespace Lexer
    {
        inline Tokens Tokenize(std::string expr) 
        {
            if(expr.empty()) return Tokens{};
            return {Token{"+"}};
        }
    }
}
