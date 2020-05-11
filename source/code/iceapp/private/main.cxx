#include <ice/assert.hxx>
#include <ice/job.hxx>

#include <fmt/format.h>
#include <CLI/CLI.hpp>

#include <filesystem>

#include "module_loader.hxx"
#include "generic_job.hxx"

int main(int argc, char** argv)
{
    CLI::App code_emitter{ "Code emitter v0.1" };

    std::string input_file;
    code_emitter.add_option("-i,--input", input_file, "The input file to be preprocessed.")
        ->required();

    std::string output_file;
    code_emitter.add_option("-o,--output", output_file, "The resulting output file.")
        ->required();

    std::vector<std::string> modules_path_list;
    code_emitter.add_option("--modules", modules_path_list, "Location of Ice modules.")
        ->default_val(".");

    //std::vector<std::string> serializers;
    //code_emitter.add_option("-s,--serializer", serializers, "Serializers to be used, will default to all if none is chosen.");

    //std::string parser;
    //code_emitter.add_option("-p,--parser", parser, "The parser to be used if multiple are available, fails if none is chosen");

    CLI11_PARSE(code_emitter, argc, argv);

    // Check the file for existance.
    if (std::filesystem::is_regular_file(input_file) == false)
    {
        fmt::print("Input file '{}' does not exist!\n", input_file);
        return 1;
    }

    {
        ice::ModuleLoader module_loader;

        // Find and load additional modules.
        for (auto modules_path : modules_path_list)
        {
            module_loader.load_all(modules_path);
        }

        // Create a generic job (1 parser, 1 serializer, N generators)
        auto job = ice::create_generic_job(module_loader, {
            { "input", { input_file } }
        });

        // Execute the job
        job->execute();
    }

    return 0;
}
