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
    CONFIRM(true, tokens.empty());
}
