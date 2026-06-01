 #include "Interpreter.h"

 namespace Interpreter
 {
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
 