#include <ice/input/tokenizer_tasks.hxx>
#include <ice/assert.hxx>
#include <fmt/format.h>

#include <fstream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    if (argc <= 1)
    {
        return 1;
    }

    std::ifstream file{ argv[1], std::ios::binary | std::ios::in };

    auto tokenizer = ice::input::tokenize_stream(file);
    for (auto token = tokenizer.next_token(); tokenizer.has_next_token(); token = tokenizer.next_token())
    {
        ht_assert(token.type != ice::input::TokenType::Invalid, "{}", token);
        fmt::print("{}\n", token);
    }

    return 0;
}
