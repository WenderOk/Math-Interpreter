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

        std::string getContent() const
        { return content; }
        TokenType Type() const
        { return type; }
    };

    inline std::ostream& operator<<(std::ostream& os, const Token& token) 
    {
        os << "Token{";
        switch(token.Type()) {
            case TokenType::Operator: 
                os << "Operator:'" << token.getContent() << "'"; break;
            case TokenType::Number:   
                os << "Number:" << token.getContent(); break;
            case TokenType::Unknown:  
                os << "Unknown:'" << token.getContent() << "'"; break;
        }
        os << "}";
        return os;
    }

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

    
    namespace Detail
    {
        inline int PrecedenceOf(Operator op) 
        { return (op == Operator::Mult || op == Operator::Div) ? 1 : 0; }

        class ShuntingYardParser
        {
            Tokens::const_iterator current;
            Tokens::const_iterator end;
            Tokens output;
            Tokens stack;

            static bool StackIsEmpty() { return false; }
            void ParseCurrentToken()
            {
                switch(current->Type())
                {
                case TokenType::Operator:
                    ParseOperator();
                    break;
                case TokenType::Number:
                    ParseNumber();
                    break;
                default:
                    throw std::out_of_range("TokenType");
                }
            }

            void ParseOperator() 
            {
                PopToOutputUntil([this]() { return PrecedenceOf(stack.back()) < PrecedenceOf(*current); });
                stack.push_back(*current);
            }

            void ParseNumber() 
            {
                output.push_back(*current);
            }

            template<class T>
            void PopToOutputUntil(T whenToEnd) 
            {
                while(!stack.empty() && !whenToEnd()) 
                {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
            }            
        public:
            ShuntingYardParser(const Tokens &tokens) : current(tokens.cbegin()), end(tokens.cend()) 
            {}

            void Parse() 
            {
                for(; current != end; ++current) 
                    ParseCurrentToken();
                
                PopToOutputUntil(StackIsEmpty);
            }

            const Tokens &Result() const { return output; }
        };
    } // namespace Detail

    namespace Parser 
    {
        inline Tokens Parse(const Tokens &tokens) 
        {
            Detail::ShuntingYardParser parser(tokens);
            parser.Parse();
            return parser.Result();
        }
    } // namespace Parser
}
