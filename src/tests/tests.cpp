#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../modules/Lexer.h"

// class LexerEncoding: public testing::Test
// {
// public:
//     Lexer lexer;

// };

TEST(LexerTests, Return_empty_token_list_when_empty_expression)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("") };
    EXPECT_EQ(true, tokens.empty());
}

TEST(LexerTests, Return_op_token_list_when_empty_expression)
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("") };
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ("+", tokens[0].content);
}
