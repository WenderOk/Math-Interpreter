#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../modules/Lexer.h"

////////////////
// LexerTests //
////////////////

// 1 //
TEST(LexerTests, Return_empty_token_list_when_empty_expression)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("") };
    EXPECT_EQ(true, tokens.empty());
}

// 2 //
TEST(LexerTests, Return_op_token_list_when_empty_expression)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+") };
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ("+", tokens[0].getContent());
}

// 3 //
TEST(LexerTests, Should_tokenize_single_digit)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("1") };
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ("1", tokens[0].getContent());
}

// 4 //
TEST(LexerTests, Should_tokenize_floating_point_number)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("12.34") };
    EXPECT_EQ("12.34", tokens[0].getContent());
}

// 5 //
TEST(LexerTests, Should_tokenize_plus_and_number)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+12.34") };
    EXPECT_EQ("+", tokens[0].getContent());
    EXPECT_EQ("12.34", tokens[1].getContent());
}

// 6 //
TEST(LexerTests, Should_skip_spaces)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize(" 1 +  12.34  ") };
    EXPECT_EQ("1", tokens[0].getContent());
    EXPECT_EQ("+", tokens[1].getContent());
    EXPECT_EQ("12.34", tokens[2].getContent());
}

// 7 //
TEST(LexerTests, Should_tokenize_complex_experssion)
{
    Interpreter::Tokens tokens(Interpreter::Lexer::Tokenize("1+2*3/(4-5)"));
    EXPECT_EQ("1", tokens[0].getContent());
    EXPECT_EQ("+", tokens[1].getContent());
    EXPECT_EQ("2", tokens[2].getContent());
    EXPECT_EQ("*", tokens[3].getContent());
    EXPECT_EQ("3", tokens[4].getContent());
    EXPECT_EQ("/", tokens[5].getContent());
    EXPECT_EQ("(", tokens[6].getContent());
    EXPECT_EQ("4", tokens[7].getContent());
    EXPECT_EQ("-", tokens[8].getContent());
    EXPECT_EQ("5", tokens[9].getContent());
    EXPECT_EQ(")", tokens[10].getContent());
}



////////////////
// TokenTests //
////////////////

// 1 //
TEST(TokenTests, Should_get_type_for_number_token)
{
    Interpreter::Token numToken(1.2);
    EXPECT_EQ(Interpreter::TokenType::Number, numToken.getType());
}

// 2 //
TEST(TokenTests, Should_get_type_for_operator_token)
{
    Interpreter::Token numToken(Interpreter::Operator::Plus);
    EXPECT_EQ("+", numToken.getContent());
}

// 3 //
TEST(TokenTests, Should_get_operator_code_from_operator_token)
{
    Interpreter::Token operToken("+");
    EXPECT_EQ(Interpreter::TokenType::Operator, operToken.getType());
}

// 4 //
TEST(TokenTests, Should_get_number_value_from_number_token)
{
    Interpreter::Token numToken(1.23);
    EXPECT_EQ(Interpreter::TokenType::Number, numToken.getType());
    EXPECT_EQ("1.23", numToken.getContent());
}
