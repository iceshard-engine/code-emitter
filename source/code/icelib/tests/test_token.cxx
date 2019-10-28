#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ice/input/tokenizer_tasks.hxx>

SCENARIO("Tokenizer", "[token,parsing]")
{
    GIVEN("An empty string")
    {
        std::string empty_input;

        auto tokenizer = ice::input::tokenize_string(empty_input, "empty_input");

        THEN("the tokenizer has a single 'EndOfFile' token.")
        {
            REQUIRE(tokenizer.has_next_token() == true);
            REQUIRE(tokenizer.next_token().type == ice::input::TokenType::EndOfFile);
            REQUIRE(tokenizer.has_next_token() == false);
        }
    }
}
