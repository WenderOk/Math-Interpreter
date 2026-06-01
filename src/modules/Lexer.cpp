#include "Interpreter.h"
#include <string>
#include <sstream>

namespace Interpreter
{
    namespace Lexer
    {
        inline Tokens Tokenize(std::string expr) 
        {
            std::istringstream stream{expr};
            Tokens listTokens;
            char ch;
            
            while (stream >> ch)
            {
                if(std::isdigit(ch))
                {
                    stream.putback(ch);
                    double num;
                    stream >> num;
                    listTokens.push_back(Token{num});
                }
                else 
                    listTokens.push_back(Token{std::string(1, ch)});
            }
            return listTokens;
        }
    }
}
