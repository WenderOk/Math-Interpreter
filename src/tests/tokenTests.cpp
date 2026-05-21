#include "Test.h"
#include "../modules/Lexer.h"

////////////////
// TokenTests //
////////////////

// 1 //
TEST(TokenTests, Should_get_type_for_number_token)
{
    Interpreter::Token numToken(1.2);
    CONFIRM(Interpreter::TokenType::Number, numToken.getType());
}

// 2 //
TEST(TokenTests, Should_get_type_for_operator_token)
{
    Interpreter::Token numToken(Interpreter::Operator::Plus);
    CONFIRM("+", numToken.getContent());
}

// 3 //
TEST(TokenTests, Should_get_operator_code_from_operator_token)
{
    Interpreter::Token operToken("+");
    CONFIRM(Interpreter::TokenType::Operator, operToken.getType());
}

// 4 //
TEST(TokenTests, Should_get_number_value_from_number_token)
{
    Interpreter::Token numToken(1.23);
    CONFIRM(Interpreter::TokenType::Number, numToken.getType());
    CONFIRM("1.23", numToken.getContent());
}