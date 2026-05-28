#pragma once

#include <exception>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

namespace Interpreter
{
    enum class TokenType 
    {
        Operator, Number, Unknown
    };

    enum Operator
    {
        Plus = '+',
        Minus = '-',
        Mult = '*',
        Div = '/'
    };

    class Token
    {
        std::string content;
        TokenType type;
    public:
        explicit Token(std::string cont): content{cont}
        {
            if(cont == std::string{ Operator::Plus } || 
               cont == std::string{ Operator::Minus} ||
               cont == std::string{ Operator::Mult } ||
               cont == std::string{ Operator::Div }) 
                type = TokenType::Operator;
            else 
                type = TokenType::Unknown;
         }
        explicit Token(double num): content{ std::to_string(num) }, type{ TokenType::Number }
        {
            content.erase(content.find_last_not_of('0') + 1, std::string::npos);
            if(content.back() == '.') content.pop_back();
        }
        explicit Token(Operator op): type{TokenType::Operator}
        {
            if(op == Operator::Plus) content = std::string{Operator::Plus};
            if(op == Operator::Minus) content = std::string{Operator::Minus};
            if(op == Operator::Mult) content = std::string{Operator::Mult};
            if(op == Operator::Div) content = std::string{Operator::Div};
        }
        bool operator==(const Token& t) const
        { return (type == t.type) && (content == t.content); }
        std::string getContent() const
        { return content; }
        TokenType Type() const
        { return type; }
    };

    typedef std::vector<Token> Tokens;

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

    namespace Parser 
    {
        inline Tokens Parse(const Tokens &tokens) 
        {
            Tokens output;
            Tokens stack;
            auto popAll = [&]() { while(!stack.empty()) 
            {
                output.push_back(stack.back());
                stack.pop_back();
            }};
            for(const Token &token : tokens)
            {
                if(token.Type() == TokenType::Operator)
                {
                    popAll();
                    stack.push_back(token);
                    continue;
                }
                output.push_back(token);
            }
            popAll();
            return output; 
        }
    } // namespace Parser
}
