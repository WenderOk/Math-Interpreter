#include "Test.h"
#include "../modules/Lexer.h"

//////////\//////
// ParserTests //
/////////\///////

// === EmptyPolicy — для наборов тестов без setup/teardown ===
struct EmptyPolicy {
    void setup() {}
    void teardown() {}
};

static MereTDD::TestSuiteSetupAndTeardown<EmptyPolicy> gParserSuite("Parser Tests", "Parser");

using namespace Interpreter;

// 1 //
TEST_SUITE("Should_return_empty_list_when_put_empty_list", "Parser")
{
    Tokens tokens = Parser::Parse({});
    CONFIRM( true, tokens.empty() );
}

// 2 //
TEST_SUITE("Should_parse_single_number", "Parser")
{
    Tokens tokens = Parser::Parse({Token(1)});
    CONFIRM( {Token(1)}, tokens );
}

// 3 //
TEST_SUITE("Should_parse_num_plus_num", "Parser")
{
    Tokens tokens = Parser::Parse({ Token(1), Token(Operator::Plus), Token(2) });
    Tokens expected = { Token(1), Token(2), Token(Operator::Plus) };
    CONFIRM( expected, tokens );
}

// 4 //
TEST_SUITE("Should_parse_two_additions", "Parser")
{
    Tokens tokens = Parser::Parse({ Token(1), Token(Operator::Plus), Token(2), Token(Operator::Plus), Token(3) });
    Tokens expected = { Token(1), Token(2), Token(Operator::Plus), Token(3), Token(Operator::Plus) };
    CONFIRM( expected, tokens );
}

// 5 //
TEST_SUITE("Should_get_same_precedence_for_operator_pairs", "Parser")
{
    CONFIRM( Detail::PrecedenceOf(Operator::Plus), Detail::PrecedenceOf(Operator::Minus) );
    CONFIRM( Detail::PrecedenceOf(Operator::Mult), Detail::PrecedenceOf(Operator::Div) );
}

// 6 //
TEST_SUITE("Should_get_greater_precedence_for_multiplicative_operators", "Parser")
{
    CONFIRM( true, Detail::PrecedenceOf(Operator::Mult) > Detail::PrecedenceOf(Operator::Plus) );
}

// 7 //
TEST_SUITE("Should_parse_add_and_mul", "Parser")
{
    Tokens tokens = Parser::Parse({ Token(1), Token(Operator::Plus), Token(2), Token(Operator::Mult), Token(3) });
    Tokens expected = { Token(1), Token(2), Token(3), Token(Operator::Mult), Token(Operator::Plus) };
    CONFIRM( expected, tokens );
}

// 8 //
TEST_SUITE("Should_parse_complex_experssion", "Parser")
{
    Tokens tokens = Parser::Parse({
        Token(1), Token(Operator::Plus), Token(2), Token(Operator::Div), Token(3),
        Token(Operator::Minus), Token(4), Token(Operator::Mult), Token(5)
    });
    Tokens expected = 
    {
        Token(1), Token(2), Token(3), Token(Operator::Div), Token(Operator::Plus),
        Token(4), Token(5), Token(Operator::Mult), Token(Operator::Minus)
    };
    CONFIRM( expected, tokens );
}