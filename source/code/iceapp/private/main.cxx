#include <ice/input/tokenizer_tasks.hxx>
#include <ice/assert.hxx>

#include <fmt/format.h>
#include <CLI/CLI.hpp>

#include <filesystem>

#include "module_loader.hxx"

int main(int argc, char** argv)
{
    CLI::App code_emitter{ "Code emitter v0.1" };

    std::string input_file;
    code_emitter.add_option("-i,--input", input_file, "The input file to be preprocessed.")
        ->required();

    std::string output_file;
    code_emitter.add_option("-o,--output", output_file, "The resulting output file.")
        ->required();

    CLI11_PARSE(code_emitter, argc, argv);

    // Check the file for existance.
    if (std::filesystem::is_regular_file(input_file) == false)
    {
        fmt::print("Input file '{}' does not exist!\n", input_file);
        return 1;
    }

    {
        ice::ModuleLoader module_loader;

        input_file = std::filesystem::canonical(input_file).generic_string();

        std::ifstream file{ input_file, std::ios::binary | std::ios::in };

        auto tokenizer = ice::input::tokenize_stream(file, input_file);
        for (auto token = tokenizer.next_token(); tokenizer.has_next_token(); token = tokenizer.next_token())
        {
            ht_assert(token.type != ice::input::TokenType::Invalid, "{}", token);
            fmt::print("{}\n", token);
        }
    }

    return 0;
}
