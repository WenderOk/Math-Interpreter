#include "Test.h"
#include "../modules/Interpreter.h"
#include "../modules/Lexer.cpp"

////////////////
// LexerTests //
////////////////

// === EmptyPolicy — для наборов тестов без setup/teardown ===
struct EmptyPolicy {
    void setup() {}
    void teardown() {}
};

static MereTDD::TestSuiteSetupAndTeardown<EmptyPolicy> gLexerSuite("Lexer Tests", "Lexer");

// 1 //
TEST_SUITE("Return_empty_token_list_when_empty_expression", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("") };
    CONFIRM(true, tokens.empty());
}

// 2 //
TEST_SUITE("Return_op_token_list_when_empty_expression", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+") };
    CONFIRM(1, (int)tokens.size());
    CONFIRM("+", tokens[0].Content());
}

// 3 //
TEST_SUITE("Should_tokenize_single_digit", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("1") };
    CONFIRM(1, (int)tokens.size());
    CONFIRM("1", tokens[0].Content());
}

// 4 //
TEST_SUITE("Should_tokenize_floating_point_number", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("12.34") };
    CONFIRM("12.34", tokens[0].Content());
}

// 5 //
TEST_SUITE("Should_tokenize_plus_and_number", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize("+12.34") };
    CONFIRM("+", tokens[0].Content());
    CONFIRM("12.34", tokens[1].Content());
}

// 6 //
TEST_SUITE("Should_skip_spaces", "Lexer")
{
    Interpreter::Tokens tokens{ Interpreter::Lexer::Tokenize(" 1 +  12.34  ") };
    CONFIRM("1", tokens[0].Content());
    CONFIRM("+", tokens[1].Content());
    CONFIRM("12.34", tokens[2].Content());
}

// 7 //
TEST_SUITE("Should_tokenize_complex_experssion", "Lexer")
{
    Interpreter::Tokens tokens(Interpreter::Lexer::Tokenize("1+2*3/(4-5)"));
    CONFIRM("1", tokens[0].Content());
    CONFIRM("+", tokens[1].Content());
    CONFIRM("2", tokens[2].Content());
    CONFIRM("*", tokens[3].Content());
    CONFIRM("3", tokens[4].Content());
    CONFIRM("/", tokens[5].Content());
    CONFIRM("(", tokens[6].Content());
    CONFIRM("4", tokens[7].Content());
    CONFIRM("-", tokens[8].Content());
    CONFIRM("5", tokens[9].Content());
    CONFIRM(")", tokens[10].Content());
}