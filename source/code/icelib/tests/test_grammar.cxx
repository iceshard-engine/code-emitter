
#include <catch2/catch.hpp>
#include <ice/input/tokenizer_tasks.hxx>
#include <ice/input/grammar.hxx>

SCENARIO("Grammar", "[parsing,grammar]")
{
    GIVEN("A empty string")
    {
        using namespace ice::input;
        using namespace ice::input::grammar;

        std::string empty_input = "const double&x=\t\t33.3f;";

        auto tokenizer = ice::input::tokenize_string(empty_input, "empty_input");

        auto grammar = ice::input::grammar::Grammar{};
        grammar.add(ice::input::grammar::Group{
            .name = "int {symbol} = {number};",
            .rules = {
                RuleValue{ .token = TokenType::Symbol, .value = "const" },
                RuleType{ .token = TokenType::Whitespace },
                RuleValue{ .token = TokenType::Symbol, .value = "int", .optional = true },
                RuleValue{ .token = TokenType::Symbol, .value = "float", .optional = true },
                RuleValue{ .token = TokenType::Symbol, .value = "double", .optional = true },
                RuleType{ .token = TokenType::Whitespace, .optional = true },
                RuleValue{ .token = TokenType::Punctuation, .value = "&" },
                RuleType{ .token = TokenType::Whitespace, .optional = true },
                RuleType{ .token = TokenType::Symbol },
                RuleType{ .token = TokenType::Whitespace, .optional = true },
                RuleValue{ .token = TokenType::Punctuation, .value = "=" },
                RuleType{ .token = TokenType::Whitespace, .optional = true },
                RuleType{ .token = TokenType::Number },
                RuleType{ .token = TokenType::Whitespace, .optional = true },
                RuleValue{ .token = TokenType::Punctuation, .value = ";" },
            } });
        grammar.add(ice::input::grammar::Group{
            .name = "return {symbol};",
            .rules = {
                RuleValue{ .token = TokenType::Symbol, .value = "return" },
                RuleType{ .token = TokenType::Whitespace },
                RuleType{ .token = TokenType::Symbol },
                RuleValue{ .token = TokenType::Punctuation, .value = ";" },
            } });

        REQUIRE(grammar.parse(tokenizer));
        grammar.print();
    }
}