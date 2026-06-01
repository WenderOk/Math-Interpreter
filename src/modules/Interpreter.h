#pragma once

#include <exception>
#include <iterator>
#include <stdexcept>
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

        operator Operator() const 
        {
            if(type != TokenType::Operator) throw std::logic_error("Should be operator token.");
            return static_cast<Operator>(content[0]);
        }

        std::string Content() const
        { return content; }
        TokenType Type() const
        { return type; }
    };

    inline std::ostream& operator<<(std::ostream& out, const Token& token) 
    {
        out << "{ ";
        switch(token.Type()) {
            case TokenType::Operator: 
                out << "Operator: " << token.Content(); break;
            case TokenType::Number:   
                out << "Number: " << token.Content(); break;
            case TokenType::Unknown:  
                out << "Unknown: " << token.Content(); break;
        }
        out << " }";
        return out;
    }

    typedef std::vector<Token> Tokens;
}
