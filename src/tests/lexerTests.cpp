#include "Test.h"
#include "../modules/Lexer.h"

////////////////
// LexerTests //
////////////////

// 1 //
TEST("Return_empty_token_list_when_empty_expression")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("") };
    CONFIRM(true, tokens.empty());
}

// 2 //
TEST("Return_op_token_list_when_empty_expression")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+") };
    CONFIRM(1, (int)tokens.size());
    CONFIRM("+", tokens[0].getContent());
}

// 3 //
TEST("Should_tokenize_single_digit")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("1") };
    CONFIRM(1, (int)tokens.size());
    CONFIRM("1", tokens[0].getContent());
}

// 4 //
TEST("Should_tokenize_floating_point_number")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("12.34") };
    CONFIRM("12.34", tokens[0].getContent());
}

// 5 //
TEST("Should_tokenize_plus_and_number")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+12.34") };
    CONFIRM("+", tokens[0].getContent());
    CONFIRM("12.34", tokens[1].getContent());
}

// 6 //
TEST("Should_skip_spaces")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize(" 1 +  12.34  ") };
    CONFIRM("1", tokens[0].getContent());
    CONFIRM("+", tokens[1].getContent());
    CONFIRM("12.34", tokens[2].getContent());
}

// 7 //
TEST("Should_tokenize_complex_experssion")
{
    Interpreter::Tokens tokens(Interpreter::Lexer::Tokenize("1+2*3/(4-5)"));
    CONFIRM("1", tokens[0].getContent());
    CONFIRM("+", tokens[1].getContent());
    CONFIRM("2", tokens[2].getContent());
    CONFIRM("*", tokens[3].getContent());
    CONFIRM("3", tokens[4].getContent());
    CONFIRM("/", tokens[5].getContent());
    CONFIRM("(", tokens[6].getContent());
    CONFIRM("4", tokens[7].getContent());
    CONFIRM("-", tokens[8].getContent());
    CONFIRM("5", tokens[9].getContent());
    CONFIRM(")", tokens[10].getContent());
}