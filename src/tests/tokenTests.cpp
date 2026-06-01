#include "Test.h"
#include "../modules/Interpreter.h"

////////////////
// TokenTests //
////////////////

// === EmptyPolicy — для наборов тестов без setup/teardown ===
struct EmptyPolicy {
    void setup() {}
    void teardown() {}
};

static MereTDD::TestSuiteSetupAndTeardown<EmptyPolicy> gTokensSuite("Tokens Tests", "Tokens");

// 1 //
TEST_SUITE("Should_get_type_for_number_token", "Tokens")
{
    Interpreter::Token numToken(1.2);
    CONFIRM(Interpreter::TokenType::Number, numToken.Type());
}

// 2 //
TEST_SUITE("Should_get_type_for_operator_token", "Tokens")
{
    Interpreter::Token numToken(Interpreter::Operator::Plus);
    CONFIRM("+", numToken.Content());
}

// 3 //
TEST_SUITE("Should_get_operator_code_from_operator_token", "Tokens")
{
    Interpreter::Token operToken("+");
    CONFIRM(Interpreter::TokenType::Operator,operToken.Type());
}

// 4 //
TEST_SUITE("Should_get_number_value_from_number_token", "Tokens")
{
    Interpreter::Token numToken(1.23);
    CONFIRM(Interpreter::TokenType::Number, numToken.Type());
    CONFIRM("1.23", numToken.Content());
}